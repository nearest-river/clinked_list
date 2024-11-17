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
typedef void (*Cloner)(const void*,const void*);


typedef int (*ComparisonFn)(const void*,const void*);


/**
 * This virtual table keeping track of the resources held by the `LinkedList`.
 */
typedef struct {
  const Destructor destructor;
  const Cloner cloner;
  const ComparisonFn compare;
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







#ifdef _cplusplus
}
#endif

#endif
