# C Data Structures

My implementation of the data structures that is commonly reused in different
projects with the C language.

For performance reasons, mostly to avoid memory fragmentation, all the 
implementations use arrays as the underling structure. 

## Elements

For more generic use of the data structures the elements stored by them are a 
custom structure that can hold the most common privitives types. The definition 
for this is located at `elmnt.h`, see the following example code for reference.

```c
// declaring and initializing list
AList alist;
AListInit(&alist);

// filling the list with string
AListAdd(&alist STRING_ELMNT("foo"));
AListAdd(&alist STRING_ELMNT("bar"));
AListAdd(&alist STRING_ELMNT("foobar"));

// getting the last element as string
const char *tail = ELMNT_STRING(AListPop(&alist));
printf("tail str: %s\n", tail);

// cleanup
AListDestroy(&alist);
```

## Data Structures

Current data structures:

### AList

**Array List implementation**. *Get* and *Set* elements with `O(1)`.
*Insert* and *Remove* elements with `O(n)`. Provide helper functions such as
revert, sort, etc.

### HTable

**Hash Table implementation**.
// TODO: in progress
