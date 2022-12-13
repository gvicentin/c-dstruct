#ifndef VALUE_H
#define VALUE_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    VT_BOOL = 0,
    VT_NUMBER,
    VT_REAL,
    VT_STRING,
    VT_OBJECT
} ElementType;

typedef struct Element_t {
    ElementType type;
    union {
        bool boolean;
        int64_t number;
        double real;
        char *string;
        void *object;
    } value;
} Value;

//  Convert types to Value
//
#define BOOL_VALUE(value) ((Value){.type = VT_BOOK, .value.boolean = value})
#define NUMBER_VALUE(value) ((Value){.type = VT_NUMBER, .value.number = value})
#define REAL_VALUE(value) ((Value){.type = VT_REAL, .value.real = value})
#define STRING_VALUE(value) ((Value){.type = VT_STRING, .value.string = value})
#define OBJECT_VALUE(value) ((Value){.type = VT_OBJECT, .value.object = value})

//  Convert from Value to types
//
#define VALUE_BOOL(value) ((value).value.boolean)
#define VALUE_NUMBER(value) ((value).value.number)
#define VALUE_REAL(value) ((value).value.real)
#define VALUE_STRING(value) ((value).value.string)
#define VALUE_OBJECT(value) ((value).value.object)

#endif // VALUE_H
