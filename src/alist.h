#ifndef ALIST_H
#define ALIST_H

#include <stdlib.h>

typedef struct alist_ {
    size_t size;
    size_t capacity;
    void **data_array;
} alist;

/**
 *  Initialize list structure.
 */
int alist_init(alist *l);

/**
 *  Increase list's capacity.
 */
int alist_expand(alist *l, size_t new_capacity);

/**
 * Returns number of elements from list.
 */
static inline size_t alist_size(alist *l) {
    return l->size;
}

/**
 * Returns element of indice 'i' from list.
 */
void * alist_get(alist *l, size_t i);

void alist_add(alist *l, void *data);

void * alist_pop(alist *l);

void alist_destroy(alist *l);

#endif // ALIST_H
