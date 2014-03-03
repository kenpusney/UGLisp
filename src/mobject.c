
#include "mobject.h"
#include <stdlib.h>

static MObject new_mobject_with(unsigned short size,MObj_tag tag){
    MObject obj = malloc(sizeof(struct MObject));
    obj->s = size;
    obj->t = tag;
    obj->rc = 0;
    return obj;
}

MObject make_mnum(double i){
    MObject obj = new_mobject_with(sizeof(i),M_NUMBER);
    obj->v.n = i;
    return obj;
}