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

inline_always
void* ll_node_element(const Node* self,const usize BYTES_PER_ELEMENT) {
  return self==NULL?NULL:((void*)self)-BYTES_PER_ELEMENT;
}

inline_always
void* ll_node_into_element(const Node* self,const usize BYTES_PER_ELEMENT) {
  void* element=ll_node_element(self,BYTES_PER_ELEMENT);
  return realloc(element,BYTES_PER_ELEMENT);
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
    .len=(usize)_mem_take((void**)&self->len),
    .tail=_mem_take((void**)&self->tail),
    .head=_mem_take((void**)&self->head),
    .vtable=self->vtable,
    .BYTES_PER_ELEMENT=self->BYTES_PER_ELEMENT
  };
  return ll_drop(&ll);
}

void ll_iter(const Self* self,void (*f)(void*)) {
  Node* current=self->head;
  while(current!=NULL) {
    f(ll_node_element(current,self->BYTES_PER_ELEMENT));
    current=current->next;
  }
}

bool ll_contains(const Self* self,void* element) {
  Node* current=self->head;
  const ComparisonFn compare=self->vtable.compare;
  while(current!=NULL) {
    if(compare(element,ll_node_element(current,self->BYTES_PER_ELEMENT))==0) {
      return true;
    }
    current=current->next;
  }

  return false;
}

inline
void* ll_front(const Self* self) {
  return ll_node_element(self->head,self->BYTES_PER_ELEMENT);
}

inline
void* ll_back(const Self* self) {
  return ll_node_element(self->tail,self->BYTES_PER_ELEMENT);
}

Node* ll_pop_front_node(Self* self) {
  if(self->head==NULL) return NULL;
  Node* node=self->head;
  self->head=node->next;

  if(self->head==NULL) {
    self->tail=NULL;
  } else {
    self->head->prev=NULL;
  }

  self->len--;
  return node;
}

Node* ll_pop_back_node(Self* self) {
  if(self->tail==NULL) return NULL;
  Node* node=self->tail;
  self->tail=node->prev;

  if(self->tail==NULL) {
    self->head=NULL;
  } else {
    self->tail->next=NULL;
  }

  self->len--;
  return node;
}

void* ll_pop_back(Self* self) {
  return ll_node_into_element(ll_pop_back_node(self),self->BYTES_PER_ELEMENT);
}

void* ll_pop_front(Self* self) {
  return ll_node_into_element(ll_pop_front_node(self),self->BYTES_PER_ELEMENT);
}






















