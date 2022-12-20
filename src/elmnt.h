#ifndef ELMNT_H
#define ELMNT_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    ELMNT_TYPE_BOOL = 0,
    ELMNT_TYPE_NUMBER,
    ELMNT_TYPE_REAL,
    ELMNT_TYPE_STRING,
    ELMNT_TYPE_OBJECT
} ElmntType;

typedef struct Elmnt_t {
    ElmntType type;
    union {
        bool boolean;
        int64_t number;
        double real;
        const char *string;
        void *object;
    } value;
} Elmnt;

//  Converting from primitive types to Elmmnt
//
#define BOOL_ELMNT(elmnt)                                                      \
    ((Elmnt){.type = ELMNT_TYPE_BOOL, .value.boolean = elmnt})

#define NUMBER_ELMNT(elmnt)                                                    \
    ((Elmnt){.type = ELMNT_TYPE_NUMBER, .value.number = elmnt})

#define REAL_ELMNT(elmnt)                                                      \
    ((Elmnt){.type = ELMNT_TYPE_REAL, .value.real = elmnt})

#define STRING_ELMNT(elmnt)                                                    \
    ((Elmnt){.type = ELMNT_TYPE_STRING, .value.string = elmnt})

#define OBJECT_ELMNT(elmnt)                                                    \
    ((Elmnt){.type = ELMNT_TYPE_OBJECT, .value.object = elmnt})

//  Conventing from Elmnt to primitive types
//
#define ELMNT_BOOL(elmnt)   ((elmnt).value.boolean)
#define ELMNT_NUMBER(elmnt) ((elmnt).value.number)
#define ELMNT_REAL(elmnt)   ((elmnt).value.real)
#define ELMNT_STRING(elmnt) ((elmnt).value.string)
#define ELMNT_OBJECT(elmnt) ((elmnt).value.object)

//  Elmnt type checking
//
#define IS_BOOL(elmnt)   ((elmnt).type == ELMNT_TYPE_BOOL)
#define IS_NUMBER(elmnt) ((elmnt).type == ELMNT_TYPE_NUMBER)
#define IS_REAL(elmnt)   ((elmnt).type == ELMNT_TYPE_REAL)
#define IS_STRING(elmnt) ((elmnt).type == ELMNT_TYPE_STRING)
#define IS_OBJECT(elmnt) ((elmnt).type == ELMNT_TYPE_OBJECT)

#endif // ELMNT_H
