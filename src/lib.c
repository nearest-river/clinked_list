#include "lib.h"
#include "mem.c"
#include "prelude.h"

typedef LinkedList Self;


inline
Self ll_new(const usize BYTES_PER_ELEMENT,const LinkedListVTable vtable) {
  Self self={
    .vtable=vtable,
    .BYTES_PER_ELEMENT=BYTES_PER_ELEMENT,
    .len=0,
    .head=NULL,
    .tail=NULL
  };

  return self;
}

void ll_drop(Self* self) {
  panic("todo");
}

usize ll_len(const Self* self) {
  return self->len;
}

bool ll_is_empty(const Self* self) {
  return self->len==0;
}

void ll_push_back(Self* self,void* element) {
  Node* node=_node_new(element,self->BYTES_PER_ELEMENT,self->tail,NULL);

  if(self->tail==NULL) {
    self->head=node;
  } else {
    self->tail->next=node;
  }
  self->tail=node;
  self->len++;
}

void ll_push_front(Self* self,void* element) {
  Node* node=_node_new(element,self->BYTES_PER_ELEMENT,self->head,NULL);

  if(self->head==NULL) {
    self->tail=node;
  } else {
    self->head->prev=node;
  }

  self->head=node;
  self->len++;
}

void ll_append(Self* self,Self* other) {
  if(self->tail==NULL) {
    _mem_swap(self,other);
    return;
  }

  if(other->head==NULL) return;
  Node* other_head=_mem_take((void**)&other->head);

  self->tail->next=other_head;
  other_head->prev=self->tail;

  self->tail=_mem_take((void**)&other->tail);

  self->len+=other->len;
  other->len=0;
}

void ll_clear(Self* self) {
  Self ll={
    .len=self->len,
    .tail=self->tail,
    .head=self->head,
    .vtable=self->vtable,
    .BYTES_PER_ELEMENT=self->BYTES_PER_ELEMENT
  };
  self->head=NULL;
  self->tail=NULL;
  self->len=0;
  return ll_drop(&ll);
}

void ll_iter(const Self* self,void (*f)(void*)) {
  Node* current=self->head;
  while(current!=NULL) {
    f(_node_data(current));
    current=current->next;
  }
}

bool ll_contains(const Self* self,void* element) {
  Node* current=self->head;
  const ComparisonFn compare=self->vtable.compare;
  while(current!=NULL) {
    if(compare(element,_node_data(current))==0) {
      return true;
    }
    current=current->next;
  }

  return false;
}

inline
void* ll_front(const Self* self) {
  return _node_data(self->head);
}

inline
void* ll_back(const Self* self) {
  return _node_data(self->tail);
}










