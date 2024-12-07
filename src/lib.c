#include "lib.h"
#include "default_impl.h"
#include "mem.h"
#include <string.h>


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

inline
Self ll_from_vec(Vec vec) {
  const LinkedListVTable vtable={
    // SAFETY: removing the destructor from `vec` to prevent `drop`
    .destructor=_mem_take((void**)&vec.vtable.destructor),
    .clone=vec.vtable.cloner,
    .compare=NULL // todo
  };

  Self self=ll_from_arr(vec.ptr,vec.BYTES_PER_ELEMENT,vec.len,vtable);
  drop_vec(&vec);

  return self;
}

Self ll_from_arr(const void* arr,const usize BYTES_PER_ELEMENT,const usize len,const LinkedListVTable vtable) {
  Self self=ll_new(BYTES_PER_ELEMENT,vtable);

  for(usize i=0;i<len;i++) {
    ll_push_back(&self,arr);
    arr+=BYTES_PER_ELEMENT;
  }

  return self;
}

inline
Self ll_clone_from_vec(Vec* vec) {
  LinkedListVTable vtable={
    .destructor=vec->vtable.destructor,
    .clone=vec->vtable.cloner,
    .compare=NULL,
  };

  return ll_clone_from_slice(vec->ptr,vec->BYTES_PER_ELEMENT,vec->len,vtable);
}

Self ll_clone_from_slice(void* arr,const usize BYTES_PER_ELEMENT,const usize len,const LinkedListVTable vtable) {
  Self self=ll_new(BYTES_PER_ELEMENT,vtable);

  for(usize i=0;i<len;i++) {
    ll_push_back(&self,arr);
    void* element=ll_node_element(self.tail,self.BYTES_PER_ELEMENT);
    vtable.clone(element,(void*)arr);

    arr+=BYTES_PER_ELEMENT;
  }

  return self;
}

void ll_drop(Self* self) {
  if(!self) return;
  const usize len=self->len;
  Node* cursor=self->tail;

  for(usize i=0;i<len;i++) {
    Node* binding=cursor;
    cursor=cursor->prev;
    ll_node_drop(binding,self->vtable.destructor,self->BYTES_PER_ELEMENT);
  }

  self->head=NULL;
  self->tail=NULL;
  self->len=0;
}

inline
void ll_node_drop(Node* self,Destructor drop,const usize BYTES_PER_ELEMENT) {
  if(!self) return;
  void* binding=ll_node_element(self,BYTES_PER_ELEMENT);

  if(drop!=NULL) drop(binding);
  free(binding);
}

inline_always
usize ll_len(const Self* self) {
  not_null(self);
  return self->len;
}

inline_always
bool ll_is_empty(const Self* self) {
  not_null(self);
  return self->len==0;
}

inline_always
void* ll_node_element(const Node* self,const usize BYTES_PER_ELEMENT) {
  return self==NULL?NULL:((void*)self)-BYTES_PER_ELEMENT;
}

inline_always
void* ll_node_into_element(const Node* self,const usize BYTES_PER_ELEMENT) {
  if(self==NULL) return NULL;
  void* element=((void*)self)-BYTES_PER_ELEMENT;

  return realloc(element,BYTES_PER_ELEMENT);
}

inline
void ll_push_back(Self* self,const void* element) {
  not_null2(self,element);
  Node* node=_node_new(element,self->BYTES_PER_ELEMENT,self->tail,NULL);

  if(self->tail==NULL) {
    self->head=node;
  } else {
    self->tail->next=node;
  }
  self->tail=node;
  self->len++;
}

inline
void ll_push_front(Self* self,const void* element) {
  not_null2(self,element);
  Node* node=_node_new(element,self->BYTES_PER_ELEMENT,NULL,self->head);

  if(self->head==NULL) {
    self->tail=node;
  } else {
    self->head->prev=node;
  }

  self->head=node;
  self->len++;
}

void ll_append(Self* self,Self* other) {
  not_null2(self,other);
  if(self->tail==NULL) {
    _mem_swap(self,other);
    return;
  }

  if(other->head==NULL) return;
  Node* other_head=_mem_take((void**)&other->head);

  self->tail->next=other_head;
  other_head->prev=self->tail;

  self->tail=_mem_take((void**)&other->tail);

  self->len+=(usize)_mem_take((void**)&other->len);
}

inline
void ll_clear(Self* self) {
  not_null(self);
  Self ll={
    .len=(usize)_mem_take((void**)&self->len),
    .tail=_mem_take((void**)&self->tail),
    .head=_mem_take((void**)&self->head),
    .vtable=self->vtable,
    .BYTES_PER_ELEMENT=self->BYTES_PER_ELEMENT
  };

  return ll_drop(&ll);
}

void ll_for_each(const Self* self,void (*f)(void*)) {
  if(f==NULL) return;
  not_null(self);

  Node* current=self->head;
  while(current!=NULL) {
    f(ll_node_element(current,self->BYTES_PER_ELEMENT));
    current=current->next;
  }
}

bool ll_contains(const Self* self,void* element) {
  not_null2(self,element);
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
  not_null(self)
  return ll_node_element(self->head,self->BYTES_PER_ELEMENT);
}

inline
void* ll_back(const Self* self) {
  not_null(self)
  return ll_node_element(self->tail,self->BYTES_PER_ELEMENT);
}

inline
Node* ll_pop_front_node(Self* self) {
  not_null(self);
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

inline
Node* ll_pop_back_node(Self* self) {
  not_null(self);
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

inline
void* ll_pop_back(Self* self) {
  return ll_node_into_element(ll_pop_back_node(self),self->BYTES_PER_ELEMENT);
}

inline
void* ll_pop_front(Self* self) {
  return ll_node_into_element(ll_pop_front_node(self),self->BYTES_PER_ELEMENT);
}

void* ll_remove(Self* self,usize idx) {
  not_null(self);
  usize len=self->len;
  if(idx>=len) return NULL;

  usize offset_from_end=len-idx-1;
  Node* cursor;
  if(idx<=offset_from_end) {
    cursor=self->head;
    usize n=idx;
    while(n--) {
      cursor=cursor->next;
    }
  } else {
    cursor=self->tail;
    usize n=offset_from_end;
    while(n--) {
      cursor=cursor->prev;
    }
  }

  _ll_unlink_node(self,cursor);
  return ll_node_into_element(cursor,self->BYTES_PER_ELEMENT);
}

void ll_insert(Self* self,usize idx,void* element) {
  not_null2(self,element);
  usize len=self->len;
  assert(idx<=len);

  if(idx==0) {
    return ll_push_front(self,element);
  } else if(idx==len) {
    return ll_push_back(self,element);
  }

  usize offset_from_end=len-idx;
  Node* cursor;
  if(idx<=offset_from_end) {
    cursor=self->head;
    usize n=idx-1;
    while(n--) {
      cursor=cursor->next;
    }
  } else {
    cursor=self->tail;
    usize n=offset_from_end;
    while(n--) {
      cursor=cursor->prev;
    }
  }

  Node* node=_node_new(element,self->BYTES_PER_ELEMENT,cursor,cursor->next);
  if(cursor->next!=NULL) {
    cursor->next->prev=node;
  }
  cursor->next=node;
  self->len++;
}

Self ll_split_off(Self* self,usize at) {
  not_null(self);
  if(self->vtable.clone==NULL) {
    panic("`self` doesn't implement `Clone`.");
  }

  usize len=self->len;
  assert(at<=len);
  LinkedList new_list=ll_new(self->BYTES_PER_ELEMENT,self->vtable);

  if(at==0) {
    new_list.len=(usize)_mem_take((void**)&self->len);
    new_list.head=_mem_take((void**)&self->head);
    new_list.tail=_mem_take((void**)&self->tail);
    goto ret;
  } else if(at==len) {
    goto ret;
  }

  Node* cursor;
  usize delta=len-at;
  if(at<=delta) {
    cursor=self->head;
    usize n=at-1;
    while(n--) {
      cursor=cursor->next;
    }
  } else {
    cursor=self->tail;
    usize n=delta;
    while(n--) {
      cursor=cursor->prev;
    }
  }

  new_list.head=_mem_take((void**)&cursor->next);
  new_list.tail=self->tail;
  new_list.len=delta;
  if(new_list.head!=NULL) {
    new_list.head->prev=NULL;
  }

  self->tail=cursor;
  self->len-=delta;
ret:
  return new_list;
}

void ll_retain(Self* self,PredicateFn f) {
  not_null(self);
  if(f==NULL) return;

  const usize len=self->len;
  Node* cursor=self->head;

  for(usize i=0;i<len;i++) {
    Node* binding=cursor;
    void* element=ll_node_element(binding,self->BYTES_PER_ELEMENT);
    cursor=cursor->next;

    if(f(element)) continue;
    _ll_unlink_node(self,binding);
    ll_node_drop(binding,self->vtable.destructor,self->BYTES_PER_ELEMENT);
  }
}

Vec ll_into_vec(Self self) {
  VecVTable vtable={
    // SAFETY: removing the destructor from self to prevent `drop`
    .destructor=_mem_take((void**)&self.vtable.destructor),
    .cloner=self.vtable.clone
  };
  Vec vec=vec_with_capacity(self.len,self.BYTES_PER_ELEMENT,vtable);

  Node* src_cursor=self.head;
  void* dest_cursor=vec.ptr;
  for(usize i=0;i<self.len;i++) {
    void* element=ll_node_element(src_cursor,self.BYTES_PER_ELEMENT);
    memmove(dest_cursor,element,self.BYTES_PER_ELEMENT);

    dest_cursor+=self.BYTES_PER_ELEMENT;
    src_cursor=src_cursor->next;
  }

  vec.len=self.len;
  ll_drop(&self);
  return vec;
}

Vec ll_to_vec(Self* self) {
  VecVTable vtable={
    .destructor=self->vtable.destructor,
    .cloner=self->vtable.clone
  };
  Vec vec=vec_with_capacity(self->len,self->BYTES_PER_ELEMENT,vtable);

  Node* src_cursor=self->head;
  void* dest_cursor=vec.ptr;
  for(usize i=0;i<self->len;i++) {
    void* element=ll_node_element(src_cursor,self->BYTES_PER_ELEMENT);
    self->vtable.clone(dest_cursor,element);

    dest_cursor+=self->BYTES_PER_ELEMENT;
    src_cursor=src_cursor->next;
  }

  return vec;
}








