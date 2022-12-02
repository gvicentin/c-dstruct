#ifndef LIST_H
#define LIST_H

#include <assert.h>
#include <stdlib.h>

typedef struct list_ {
    size_t size;
    size_t capacity;
    void **data_array;
} list;

int list_create(list *l);

int list_expand(list *l, size_t new_capacity);

extern inline size_t list_size(list *l) {
    return l->size;
}

extern inline void * list_get(list *l, size_t i) {
    assert(i < l->size);
    return l->data_array;
}

extern inline void list_add(list *l, void *data) {
    if (l->size >= l->capacity) {
        // Double the capacity when needed
        list_expand(l, l->capacity << 1);
    }

    l->data_array[l->size++] = data;
}

extern inline void * list_pop(list *l) {
    assert (l->size > 0);
    return l->data_array[--l->size];
}

void list_destroy(list *l);

#endif // LIST_H
