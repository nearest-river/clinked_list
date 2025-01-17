#ifndef CLINKED_LIST_H
#define CLINKED_LIST_H
#include "prelude.h"
#include "default_impl.h"

/** LinkedList Node. (data isn't directly added to prevent indirection.) */
typedef struct Node {
  struct Node* prev;
  struct Node* next;
} Node;

typedef struct {
  Node* head;
  Node* tail;
  usize len;
  const usize BYTES_PER_ELEMENT;
  const LinkedListVTable vtable;
} LinkedList;



#ifdef _cplusplus
extern "C" {
#endif

LinkedList ll_new(const usize BYTES_PER_ELEMENT,const LinkedListVTable vtable);

LinkedList ll_from_vec(Vec vec);

LinkedList ll_from_arr(const void* arr,const usize BYTES_PER_ELEMENT,const usize len,const LinkedListVTable vtable);

LinkedList ll_clone_from_vec(Vec* vec);

LinkedList ll_clone_from_slice(void* arr,const usize BYTES_PER_ELEMENT,const usize len,const LinkedListVTable vtable);

void ll_drop(LinkedList* self);

usize ll_len(const LinkedList* self);

bool ll_is_empty(const LinkedList* self);

void ll_push_back(LinkedList* self,const void* element);

void ll_push_front(LinkedList* self,const void* element);

void ll_append(LinkedList* self,LinkedList* other);

void ll_clear(LinkedList* self);

void ll_for_each(const LinkedList* self,void (*f)(void*));

bool ll_contains(const LinkedList* self,void* element);

void* ll_front(const LinkedList* self);

void* ll_back(const LinkedList* self);

Node* ll_pop_front_node(LinkedList* self);

Node* ll_pop_back_node(LinkedList* self);

void* ll_pop_back(LinkedList* self);

void* ll_pop_front(LinkedList* self);

void* ll_remove(LinkedList* self,usize idx);

void ll_insert(LinkedList* self,usize idx,void* element);

LinkedList ll_split_off(LinkedList* self,usize at);

void ll_retain(LinkedList* self,PredicateFn f); 

Vec ll_into_vec(LinkedList self);

Vec ll_to_vec(LinkedList* self);

bool ll_remove_element(LinkedList* self,const void* element);

bool ll_insert_after(LinkedList* self,void* element,void* target);

bool ll_insert_before(LinkedList* self,void* element,void* target);

void* ll_remove_if(LinkedList* self,PredicateFn f);

void* ll_remove_after(LinkedList* self,void* target);

void* ll_remove_before(LinkedList* self,void* target);

void ll_reverse(LinkedList* self);


//////////
// Node //
//////////

void* ll_node_element(const Node* self,const usize BYTES_PER_ELEMENT);

void* ll_node_into_element(const Node* self,const usize BYTES_PER_ELEMENT);

void ll_node_drop(Node* self,Destructor drop,const usize BYTES_PER_ELEMENT);



#ifdef _cplusplus
}
#endif

#endif
