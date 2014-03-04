
#include "mobject.h"
#include <stdlib.h>
#include <assert.h>

void free_mobject(MObject);

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

MObject obj_ref(MObject obj){
    assert(obj);
    obj->rc++;
    return obj;
}

MObject obj_deref(MObject obj){
    assert(obj && obj->rc);
    obj->rc--;
    if(!obj->rc){
        free_mobject(obj);
        obj = NULL;
    }
    return obj;
}

void free_mobject(MObject obj){
    assert(obj);
    free(obj);
}