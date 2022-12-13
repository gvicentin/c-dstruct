#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    ET_BOOL = 0,
    ET_NUMBER,
    ET_REAL,
    ET_STRING,
    ET_OBJECT
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
} Element;

#define BOOL_EL(elmnt)   ((Element){.type = EL_BOOL, .value.boolean = elmnt})
#define NUMBER_EL(elmnt) ((Element){.type = EL_NUMBER, .value.number = elmnt})
#define REAL_EL(elmnt)   ((Element){.type = EL_REAL, .value.real = elmnt})
#define STRING_EL(elmnt) ((Element){.type = EL_STRING, .value.string = elmnt})
#define OBJECT_EL(elmnt) ((Element){.type = EL_OBJECT, .value.object = elmnt})

#define EL_BOOL(elmnt)   ((elmnt).value.boolean)
#define EL_NUMBER(elmnt) ((elmnt).value.number)
#define EL_REAL(elmnt)   ((elmnt).value.real)
#define EL_STRING(elmnt) ((elmnt).value.string)
#define EL_OBJECT(elmnt) ((elmnt).value.object)

#endif // ELEMENT_H
