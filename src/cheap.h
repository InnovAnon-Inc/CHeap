#ifndef _CHEAP_H_
#define _CHEAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#include <glitter.h>
#include <array.h>

typedef __attribute__ ((nonnull (1, 2), warn_unused_result))
int (*cheap_cmp_t) (void const *restrict a, void const *restrict b) ;

typedef struct {
   array_t *restrict array;
   size_t n;
   cheap_cmp_t cmp;
} cheap_t;

void init_cheap (cheap_t *restrict cheap, array_t *restrict array)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

int alloc_cheap (cheap_t *restrict cheap, array_t *restrict array)
__attribute__ ((leaf, nonnull (1, 2), nothrow, warn_unused_result)) ;

void free_cheap (cheap_t *restrict cheap, array_t *restrict array)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

size_t get_parent (size_t i)
__attribute__ ((const, leaf, nothrow, warn_unused_result)) ;

bool has_parent (size_t i)
__attribute__ ((const, leaf, nothrow, warn_unused_result)) ;

size_t get_left_child (size_t i)
__attribute__ ((const, leaf, nothrow, warn_unused_result)) ;

bool has_left_child (cheap_t const *restrict cheap, size_t i)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

size_t get_right_child (size_t i)
__attribute__ ((const, leaf, nothrow, warn_unused_result)) ;

bool has_right_child (cheap_t const *restrict cheap, size_t i)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

bool has_child (cheap_t const *restrict cheap, size_t i)
__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result)) ;

int cheap_cmp (cheap_t const *restrict cheap, size_t i, size_t j)
__attribute__ ((pure, leaf, nonnull (1), nothrow, warn_unused_result)) ;

/* O (log n), Omega (1) */
void cheapify_up (cheap_t const *restrict cheap, size_t i)
__attribute__ ((nonnull (1), nothrow)) ;

void insert_cheap (cheap_t *restrict cheap, void const *restrict e)
__attribute__ ((nonnull (1, 2), nothrow)) ;

/* O (n log n) ? */
void inserts_cheap (cheap_t *restrict cheap,
   void const *restrict e, size_t n)
__attribute__ ((nonnull (1, 2), nothrow)) ;

void cheapify_down (cheap_t const *restrict cheap, size_t i)
__attribute__ ((nonnull (1), nothrow)) ;

void remove_cheap (cheap_t *restrict cheap, void *restrict e)
__attribute__ ((nonnull (1, 2), nothrow)) ;

void removes_cheap (cheap_t *restrict cheap,
   void *restrict e, size_t n)
__attribute__ ((nonnull (1, 2), nothrow)) ;

#ifdef __cplusplus
}
#endif

#endif /* _CHEAP_H_ */