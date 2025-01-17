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
  not_null(arr);
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
  not_null(self);
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

bool ll_remove_element(Self* self,const void* element) {
  not_null2(self,element);
  const ComparisonFn cmp=self->vtable.compare;
  if(cmp==NULL) {
    panic("LinkedList doesn't implement `ComparisonFn`");
  }

  Node* cursor=self->head;
  const usize len=self->len;
  const usize BYTES_PER_ELEMENT=self->BYTES_PER_ELEMENT;
  for(usize i=0;i<len;i++) {
    void* elem=ll_node_element(cursor,BYTES_PER_ELEMENT);
    if(cmp(element,elem)==0) {
      _ll_unlink_node(self,cursor);
      ll_node_drop(cursor,self->vtable.destructor,BYTES_PER_ELEMENT);
      return true;
    }

    cursor=cursor->next;
  }

  return false;
}

bool ll_insert_after(Self* self,void* element,void* target) {
  not_null2(self,element);
  const ComparisonFn cmp=self->vtable.compare;
  if(cmp==NULL) {
    panic("LinkedList doesn't implement `ComparisonFn`");
  }

  const usize len=self->len;
  const usize BYTES_PER_ELEMENT=self->BYTES_PER_ELEMENT;
  Node* cursor=self->head;
  for(usize i=0;i<len;i++,cursor=cursor->next) {
    void* elem=ll_node_element(cursor,BYTES_PER_ELEMENT);
    if(cmp(target,elem)!=0) {
      continue;
    }

    Node* node=_node_new(element,self->BYTES_PER_ELEMENT,cursor,cursor->next);
    if(cursor->next!=NULL) {
      cursor->next->prev=node;
    }

    cursor->next=node;
    self->len++;
    return true;
  }

  return false;
}

bool ll_insert_before(Self* self,void* element,void* target) {
  not_null2(self,element);
  const ComparisonFn cmp=self->vtable.compare;
  if(cmp==NULL) {
    panic("LinkedList doesn't implement `ComparisonFn`");
  }

  const usize len=self->len;
  const usize BYTES_PER_ELEMENT=self->BYTES_PER_ELEMENT;
  Node* cursor=self->tail;
  for(usize i=0;i<len;i++,cursor=cursor->prev) {
    void* elem=ll_node_element(cursor,BYTES_PER_ELEMENT);
    if(cmp(target,elem)!=0) {
      continue;
    }

    Node* node=_node_new(element,self->BYTES_PER_ELEMENT,cursor->prev,cursor);
    if(cursor->prev!=NULL) {
      cursor->prev->next=node;
    }
    cursor->prev=node;
    self->len++;
    return true;
  }

  return false;
}

void* ll_remove_if(Self* self,PredicateFn f) {
  not_null(self);

  const usize BYTES_PER_ELEMENT=self->BYTES_PER_ELEMENT;
  for(Node* cursor=self->head;cursor;cursor=cursor->next) {
    void* element=ll_node_element(cursor,BYTES_PER_ELEMENT);
    if(!f(element)) {
      continue;
    }

    _ll_unlink_node(self,cursor);
    // equivalent to ll_node_into_element()
    return realloc(element,BYTES_PER_ELEMENT);
  }

  return NULL;
}

void* ll_remove_after(Self* self,void* target) {
  not_null2(self,target);
  const ComparisonFn cmp=self->vtable.compare;
  if(cmp==NULL) {
    panic("LinkedList doesn't implement `ComparisonFn`");
  }

  const usize BYTES_PER_ELEMENT=self->BYTES_PER_ELEMENT;
  for(Node* cursor=self->head;cursor;cursor=cursor->next) {
    void* element=ll_node_element(cursor,BYTES_PER_ELEMENT);
    if(cmp(element,target)!=0) {
      continue;
    }

    Node* next=cursor->next;
    if(!next) {
      return NULL;
    }

    _ll_unlink_node(self,next);
    return ll_node_into_element(next,BYTES_PER_ELEMENT);
  }

  return NULL;
}

void* ll_remove_before(Self* self,void* target) {
  not_null2(self,target);
  const ComparisonFn cmp=self->vtable.compare;
  if(cmp==NULL) {
    panic("LinkedList doesn't implement `ComparisonFn`");
  }

  const usize BYTES_PER_ELEMENT=self->BYTES_PER_ELEMENT;
  for(Node* cursor=self->head;cursor;cursor=cursor->next) {
    void* element=ll_node_element(cursor,BYTES_PER_ELEMENT);
    if(cmp(element,target)!=0) {
      continue;
    }

    Node* prev=cursor->prev;
    if(!prev) {
      return NULL;
    }

    _ll_unlink_node(self,prev);
    return ll_node_into_element(prev,BYTES_PER_ELEMENT);
  }

  return NULL;
}

void ll_reverse(Self* self) {
  not_null(self);

  Node* temp=NULL;
  Node* head=self->head;
  for(Node* cursor=head;cursor;cursor=cursor->prev) {
    temp=cursor->prev;
    cursor->prev=cursor->next;
    cursor->next=temp;
  }

  if(temp) {
    self->head=temp->prev;
  }

  self->tail=head;
}











