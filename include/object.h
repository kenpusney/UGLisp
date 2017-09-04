
#ifndef _MOBJECT_H
#define _MOBJECT_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef enum {
    M_ATOM,
    M_NUMBER,
    M_STRING,
    M_LIST,
    M_VECTOR,
    M_CHAR,
    M_CALLABLE,
    M_CLOSURE,
    M_FUNCTION,
} MObj_tag;

struct callable_t;

typedef struct MObject_t
{
    unsigned short s;
    unsigned short rc;
    MObj_tag t;
    union {
        void *unit;
        double n;
        struct MList_t *l;
        struct MVector_t *vec;
        char *str;
        struct callable_t *c;
    } v;
    unsigned char n[0];
} MObject_t, *MObject;

typedef struct MListNode_t
{
    MObject v;
    struct MListNode_t *next;
} MListNode_t, *MListNode;

typedef struct MList_t
{
    MListNode head;
    MListNode tail;
} MList_t, *MList;

typedef struct MVector_t
{
    unsigned int s;
    struct MObject_t head[0];
} MVector_t, *MVector;

MObject make_matom(char *);
MObject make_mstr(char *);
MObject make_mnum(double);

MObject dup(MObject obj);

MList make_mlist();
MObject wrap_mlist(MList);
MList append_mlist(MList, MObject);

MObject obj_ref(MObject);
MObject obj_deref(MObject);

void free_mobject(MObject);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
