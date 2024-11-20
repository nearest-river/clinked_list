#ifndef CLINKED_LIST_H
#define CLINKED_LIST_H
#include "prelude.h"

/** LinkedList Node. (data isn't directly added to prevent indirection.) */
typedef struct Node {
  struct Node* prev;
  struct Node* next;
} Node;

/**
 * A function that frees the resources held by `self`.
 */
typedef void (*Destructor)(void*);

/**
 * A function that clones from `src` to `dest` without forgetting about the resources held by `self`.
 * 
 * * Params: `(void* dest,void* src)`.
 */
typedef void (*Clone)(const void*,const void*);


typedef int (*ComparisonFn)(const void*,const void*);


/**
 * This virtual table keeping track of the resources held by the `LinkedList`.
 */
typedef struct {
  Destructor destructor;
  Clone clone;
  ComparisonFn compare;
} LinkedListVTable;

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

void ll_drop(LinkedList* self);

usize ll_len(const LinkedList* self);

bool ll_is_empty(const LinkedList* self);

void ll_push_back(LinkedList* self,void* element);

void ll_push_front(LinkedList* self,void* element);

void ll_append(LinkedList* self,LinkedList* other);

void ll_clear(LinkedList* self);

void ll_iter(const LinkedList* self,void (*f)(void*));

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



//////////
// Node //
//////////

void* ll_node_element(const Node* self,const usize BYTES_PER_ELEMENT);

void* ll_node_into_element(const Node* self,const usize BYTES_PER_ELEMENT);





#ifdef _cplusplus
}
#endif

#endif
