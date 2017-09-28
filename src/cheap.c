#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

/*#define NDEBUG 1*/

#ifndef NDEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>

/*#include <math.h>*/

#include <cheap.h>

__attribute__ ((const, leaf, nothrow, warn_unused_result))
size_t get_parent (size_t i) { return i / 2; }

__attribute__ ((const, leaf, nothrow, warn_unused_result))
bool has_parent (size_t i) { return i != 0; }

__attribute__ ((const, leaf, nothrow, warn_unused_result))
size_t get_left_child (size_t i) { return i * 2; }

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool has_left_child (cheap_t *restrict cheap, size_t i) {
   size_t child = get_left_child (i);
   return child < cheap->n;
}

__attribute__ ((const, leaf, nothrow, warn_unused_result))
size_t get_right_child (size_t i) { return i * 2 + 1; }

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool has_right_child (cheap_t *restrict cheap, size_t i) {
   size_t child = get_right_child (i);
   return child < cheap->n;
}

__attribute__ ((pure, leaf, nonnull (1), nothrow, warn_unused_result))
int cheap_cmp (cheap_t const *restrict cheap, size_t i, size_t j) {
   void const *restrict ie = get_array (&(cheap->array), i);
   void const *restrict je = get_array (&(cheap->array), j);
   return cheap->cmp (ie, je);
}

__attribute__ ((nonnull (1)))
void insert_cheap (cheap_t *restrict cheap, void const *restrict e) {
   size_t parent;
   /* Add the element to the bottom level of the heap. */
   set_array (&(cheap->array), cheap->n, e);
   cheap->n++;

   /* Compare the added element with its parent; if they are in the correct order, stop. */
   parent = get_parent (cheap->n - 1);
   /* min heap */
   if (cheap_cmp (&cheap, cheap->n - 1, parent) >= 0) return;

   /* If not, swap the element with its parent and return to the previous step. */
   swap_array2 (&(cheap->array), cheap->n - 1, parent);
}