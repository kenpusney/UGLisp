
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

Symbol make_object_symbol(MObject *obj)
{
    Symbol symbol = (Symbol)malloc(sizeof(struct symbol_t));
    return symbol;
}
