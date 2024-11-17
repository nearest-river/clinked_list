#ifndef CLINKED_LIST_MEM_H
#define CLINKED_LIST_MEM_H
#include "lib.h"
#include "prelude.h"
#include <string.h>


#ifdef _cplusplus 
extern "C" {
#endif

/// thanks for choosing the holy version of malloc
inline
void* _mem_alloc(usize size) {
  void* ptr=malloc(size);
  if(ptr==NULL) panic("Could'nt allocate memory.\nmalloc returned `NULL`\n");

  return ptr;
}

inline
void _ll_drop_in_place(void* ptr,Destructor destructor) {
  if(!destructor) return;
  destructor(ptr);
}

inline
Node* _node_new(void* data,const usize BYTES_PER_ELEMENT,Node* prev,Node* next) {
  const usize size=sizeof(Node)+BYTES_PER_ELEMENT;
  Node* node=(struct Node*)_mem_alloc(MIN_NON_ZERO_CAP(size));

  // the data is actually stored after the node's memory as c doesn't support generics.
  // this should be a secret between us.. the CIA is always looking for it.
  memmove((void*)(node+1),data,BYTES_PER_ELEMENT);

  node->next=next;
  node->prev=prev;
  return node;
}

/// be careful.. the CIA might be watching
inline_always
void* _node_data(Node* self) {
  return self==NULL?NULL:(self+1);
}


inline_always
void _mem_swap(LinkedList* self,LinkedList* other) {
  usize size=sizeof(LinkedList);
  u8* a=(u8*)self,*b=(u8*)other;
  while(size--) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
    a++;
    b++;
  }
}

inline_always
void* _mem_take(void** self) {
  void* ptr=*self;
  *self=NULL;
  return ptr;
}










#ifdef _cplusplus
}
#endif

#endif
