#include "mem.h"

/// thanks for choosing the holy version of malloc
inline
void* _mem_alloc(usize size) {
  void* ptr=malloc(size);
  if(ptr==NULL) panic("Could'nt allocate memory.\nmalloc returned `NULL`\n");

  return ptr;
}

inline
Node* _node_new(void* data,const usize BYTES_PER_ELEMENT,Node* prev,Node* next) {
  const usize size=sizeof(Node)+BYTES_PER_ELEMENT;
  void* data_ptr=_mem_alloc(MIN_NON_ZERO_CAP(size));
  Node* node=(Node*)(data_ptr+BYTES_PER_ELEMENT);

  // the data is actually stored before the node's memory as c doesn't support generics.
  // this should be a secret between us.. the CIA is always looking for it.
  memmove(data_ptr,data,BYTES_PER_ELEMENT);

  node->next=next;
  node->prev=prev;
  return node;
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

inline
void _ll_unlink_node(LinkedList* self,Node* node) {
  if(node->prev!=NULL) {
    node->prev->next=node->next;
  } else {
    self->head=node->next;
  }

  if(node->next!=NULL) {
    node->next->prev=node->prev;
  } else {
    self->tail=node->prev;
  }

  self->len--;
}





