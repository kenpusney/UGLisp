
#include <runtime.h>
#include <stdlib.h>
#include <stdio.h>

#include <repl.h>

MObject invoke(Environment environment, MObject obj, MList args)
{
    if (obj->t == M_CALLABLE)
    {
        Callable callable = obj->v.c;
        if (callable->t == CALLABLE_NATIVE)
        {
            return callable->v.native(environment, args);
        }
    }

    return NULL;
}

MObject eval(Environment env, MObject expr)
{
    // fork a new environment
    // env = make_environment(env);

    switch (expr->t)
    {
    case M_ATOM:
    {
        return lookup_symbol(env, expr->v.str);
    }
    case M_LIST:
    {
        return invoke(env, eval(env, expr->v.l->head->v), expr->v.l);
        break;
    }
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

static MObject native_def(Environment env, MList expr)
{
    MObject key = expr->head->next->v;
    MObject value = expr->head->next->next->v;

    push_symbol(env, key->v.str, value);
    return value;
}

static Callable new_native_callable(native_call_t native)
{
    Callable callable = malloc(sizeof(struct callable_t));
    callable->t = CALLABLE_NATIVE;
    callable->v.native = native;

    return callable;
}

void initEnv(Environment env)
{
    push_symbol(env, "def", wrap_callable(new_native_callable(&native_def)));
}
