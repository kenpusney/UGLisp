
#include <stdio.h>

#include "repl.h"
#include "object.h"

#define loop while (1)

static void printPadding(int padding)
{
    for (int i = 0; i < padding * 2; i++)
    {
        putchar(' ');
    }
}

static void printList(MList list, int padding)
{
    MListNode node = list->head;
    printPadding(padding - 1);
    puts("List<");

    while (node != NULL)
    {
        if (node->v->t == M_LIST)
        {
            printList(node->v->v.l, padding + 1);
        }
        else
        {
            printPadding(padding);
            print(node->v);
        }
        node = node->next;
    }
    printPadding(padding - 1);
    puts(">");
}

void print(MObject obj)
{
    if (!obj)
        return;
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
        printList(obj->v.l, 1);
        break;
    case M_VECTOR:
        printf("#<VECTOR @%x>\n", (unsigned int)obj->v.unit);
        break;
    default:
        printf("#<OBJECT @%x>\n", (unsigned int)obj->v.unit);
    }
}
