
#ifndef _MSYMTAB_H
#define _MSYMTAB_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "hash.h"

typedef struct symtab_t
{
    htable_t *tbl;
} symtab_t, *SymbolTable;

SymbolTable make_symtab();
MObject symtab_fetch(SymbolTable symtab, char *sym);
unsigned int symtab_push(SymbolTable symtab, char *sym, MObject obj);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif
