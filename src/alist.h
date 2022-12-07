#ifndef ALIST_H
#define ALIST_H

#include <assert.h>
#include <stdlib.h>

typedef struct alist_t {
    size_t size;
    size_t capacity;
    void **data_array;
} alist;

//  Initialize list structure.
//
int alist_init(alist *l);

//  De-initialize list structure.
//
void alist_destroy(alist *l);

//  Increase list's capacity.
//
int alist_expand(alist *l, size_t new_capacity);

//  Returns number of elements from list.
//
static inline size_t alist_size(alist *l) { return l->size; }

//  Returns element of index 'i' from list.
//
static inline void *alist_get(alist *l, size_t i) {
    assert(i < l->size);
    return l->data_array[i];
}

//  Set element of index 'i'.
//
static inline void alist_set(alist *l, size_t i, void *data) {
    assert(i < l->size);
    l->data_array[i] = data;
}

//  Add element in the end of the list.
//
void alist_add(alist *l, void *data);

//  Remove element from the end of the list, and
//  returns the removed element.
//
void *alist_pop(alist *l);

//  Adds element in index 'i'.
//
void alist_insert(alist *l, size_t i, void *data);

//  Removes element in index 'i', and 
//  return the removed element.
void *alist_remove(alist *l, size_t i);

#endif // ALIST_H
