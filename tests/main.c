#include <stdio.h>
#include "../src/lib.h"

void i32_clone(i32* dest,i32* src);
int i32_compare(const i32* self,const i32* rhs);
void print(void* element);

static const LinkedListVTable LL_I32_VTABLE={
  .clone=(Clone)i32_clone,
  .compare=(ComparisonFn)i32_compare,
  .destructor=NULL
};


int main() {
  LinkedList ll=ll_new(sizeof(i32),LL_I32_VTABLE);
  
  for(i32 i=0;i<10;i++) {
    ll_push_back(&ll,&i);
  }

  ll_iter(&ll,print);
  printf("\n");
  return 0;
}

inline
void i32_clone(i32* dest,i32* src) {
  *src=*dest;
}

inline
int i32_compare(const i32* self,const i32* rhs) {
  i32 a=*self;
  i32 b=*rhs;
  return a==b?0:a<b?-1:1;
}

inline
void print(void* element) {
  printf("%d ",*(i32*)element);
}








