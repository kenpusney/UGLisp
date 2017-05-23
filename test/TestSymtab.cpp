
#include "unittest.hpp"
#include <symtab.h>
#include <object.h>
#include <repl.h>
#include <stdlib.h>

TestCase(Test_Create_A_Symtab)
{
    char hello[] = "hello world";
    char key[] = "hello";
    SymbolTable symtab = make_symtab();
    MObject mstr = obj_ref(make_mstr(hello));

    symtab_push(symtab, key, mstr);

    print(symtab_fetch(symtab, key));

    obj_deref(mstr);
}
