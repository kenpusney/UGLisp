
#include <stdlib.h>

#include <runtime.h>
#include <hash.h>

Environment make_environment(Environment parent)
{
    Environment env = (Environment)malloc(sizeof(struct environment_t));

    env->parent = parent;
    env->symbols = make_shtable(2 << 18);
    env->caller = NULL;

    return env;
}

Symbol lookup_symbol(Environment env, char *key)
{
    if (hfind(env->symbols, key) != NULL)
    {
        return (Symbol)hfind(env->symbols, key);
    }
    if (env->parent != NULL)
    {
        return lookup_symbol(env->parent, key);
    }
    return NULL;
}

void push_symbol(Environment env, char *key, Symbol value)
{
    hinsert(env->symbols, key, value);
}

Symbol make_object_symbol(MObject obj)
{
    Symbol symbol = (Symbol)malloc(sizeof(struct symbol_t));

    symbol->t = ENV_OBJECT;
    symbol->v.object = obj;
    return symbol;
}

Symbol make_callable_symbol(Callable callable)
{
    Symbol symbol = (Symbol)malloc(sizeof(struct symbol_t));

    symbol->t = ENV_CALLABLE;
    symbol->v.callable = callable;
    return symbol;
}

MObject wrap_callable(Callable call)
{
    MObject object = (MObject)malloc(sizeof(struct MObject_t));
    object->t = M_CALLABLE;
    object->s = sizeof(*call);
    object->v.c = call;
    return object;
}
