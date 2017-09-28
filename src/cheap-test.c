#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#define NDEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/*#include <math.h>*/

#include <cheap.h>

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
   data_print (array, i, j);
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
      insert_cheap (&cheap, nums + testi);
      nums[testi] = rand ();
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
