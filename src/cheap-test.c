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

__attribute__ ((nothrow, warn_unused_result))
int main (void) {
   cheap_t darr;
   time_t t;
   size_t ntest = 1000;
   size_t testi;
   int nums[100];

   t = time (NULL);
   srand ((unsigned int) t);

   TODO (something)

   fputs ("success", stderr); fflush (stderr);

   return EXIT_SUCCESS;
}
