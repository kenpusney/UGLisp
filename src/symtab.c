
#include "symtab.h"
#include <stdlib.h>

SymbolTable make_symtab()
{
    SymbolTable symtab = (SymbolTable)malloc(sizeof(struct symtab_t));
    HashTable htable = make_shtable(next_prime(1000));
    symtab->tbl = htable;
    return symtab;
}

MObject symtab_fetch(SymbolTable symtab, char *sym)
{
    return hget(symtab->tbl, sym);
};
unsigned int symtab_push(SymbolTable symtab, char *sym, MObject obj)
{
    return hput(symtab->tbl, sym, obj);
}
