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

__attribute__ ((nonnull (1)))
void insert_cheap (cheap_t *restrict cheap) {
   /* Add the element to the bottom level of the heap. */
   cheap->data
   /* Compare the added element with its parent; if they are in the correct order, stop. */
   /* If not, swap the element with its parent and return to the previous step. */
}