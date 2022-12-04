#include "list.h"

#define INITIAL_CAPACITY 16

// Inline functions
size_t list_size(list *l);

void list_add(list *l, void *data);

void * list_get(list *l, size_t i);
void * list_pop(list *l);

int list_init(list *l) {
    // Allocate initial buffer
    l->data_array = (void **) malloc(sizeof(void *)*INITIAL_CAPACITY); 
    if (l->data_array == NULL) {
        return 1;
    }

    l->capacity = INITIAL_CAPACITY;
    l->size = 0;

    return 0;
}

int list_expand(list *l, size_t new_capacity) {
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

void list_destroy(list *l) {
    free(l->data_array);
}
