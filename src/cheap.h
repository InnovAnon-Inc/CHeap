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
   array_t array;
   size_t n;
   cheap_cmp_t cmp;
} cheap_t;

size_t cheapsz (size_t esz, size_t n)
__attribute__ ((const, leaf, nothrow, warn_unused_result)) ;

size_t cheapsz2 (cheap_t const *restrict cheap)
__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result)) ;

cheap_t *ez_alloc_cheap (size_t esz, size_t maxn, cheap_cmp_t cmp)
__attribute__ ((/*alloc_align (1),*/ /*alloc_size (1, 2),*/ /*malloc,*/
	nonnull (3), nothrow, warn_unused_result)) ;

void ez_free_cheap (cheap_t *restrict cheap)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void init_cheap (cheap_t *restrict cheap,
   void *restrict data, size_t esz, size_t n, cheap_cmp_t cmp)
__attribute__ ((leaf, nonnull (1, 2, 5), nothrow)) ;

int alloc_cheap (cheap_t *restrict cheap,
   size_t esz, size_t n, cheap_cmp_t cmp)
__attribute__ ((leaf, nonnull (1, 4), nothrow, warn_unused_result)) ;

void free_cheap (cheap_t const *restrict cheap)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

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

void build_cheap (cheap_t const *restrict cheap)
__attribute__ ((nonnull (1), nothrow)) ;

bool isfull_cheap (cheap_t const *restrict cheap)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

bool isempty_cheap (cheap_t const *restrict cheap)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

size_t remaining_space_cheap (cheap_t const *restrict cheap)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

size_t indexOf_cheap (cheap_t const *restrict cheap,
	void const *restrict e)
__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result)) ;

bool contains_cheap (cheap_t const *restrict cheap,
	void const *restrict e)
__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result)) ;

ssize_t indexOf_cheap_chk (cheap_t const *restrict cheap,
   void const *restrict e)
__attribute__ ((nonnull (1, 2), nothrow, pure, warn_unused_result)) ;

void *index_cheap (cheap_t const *restrict cheap, size_t i)
__attribute__ ((leaf, nonnull (1), nothrow, pure, returns_nonnull, warn_unused_result)) ;

TODO (isEdge (i))
TODO (isEdge (e))
TODO (getEdges ())
TODO (isLeaf (i))
TODO (isLeaf (e))
TODO (getLeafs ())
TODO (getPath (i))
TODO (getPath (e))
TODO (getDepth (i))
TODO (getDepth (e))
TODO (depth-first ())
TODO (breadth-first ())

#ifdef __cplusplus
}
#endif

#endif /* _CHEAP_H_ */