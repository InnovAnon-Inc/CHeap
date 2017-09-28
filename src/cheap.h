#ifndef _CHEAP_H_
#define _CHEAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#include <glitter.h>

typedef struct {
   void *restrict data;
   size_t esz;
   size_t n;
   size_t maxn;
} cheap_t;

#ifdef __cplusplus
}
#endif

#endif /* _CHEAP_H_ */