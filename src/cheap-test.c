#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <mmalloc.h>
#include <simon.h>

#include <cheap.h>

#ifndef TEST

__attribute__ ((nonnull (1), nothrow))
static void dumpq(cheap_t const *restrict q) {
   size_t i;
   fputs ("Q: ", stderr);
   for (i = 0; i != used_space_cheap (q); i++) {
      void *restrict head = index_cheap (q, i);
      fprintf (stderr, "(%1d:%3d), ", (int) i, *(int *restrict) head);
   }
   fputs ("\n", stderr);
}

typedef struct {
   size_t esz;
   size_t n;
} cheap_alloc_t;

__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result))
static int cmp (void const *restrict a, void const *restrict b) {
   int ai = *(int const *restrict) a;
   int bi = *(int const *restrict) b;
   return ai - bi;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static void *cheap_alloc (void const *restrict arg_) {
   cheap_alloc_t const *restrict arg = (cheap_alloc_t const *restrict) arg_;
   return ez_alloc_cheap (arg->esz, arg->n, cmp);
}

__attribute__ ((nonnull (1), nothrow))
static void generate_int (void *restrict arg_) {
   int *restrict arg = (int *restrict) arg_;
   *arg = random_range_java (-10, 10); /* arbitrary params */
}

__attribute__ ((nonnull (1), nothrow))
static void generates_int (void *restrict arg_, size_t n) {
   int *restrict arg = (int *restrict) arg_;
   size_t i;
   for (i = 0; i != n; i++)
      arg[i] = random_range_java (-10, 10); /* arbitrary params */
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int cheap_add_test (void *restrict arg_) {
   int tmp;
   int err = add_test (arg_, &tmp,
      (isfull_t) isfull_cheap, generate_int, (add_t) insert_cheap);
   if (err == TEST_NA) return 0;
   error_check (err != 0) return -1;
   fprintf (stderr, "caq_add_test (), tmp:%d\n", tmp);
   dumpq ((cheap_t *restrict) arg_);
   return 0;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int cheap_remove_test (void *restrict arg_) {
   int tmp;
   int err = remove_test (arg_, &tmp,
      (isempty_t) isempty_cheap, (remove_t) remove_cheap);
   if (err == TEST_NA) return 0;
   error_check (err != 0) return -1;
   fprintf (stderr, "caq_remove_test (), tmp:%d\n", tmp);
   dumpq ((cheap_t *restrict) arg_);
   return 0;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int cheap_adds_test (void *restrict arg_) {
   int tmps[13]; /* arbitrary params */
   error_check (adds_test (arg_, tmps, ARRSZ (tmps),
      (remaining_space_t) remaining_space_cheap,
      generates_int, (adds_t) inserts_cheap) != 0)
      return -1;
   /* can't print tmps, because we don't know how many elements are init'd */
   fprintf (stderr, "caq_adds_test ()\n");
   dumpq ((cheap_t *restrict) arg_);
   return 0;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int cheap_removes_test (void *restrict arg_) {
   int tmps[12]; /* arbitrary params */
   error_check (removes_test (arg_, tmps, ARRSZ (tmps),
      (used_space_t) used_space_cheap, (removes_t) removes_cheap) != 0)
      return -1;
   /* can't print tmps, because we don't know how many elements are init'd */
   fprintf (stderr, "caq_removes_test ()\n");
   dumpq ((cheap_t *restrict) arg_);
   return 0;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int cheap_cb (void *restrict arg) {
   stdcb_t tests[4];

   TODO (more tests)
   tests[0] = cheap_add_test;
   tests[1] = cheap_remove_test;
   tests[2] = cheap_adds_test;
   tests[3] = cheap_removes_test;

   error_check (random_ops (arg, tests, ARRSZ (tests), 1000) != 0) /* arbitrary params */
   /*random_ops2 (arg, tests, ARRSZ (tests));*/
      return -1;

   return 0;
}

int main(void) {
   time_t t;
   cheap_alloc_t alloc_arg;

   t = time (NULL);
   srand ((unsigned int) t);

   alloc_arg.esz = sizeof (int);
   alloc_arg.n   = 10; /* arbitrary params */

   error_check (ezmalloc (cheap_alloc, &alloc_arg,
      cheap_cb,
      (free_t) ez_free_cheap) != 0)
      return EXIT_FAILURE;

   return EXIT_SUCCESS;
}

#else

/* must provide a callback for printing each field of a struct */

static void data_print (void const *restrict data,
   size_t i, size_t j) {
   fprintf (stderr, "["); fflush (stderr);
   /*if (array->n != 0) {*/
   if (i != j) {
      fprintf (stderr, "%d", ((int const *restrict) data)[i]); fflush (stderr);
      for (i++; i != j; i++)
         fprintf (stderr, ", %d", ((int const *restrict) data)[i]); fflush (stderr);
   }
   fprintf (stderr, "]\n"); fflush (stderr);
}

/* must provide acllback for printing array->data */

__attribute__ ((nonnull (1), nothrow))
static void array_print (array_t const *restrict array,
   size_t i, size_t j) {
   fprintf (stderr, "esz : %d\n", (int) array->esz);  fflush (stderr);
   fprintf (stderr, "maxn: %d\n", (int) array->n); fflush (stderr);
   data_print (array->data, i, j);
}

__attribute__ ((nonnull (1), nothrow))
static void cheap_print (cheap_t const *restrict darr) {
   size_t i;
   fprintf (stderr, "n: %d\n", (int) darr->n);    fflush (stderr);
   array_print ((&darr->array), (size_t) 0, darr->n);
}

__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result))
static int cmp (void const *restrict a, void const *restrict b) {
   int ai = *(int const *restrict) a;
   int bi = *(int const *restrict) b;
   return ai - bi;
}

__attribute__ ((nothrow, warn_unused_result))
int main (void) {
   cheap_t cheap;
   time_t t;
   size_t ntest = 100;
   size_t testi;
   int nums[10];
   int maxn = 20;

   t = time (NULL);
   srand ((unsigned int) t);

   error_check (alloc_cheap (&cheap,
      sizeof (*nums), ARRSZ (nums), cmp) != 0)
      return -1;

   /*#pragma GCC ivdep*/
   for (testi = 0; testi != ARRSZ (nums); testi++)
      nums[testi] = rand () % maxn;

   cheap_print (&cheap);
   for (testi = 0; testi != ARRSZ (nums); testi++) {
      fprintf (stderr, "nums 1 [%d]: %d\n", (int) testi, nums[testi]); fflush (stderr);
      insert_cheap (&cheap, nums + testi);
      nums[testi] = rand ();
      fprintf (stderr, "nums 2 [%d]: %d\n", (int) testi, nums[testi]); fflush (stderr);
      cheap_print (&cheap);
   }
   fputs ("", stderr);

   /*#pragma GCC ivdep*/
   /*for (testi = 0; testi != ARRSZ (nums); testi++)
      nums[testi] = rand ();*/

   for (testi = 0; testi != ARRSZ (nums); testi++) {
      remove_cheap (&cheap, nums + testi);
      cheap_print (&cheap);
   }
   data_print (nums, (size_t) 0, ARRSZ (nums));


   /*
   for (testi = 0; testi != ntest; testi++)
      switch (rand () % 1) {
      case 0:

         break;
      default __builtin_unreachable ();
      }
   */

   free_cheap  (&cheap);

   /*
   error_check (init_test (&cheap) != 0) return -1;

   get_nums (nums, ARRSZ (nums));

   for (testi = 0; testi != ntest; testi++)
      switch (rand () % 10) {
      case 0:
         error_check (test0 (&darr) != 0) return -4;
         break;
      case 1:
         error_check (test1 (&darr, ARRSZ (nums)) != 0) return -5;
         break;
      case 2:
         error_check (test2 (&darr) != 0) return -6;
         break;
      case 3:
         error_check (test3 (&darr) != 0) return -6;
         break;
      case 4:
         error_check (test4 (&darr) != 0) return -7;
         break;
      case 5:
         error_check (test5 (&darr, nums, ARRSZ (nums)) != 0) return -5;
         break;
      case 6:
         error_check (test6 (&darr) != 0) return -7;
         break;
      case 7:
         error_check (test7 (&darr) != 0) return -7;
         break;
      case 8:
         error_check (test8 (&darr) != 0) return -8;
         break;
      case 9:
         error_check (test9 (&darr) != 0) return -9;
         break;
      default: __builtin_unreachable ();
      }

   free_test (&cheap);
   */
   fputs ("success", stderr); fflush (stderr);

   return EXIT_SUCCESS;
}

#endif
