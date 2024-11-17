#ifndef CLINKED_LIST_PRELUDE_H
#define CLINKED_LIST_PRELUDE_H

#include <stdlib.h>
#include <stdio.h>
#include "../include/cprimitives/src/lib.h"


#ifndef MAX
#define MAX(x,y) ((x)>(y))?(x):(y)
#endif

#define MIN_NON_ZERO_CAP(SIZE) ((SIZE)==1)?(8):((SIZE)<=1024)?4:1
#define panic(...) { fprintf(stderr,__VA_ARGS__);exit(1); }
#define inline_always __inline __attribute__ ((__always_inline__))



#endif
