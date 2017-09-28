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

#define CHEAP_ROOT (0)

__attribute__ ((const, leaf, nothrow, warn_unused_result))
size_t get_parent (size_t i) { return i / 2; }

__attribute__ ((const, leaf, nothrow, warn_unused_result))
bool has_parent (size_t i) { return i != 0; }

__attribute__ ((const, leaf, nothrow, warn_unused_result))
size_t get_left_child (size_t i) { return i * 2; }

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool has_left_child (cheap_t const *restrict cheap, size_t i) {
   size_t child = get_left_child (i);
   return child < cheap->n;
}

__attribute__ ((const, leaf, nothrow, warn_unused_result))
size_t get_right_child (size_t i) { return i * 2 + 1; }

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
   void const *restrict ie = get_array (&(cheap->array), i);
   void const *restrict je = get_array (&(cheap->array), j);
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
      if (cheap_cmp (&cheap, i, parent) >= 0) return;

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

   for ( ; old_n != cheap->n; old_n++)
      cheapify_up (cheap, old_n);
}

__attribute__ ((nonnull (1), nothrow))
void cheapify_down (cheap_t const *restrict cheap, size_t i) {
   size_t child;
   while (has_child (cheap, i)) {
      /* Compare the new root with its children; if they are in the correct order, stop. */
      /* If not, swap the element with one of its children and return to the previous step. (Swap with its smaller child in a min-heap and its larger child in a max-heap.) */
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

   for (i = n - 1; i >= 0; i--)
      cheapify_down (cheap, i);
}

/* init, alloc, free */
