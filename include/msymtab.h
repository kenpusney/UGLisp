
#ifndef _MSYMTAB_H
#define _MSYMTAB_H

void    symtab_init  ();
void    symtab_config(unsigned int cfg);
MObject symtab_fetch (char* sym);
MObject symtab_push  (char* sym,MObject obj);
MObject symtab_reset (char* sym,MObject obj);

#endif
