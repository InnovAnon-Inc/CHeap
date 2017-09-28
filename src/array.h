#ifndef _ARRAY_H_
#define _ARRAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#include <glitter.h>

typedef struct {
   void *restrict data;
   size_t esz;
   size_t n;
} array_t;

void *index_array (array_t const *restrict array, size_t i)
__attribute__ ((leaf, nonnull (1), pure, returns_nonnull, warn_unused_result)) ;

void init_array (array_t *restrict array,
	void *restrict data, size_t esz, size_t n)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

int alloc_array (array_t *restrict array,
	size_t esz, size_t n)
__attribute__ ((nonnull (1), nothrow, warn_unused_result)) ;

void get_array (array_t const *restrict array, size_t i,
   void *restrict e)
__attribute__ ((nonnull (1, 3), nothrow)) ;

void set_array (array_t const *restrict array, size_t i,
	void const *restrict e)
__attribute__ ((nonnull (1, 3), nothrow)) ;

void free_array (array_t const *restrict array)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

#ifdef __cplusplus
}
#endif

#endif /* _ARRAY_H_ */