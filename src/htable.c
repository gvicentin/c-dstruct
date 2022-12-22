#include "htable.h"

#define INITIAL_CAPACITY 16

int HTableInit(HTable *t) {
    t->entriesArray =
        (HTableEntry *)calloc(INITIAL_CAPACITY, sizeof(HTableEntry));
    if (t->entriesArray == NULL) {
        return 1;
    }

    t->capacity = INITIAL_CAPACITY;
    t->size = 0;

    return 0;
}

void HTableDestroy(HTable *t) {
    for (size_t i = 0; i < t->capacity; ++i) {
        if (t->entriesArray[i].key == NULL) {
            free((void *)t->entriesArray[i].key);
        }
    }

    free(t->entriesArray);
}
