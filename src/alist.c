#include "alist.h"

#include <assert.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 16

int alist_init(alist *l) {
    // Allocate initial buffer
    l->data_array = (void **) malloc(sizeof(void *)*INITIAL_CAPACITY); 
    if (l->data_array == NULL) {
        return 1;
    }

    l->capacity = INITIAL_CAPACITY;
    l->size = 0;

    return 0;
}

int alist_expand(alist *l, size_t new_capacity) {
    if (new_capacity <= l->capacity) {
        return 0;
    }

    // Realloc data buffer
    void **new_array = (void **) realloc(l->data_array, sizeof(void *)*new_capacity); 
    if (new_array == NULL) {
        return 1;
    }

    l->data_array = new_array;
    l->capacity = new_capacity;

    return 0;
}

void * alist_get(alist *l, size_t i) {
    assert(i < l->size);
    return l->data_array[i];
}

void alist_add(alist *l, void *data) {
    if (l->size >= l->capacity) {
        // Double the capacity when needed
        alist_expand(l, l->capacity << 1);
    }

    l->data_array[l->size++] = data;
}

void * alist_pop(alist *l) {
    assert (l->size > 0);
    return l->data_array[--l->size];
}

void alist_destroy(alist *l) {
    free(l->data_array);
}
