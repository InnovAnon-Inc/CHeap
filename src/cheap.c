#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

/*#define NDEBUG 1*/

#include <stdbool.h>
#ifndef NDEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>

/*#include <math.h>*/

#include <cheap.h>

#define CHEAP_ROOT ((size_t) 0)

__attribute__ ((const, leaf, nothrow, warn_unused_result))
size_t get_parent (size_t i) { return (i - 1) / 2; }

__attribute__ ((const, leaf, nothrow, warn_unused_result))
bool has_parent (size_t i) { return i != 0; }

__attribute__ ((const, leaf, nothrow, warn_unused_result))
size_t get_left_child (size_t i) { return i * 2 + 1; }

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool has_left_child (cheap_t const *restrict cheap, size_t i) {
   size_t child = get_left_child (i);
   return child < cheap->n;
}

__attribute__ ((const, leaf, nothrow, warn_unused_result))
size_t get_right_child (size_t i) { return i * 2 + 2; }

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool has_right_child (cheap_t const *restrict cheap, size_t i) {
   size_t child = get_right_child (i);
   return child < cheap->n;
}

__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result))
bool has_child (cheap_t const *restrict cheap, size_t i) {
   return has_left_child (cheap, i)  || has_right_child (cheap, i);
   /*return has_right_child (cheap, i) || has_left_child (cheap, i);*/
}

__attribute__ ((pure, leaf, nonnull (1), nothrow, warn_unused_result))
int cheap_cmp (cheap_t const *restrict cheap, size_t i, size_t j) {
   void const *restrict ie = index_array (&(cheap->array), i);
   void const *restrict je = index_array (&(cheap->array), j);
   return cheap->cmp (ie, je);
}

/* O (log n), Omega (1) */
__attribute__ ((nonnull (1), nothrow))
void cheapify_up (cheap_t const *restrict cheap, size_t i) {
   size_t parent;
   while (has_parent (i)) {
      /* Compare the added element with its parent; if they are in the correct order, stop. */
      parent = get_parent (i);

      /* min heap */
      if (cheap_cmp (cheap, i, parent) >= 0) return;

      /* If not, swap the element with its parent and return to the previous step. */
      swap_array2 (&(cheap->array), i, parent);

      /* tail-recursive optimization: cheapify_up (cheap, parent) */
      i = parent;
   }
}

__attribute__ ((nonnull (1, 2), nothrow))
void insert_cheap (cheap_t *restrict cheap, void const *restrict e) {
   size_t old_n = cheap->n;
   /* Add the element to the bottom level of the heap. */
   set_array (&(cheap->array), old_n, e);
   cheap->n++;
   cheapify_up (cheap, old_n);
}

/* O (n log n) ? */
__attribute__ ((nonnull (1, 2), nothrow))
void inserts_cheap (cheap_t *restrict cheap,
   void const *restrict e, size_t n) {
   size_t old_n = cheap->n;
   sets_array (&(cheap->array), old_n, e, n);
   cheap->n += n;

   TODO (floyd ?)
   for ( ; old_n != cheap->n; old_n++)
      cheapify_up (cheap, old_n);
}

__attribute__ ((nonnull (1), nothrow))
void cheapify_down (cheap_t const *restrict cheap, size_t i) {
   size_t lchild;
   size_t rchild;
   size_t largest;
   while (true) {
      lchild  = get_left_child  (i);
      rchild  = get_right_child (i);
      largest = i;

      /* Compare the new root with its children; if they are in the correct order, stop. */
      if (has_left_child (cheap, i)
      && cheap_cmp (cheap, lchild, largest) < 0)
         largest = lchild;

      if (has_right_child (cheap, i)
      && cheap_cmp (cheap, rchild, largest))
         largest = rchild;

      /* If not, swap the element with one of its children and return to the previous step. (Swap with its smaller child in a min-heap and its larger child in a max-heap.) */
      if (largest == i) return;

      swap_array2 (&(cheap->array), i, largest);

      /* tail-recursive optimization: cheapify_down (cheap, largest) */
      i = largest;
   }
}

__attribute__ ((nonnull (1, 2), nothrow))
void remove_cheap (cheap_t *restrict cheap, void *restrict e) {
   /* Replace the root of the heap with the last element on the last level. */
   /*swap_array2 (&(cheap->array), CHEAP_ROOT, cheap->n - 1);*/
   get_array (&(cheap->array), CHEAP_ROOT, e);
   cp_array (&(cheap->array), cheap->n - 1, CHEAP_ROOT);
   cheap->n--;

   cheapify_down (cheap, CHEAP_ROOT);
}

__attribute__ ((nonnull (1, 2), nothrow))
void removes_cheap (cheap_t *restrict cheap,
   void *restrict e, size_t n) {
   size_t i;
   gets_array (&(cheap->array), CHEAP_ROOT, e, n); /* mostly sorted... mostly */
   cps_array (&(cheap->array), cheap->n - n, CHEAP_ROOT, n);
   cheap->n -= n;

   TODO (floyd ?: see build_cheap ())
   /*for (i = get_parent (n) + 1; i != 0; i--)*/
   for (i = n; i != 0; i--)
      cheapify_down (cheap, i - 1);
}

/* assumes array is init'd but not yet heaped */
__attribute__ ((nonnull (1), nothrow))
void build_cheap (cheap_t const *restrict cheap) {
   size_t i;
   for (i = get_parent (cheap->n) + 1; i != 0; i--)
      cheapify_down (cheap, i - 1);
}

__attribute__ ((leaf, nonnull (1, 2, 5), nothrow))
void init_cheap (cheap_t *restrict cheap,
   void *restrict data, size_t esz, size_t n, cheap_cmp_t cmp) {
   init_array (&(cheap->array), data, esz, n);
   cheap->n   = 0;
   cheap->cmp = cmp;
}

__attribute__ ((leaf, nonnull (1, 4), nothrow, warn_unused_result))
int alloc_cheap (cheap_t *restrict cheap,
   size_t esz, size_t n, cheap_cmp_t cmp) {
   error_check (alloc_array (&(cheap->array), esz, n) != 0) return -1;
   cheap->n   = 0;
   cheap->cmp = cmp;
   return 0;
}

__attribute__ ((leaf, nonnull (1), nothrow))
void free_cheap (cheap_t const *restrict cheap) {
   free_array (&(cheap->array));
}
