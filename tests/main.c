#include <stdio.h>
#include "../src/lib.h"

void print_ll(LinkedList* self);


int main(int argc,const char** argv) {
  LinkedList ll=ll_new(sizeof(i32),LL_VTABLE_I32);
  
  for(i32 i=0;i<10;i++) {
    ll_push_back(&ll,&i);
  }

  lambda(is_odd ,=, (i32* x),->, bool ,(*x & 1));
  ll_retain(&ll,(PredicateFn)is_odd);

  printf("before drop:\n");
  print_ll(&ll);

  ll_clear(&ll);

  printf("after drop:\n");
  print_ll(&ll);

  return 0;
}

void print_as_i32(void* element) {
  printf("%d ",*(i32*)element);
}

inline
void print_ll(LinkedList* self) {
  printf("LinkedList(%lu) {\n  ",self->len);
  ll_for_each(self,print_as_i32);
  printf("\n}\n");
}





