#include "alist.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16

int AListInit(AList *l) {
    // Allocate initial buffer
    l->elmntArray = (Elmnt *)malloc(sizeof(Elmnt) * INITIAL_CAPACITY);
    if (l->elmntArray == NULL) {
        return 1;
    }

    l->capacity = INITIAL_CAPACITY;
    l->size = 0;

    return 0;
}

void AListDestroy(AList *l) { free(l->elmntArray); }

int AListExpand(AList *l, size_t newCapacity) {
    if (newCapacity <= l->capacity) {
        return 0;
    }

    // Realloc data buffer
    Elmnt *newArray =
        (Elmnt *)realloc(l->elmntArray, sizeof(Elmnt) * newCapacity);
    if (newArray == NULL) {
        return 1;
    }

    l->elmntArray = newArray;
    l->capacity = newCapacity;

    return 0;
}

void AListAdd(AList *l, Elmnt elmnt) {
    if (l->size >= l->capacity) {
        // Double the capacity when needed
        AListExpand(l, l->capacity << 1);
    }

    l->elmntArray[l->size++] = elmnt;
}

void AListAddAll(AList *l, AList *r) {
    if (l->size + r->size >= l->capacity) {
        AListExpand(l, l->capacity + r->size);
    }

    for (size_t i = 0; i < r->size; ++i) {
        l->elmntArray[l->size + i] = r->elmntArray[i];
    }
    l->size += r->size;
}

Elmnt AListPop(AList *l) {
    assert(l->size > 0);
    return l->elmntArray[--l->size];
}

void AListInsert(AList *l, size_t i, Elmnt elmnt) {
    assert(i <= l->size);

    if (l->size >= l->capacity) {
        // Double the capacity when needed
        AListExpand(l, l->capacity << 1);
    }

    // shift array to the right and add element
    memmove(l->elmntArray + i + 1, l->elmntArray + i,
            (l->size - i) * sizeof(Elmnt));
    l->elmntArray[i] = elmnt;
    ++l->size;
}

void AListInsertAll(AList *l, AList *r, size_t i) {
    assert(i <= l->size);

    if (l->size + r->size >= l->capacity) {
        AListExpand(l, l->capacity + r->size);
    }

    // shift array to the ridht and add all elements
    memmove(l->elmntArray + i + r->size, l->elmntArray + i,
            (l->size - i) * sizeof(Elmnt));
    for (size_t j = 0; j < r->size; ++j) {
        l->elmntArray[i + j] = r->elmntArray[j];
    }
    l->size += r->size;
}

Elmnt AListRemove(AList *l, size_t i) {
    assert(i < l->size);

    // shift array to left and remove element
    Elmnt elmnt = l->elmntArray[i];
    memmove(l->elmntArray + i, l->elmntArray + i + 1,
            (l->size - i) * sizeof(Elmnt));
    --l->size;

    return elmnt;
}
