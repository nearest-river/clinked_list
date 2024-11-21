#ifndef CLINKED_LIST_MEM_H
#define CLINKED_LIST_MEM_H
#include "lib.h"
#include "prelude.h"
#include <string.h>


#ifdef _cplusplus 
extern "C" {
#endif

void* _mem_alloc(usize size);

void _ll_drop_in_place(void* ptr,Destructor destructor);

Node* _node_new(const void* data,const usize BYTES_PER_ELEMENT,Node* prev,Node* next);

void _mem_swap(LinkedList* self,LinkedList* other);

void* _mem_take(void** self);

void _ll_unlink_node(LinkedList* self,Node* node);


#ifdef _cplusplus
}
#endif

#endif
