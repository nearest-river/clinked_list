#ifndef CLINKED_LIST_PRELUDE_H
#define CLINKED_LIST_PRELUDE_H

#include <stdlib.h>
#include <stdio.h>
#include "../include/cprimitives/src/lib.h"


#ifndef MAX
#define MAX(x,y) ((x)>(y))?(x):(y)
#endif

#define MIN_NON_ZERO_CAP(BYTES_PER_ELEMENT) BYTES_PER_ELEMENT==1?8:BYTES_PER_ELEMENT<=1024?4:1
#define panic(...) { fprintf(stderr,__VA_ARGS__);exit(1); }



#endif
