#include <stdio.h>
#include "../src/lib.h"

void print(void* element);
void ll_print(LinkedList* self);
bool is_even(i32* x);



int main(int argc,const char** argv) {
  LinkedList ll=ll_new(sizeof(i32),LL_VTABLE_I32);
  
  for(i32 i=0;i<10;i++) {
    ll_push_back(&ll,&i);
  }

  ll_retain(&ll,(PredicateFn)is_even);

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
void print(void* element) {
  printf("%d ",*(i32*)element);
}

inline
bool is_even(i32* x) {
  return !(*x & 1);
}






