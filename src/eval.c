
#include <runtime.h>
#include <stdlib.h>
#include <stdio.h>

#include <repl.h>

MObject eval(Environment env, MObject expr)
{
    // fork a new environment
    // env = make_environment(env);

    switch (expr->t)
    {
    case M_ATOM:
        return lookup_symbol(env, expr->v.str)->v.object;
        break;
    case M_CLOSURE:
        break;
    case M_FUNCTION:
        break;
    case M_LIST:
        break;
    case M_VECTOR:
        break;
    case M_NUMBER:
    case M_STRING:
    case M_CHAR:
        return expr;
    default:
        break;
    }
    return NULL;
}
