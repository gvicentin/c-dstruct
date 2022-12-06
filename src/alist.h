#ifndef ALIST_H
#define ALIST_H

#include <stdlib.h>

typedef struct alist_t {
  size_t size;
  size_t capacity;
  void **data_array;
} alist;

//  Initialize list structure.
//
int alist_init(alist *l);

//  Increase list's capacity.
//
int alist_expand(alist *l, size_t new_capacity);

//  Returns number of elements from list.
//
static inline size_t alist_size(alist *l) { return l->size; }

//  Returns element of indice 'i' from list.
//
void *alist_get(alist *l, size_t i);

//  Add element in the end of the list.
//
void alist_add(alist *l, void *data);

//  Remove element from the end of the list, and
//  returns the removed element.
//
void *alist_pop(alist *l);

//  De-initialize list structure.
//
void alist_destroy(alist *l);

#endif // ALIST_H
