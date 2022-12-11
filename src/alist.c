#include "alist.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16

int AListInit(AList *l) {
    // Allocate initial buffer
    l->dataArray = (void **)malloc(sizeof(void *) * INITIAL_CAPACITY);
    if (l->dataArray == NULL) {
        return 1;
    }

    l->capacity = INITIAL_CAPACITY;
    l->size = 0;

    return 0;
}

void AListDestroy(AList *l) { free(l->dataArray); }

int AListExpand(AList *l, size_t newCapacity) {
    if (newCapacity <= l->capacity) {
        return 0;
    }

    // Realloc data buffer
    void **newArray =
        (void **)realloc(l->dataArray, sizeof(void *) * newCapacity);
    if (newArray == NULL) {
        return 1;
    }

    l->dataArray = newArray;
    l->capacity = newCapacity;

    return 0;
}

void AListAdd(AList *l, void *data) {
    if (l->size >= l->capacity) {
        // Double the capacity when needed
        AListExpand(l, l->capacity << 1);
    }

    l->dataArray[l->size++] = data;
}

void AListAddAll(AList *l, AList *r) {
    if (l->size + r->size >= l->capacity) {
        AListExpand(l, l->capacity + r->size);
    }

    for (size_t i = 0; i < r->size; ++i) {
        l->dataArray[l->size + i] = r->dataArray[i];
    }
    l->size += r->size;
}

void *AListPop(AList *l) {
    assert(l->size > 0);
    return l->dataArray[--l->size];
}

void AListInsert(AList *l, size_t i, void *data) {
    assert(i <= l->size);

    if (l->size >= l->capacity) {
        // Double the capacity when needed
        AListExpand(l, l->capacity << 1);
    }

    // shift array to the right and add element
    memmove(l->dataArray + i + 1, l->dataArray + i,
            (l->size - i) * sizeof(void *));
    l->dataArray[i] = data;
    ++l->size;
}

void AListInsertAll(AList *l, AList *r, size_t i) {
    assert(i <= l->size);

    if (l->size + r->size >= l->capacity) {
        AListExpand(l, l->capacity + r->size);
    }

    // shift array to the ridht and add all elements
    memmove(l->dataArray + i + r->size, l->dataArray + i,
            (l->size - i) * sizeof(void *));
    for (size_t j = 0; j < r->size; ++j) {
        l->dataArray[i + j] = r->dataArray[j];
    }
    l->size += r->size;
}

void *AListRemove(AList *l, size_t i) {
    assert(i < l->size);

    // shift array to left and remove element
    void *data = l->dataArray[i];
    memmove(l->dataArray + i, l->dataArray + i + 1,
            (l->size - i) * sizeof(void *));
    --l->size;

    return data;
}
