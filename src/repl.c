
#include <stdio.h>

#include "repl.h"
#include "object.h"

#define loop while (1)

void print(MObject obj)
{
    if (!obj)
        return;
    printf("#=> ");
    switch (obj->t)
    {
    case M_NUMBER:
        printf("%f\n", obj->v.n);
        break;
    case M_STRING:
        printf("\"%s\"\n", obj->v.str);
        break;
    case M_ATOM:
        printf("#<ATOM \"%s\">\n", obj->v.str);
        break;
    case M_CLOSURE:
        printf("#<CLOSURE @%x>\n", (unsigned int)obj->v.unit);
        break;
    case M_FUNCTION:
        printf("#<FUNCTION @%x>\n", (unsigned int)obj->v.unit);
        break;
    case M_LIST:
        printf("#<LIST @%x>\n", (unsigned int)obj->v.unit);
        break;
    case M_VECTOR:
        printf("#<VECTOR @%x>\n", (unsigned int)obj->v.unit);
        break;
    default:
        printf("#<OBJECT @%x>\n", (unsigned int)obj->v.unit);
    }
}
