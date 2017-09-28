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
   array_t *restrict data;
   size_t n;
   cheap_cmp_t cmp;
} cheap_t;

void init_cheap (cheap_t *restrict cheap, array_t *restrict array)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

int alloc_cheap (cheap_t *restrict cheap, array_t *restrict array)
__attribute__ ((leaf, nonnull (1, 2), nothrow, warn_unused_result)) ;

void free_cheap (cheap_t *restrict cheap, array_t *restrict array)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void insert_cheap (cheap_t *restrict cheap, void *restrict e) ;
void remove_cheap (cheap_t *restrict cheap, void *restrict e) ;

#ifdef __cplusplus
}
#endif

#endif /* _CHEAP_H_ */