#include <stdio.h>
#include "../src/lib.h"

void i32_clone(i32* dest,i32* src);
int i32_compare(const i32* self,const i32* rhs);
void print(void* element);
void ll_print(LinkedList* self);

static const LinkedListVTable LL_VTABLE_I32={
  .clone=(Clone)i32_clone,
  .compare=(ComparisonFn)i32_compare,
  .destructor=NULL
};


int main(int argc,const char** argv) {
  LinkedList ll=ll_new(sizeof(i32),LL_VTABLE_I32);
  
  for(i32 i=0;i<10;i++) {
    ll_push_back(&ll,&i);
  }

  printf("before drop:\n");
  ll_print(&ll);

  ll_drop(&ll);

  printf("after drop:\n");
  ll_print(&ll);

  return 0;
}

void ll_print(LinkedList* self) {
  printf("LinkedList(%lu) {\n  ",self->len);
  ll_for_each(self,print);
  printf("\n}\n");
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








