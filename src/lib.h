#ifndef CLINKED_LIST_H
#define CLINKED_LIST_H
#include "prelude.h"


typedef struct Node {
  void* data;
  struct Node* next;
  struct Node* prev;
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
typedef void (*Cloner)(void*,void*);

/**
 * This virtual table keeping track of the resources held by the `LinkedList`.
 */
typedef struct {
  const Destructor destructor;
  const Cloner cloner;
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
