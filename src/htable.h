#ifndef HTABLE_H
#define HTABLE_H

#include <stdlib.h>

#include "elmnt.h"

typedef struct HTableEntry_t {
    const char *key;
    Elmnt elmnt;
} HTableEntry;

typedef struct HTable_t {
    size_t size;
    size_t capacity;
    HTableEntry *entriesArray;
} HTable;

int HTableInit(HTable *t);

void HTableDestroy(HTable *t);

#endif // HTABLE_H
