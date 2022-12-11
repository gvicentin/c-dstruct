#ifndef ALIST_H
#define ALIST_H

#include <assert.h>
#include <stdlib.h>

typedef struct AList_t {
    size_t size;
    size_t capacity;
    void **dataArray;
} AList;

//  Initialize list structure.
//
int AListInit(AList *l);

//  De-initialize list structure.
//
void AListDestroy(AList *l);

//  Increase list's capacity.
//
int AListExpand(AList *l, size_t newCapacity);

//  Returns number of elements from list.
//
static inline size_t AListSize(AList *l) { return l->size; }

//  Returns element of index 'i' from list.
//
static inline void *AListGet(AList *l, size_t i) {
    assert(i < l->size);
    return l->dataArray[i];
}

//  Set element of index 'i'.
//
static inline void AListSet(AList *l, size_t i, void *data) {
    assert(i < l->size);
    l->dataArray[i] = data;
}

//  Add element in the end of the list.
//
void AListAdd(AList *l, void *data);

//  Add all elements from list r to list l.
//
void AListAddAll(AList *l, AList *r);

//  Remove element from the end of the list, and
//  returns the removed element.
//
void *AListPop(AList *l);

//  Adds element in index 'i'.
//
void AListInsert(AList *l, size_t i, void *data);

//  Insert all elements from list r to the list r.
//
void AListInsertAll(AList *l, AList *r, size_t i);

//  Removes element in index 'i', and
//  return the removed element.
void *AListRemove(AList *l, size_t i);

#endif // ALIST_H
