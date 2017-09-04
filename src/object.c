
#include "object.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

static MObject new_mobject_with(unsigned short size, MObj_tag tag)
{
    MObject obj = malloc(sizeof(struct MObject_t));
    obj->s = size;
    obj->t = tag;
    obj->rc = 0;
    return obj;
}

MObject dup(MObject obj)
{
    switch (obj->t)
    {
    case M_STRING:
        return make_mstr(obj->v.str);
    default:
    {
        MObject new = new_mobject_with(obj->s, obj->t);
        memcpy(&new->v, &obj->v, sizeof(obj->v));
        return new;
    }
    }
}

MObject make_mnum(double i)
{
    MObject obj = new_mobject_with(sizeof(i), M_NUMBER);
    obj->v.n = i;
    return obj;
}

MObject make_mstr(char *s)
{
    assert(s);
    MObject obj = new_mobject_with(strlen(s), M_STRING);
    obj->v.str = malloc(strlen(s) + 1);
    memcpy(obj->v.str, s, strlen(s) + 1);
    return obj;
}

MObject make_matom(char *s)
{
    assert(s);
    MObject obj = new_mobject_with(strlen(s), M_ATOM);
    obj->v.str = malloc(strlen(s) + 1);
    memcpy(obj->v.str, s, strlen(s) + 1);
    return obj;
}

MObject obj_ref(MObject obj)
{
    assert(obj);
    obj->rc++;
    return obj;
}

MObject obj_deref(MObject obj)
{
    assert(obj && obj->rc);
    obj->rc--;
    if (!obj->rc)
    {
        free_mobject(obj);
        obj = NULL;
    }
    return obj;
}

MList make_mlist()
{
    MList mlist = malloc(sizeof(struct MList_t));
    mlist->head = NULL;
    mlist->tail = NULL;
    return mlist;
}

MObject wrap_mlist(MList list)
{
    MObject obj = new_mobject_with(sizeof(struct MList_t), M_LIST);
    obj->v.l = list;
    return obj;
}

static MListNode makeMListNode(MObject object)
{
    MListNode node = malloc(sizeof(struct MListNode_t));
    node->v = object;
    node->next = NULL;
    return node;
}

MList append_mlist(MList mlist, MObject object)
{
    MListNode node = makeMListNode(object);
    if (mlist->head == NULL && mlist->tail == NULL)
    {
        mlist->head = node;
        mlist->tail = node;
    }
    else
    {
        mlist->tail->next = node;
        mlist->tail = node;
    }
    return mlist;
}

static void free_mlist(MList list)
{
    // TODO
}

void free_mobject(MObject obj)
{
    assert(obj);
    if (obj->t == M_LIST)
    {
        free_mlist(obj->v.l);
    }
    free(obj);
}
