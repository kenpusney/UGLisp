
#ifndef _MOBJECT_H
#define _MOBJECT_H

typedef enum {
    M_ATOM,
    M_NUMBER,
    M_STRING,
    M_CLOSURE,
    M_FUNCTION,
    M_LIST,
    M_VECTOR,
    M_CHAR,
} MObj_tag;

typedef struct MObject{
    unsigned short s;
    unsigned short rc;
    MObj_tag t;
    union{
        void* unit;
        double n;
        struct MList* l;
        struct MVector* vec;
        char* str;
    } v;
    unsigned char* n[0];
}* MObject;

typedef struct MList{
    MObject v;
    struct MList* n;
}* MList;

typedef struct MVector{
    unsigned int s;
    struct MObject head[0];
}* MVector;

MObject make_mnum(double);

MObject obj_ref(MObject);
MObject obj_deref(MObject);

#endif
