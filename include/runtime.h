
#ifndef __RUNTIME_H
#define __RUNTIME_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "object.h"
#include "hash.h"
#include "vm.h"
#include "stddef.h"

struct environment_t;

enum callable_type
{
    CALLABLE_DEFINED,
    CALLABLE_COMPILED,
    CALLABLE_NATIVE
};

typedef MObject (*native_call_t)(struct environment_t *callable, MList expr);

typedef struct callable_t
{
    enum callable_type t;
    HashTable closure;
    union {
        struct
        {
            MObject expr;
            MObject pc;
        } * defined;
        struct
        {
            Operations *ops;
            size_t size;
            size_t pc;
        } * compiled;
        native_call_t native;
    } v;
} callable_t, *Callable;

typedef struct call_stack_t
{
    struct call_stack_t *head;
    struct call_stack_t *next;
    Callable *callable;
} call_stack_t, CallStack;

enum symbol_type
{
    ENV_CALLABLE,
    ENV_OBJECT
};

typedef struct symbol_t
{
    enum symbol_type t;
    union {
        Callable callable;
        MObject object;
    } v;
} symbol_t, *Symbol;

typedef struct environment_t
{
    struct environment_t *parent;
    HashTable symbols;
    Callable caller;
} environment_t, *Environment;

Environment make_environment(Environment parent);
Symbol lookup_symbol(Environment env, char *key);
void push_symbol(Environment env, char *key, Symbol value);
void initEnv(Environment env);

MObject eval(Environment env, MObject expr);

Symbol make_object_symbol(MObject obj);
Symbol make_callable_symbol(Callable symbol);

Callable make_defined_callable(MObject *expr);
CallStack make_callstack();
MObject wrap_callable(Callable call);
void attachCall(CallStack stack, Callable call);
void resumeCall(CallStack stack, Callable call);
void yieldCall(CallStack stack, Callable call);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // __RUNTIME_H
