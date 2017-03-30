
#include "symtab.h"

typedef struct symtab_t
{
    htable_t *tbl;
} symtab_t;

static symtab_t default_symtab;

void symtab_init()
{
    default_symtab.tbl = make_shtable(next_prime(1000));
}

void symtab_config(unsigned int cfg){};
MObject symtab_fetch(char *sym)
{
    return hget(default_symtab.tbl, sym);
};
unsigned int symtab_push(char *sym, MObject obj)
{
    return hput(default_symtab.tbl, sym, obj);
}
//MObject symtab_reset(char* sym,MObject obj){
//    return hupdate(default_symtab.tbl,sym,obj);
//}
