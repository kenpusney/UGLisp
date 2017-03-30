
#include <stdio.h>
#include "object.h"
#include "parser.h"
#include "hash.h"
#include "symtab.h"

#include "repl.h"

int main()
{
    MObject z = obj_ref(make_mstr("Hello,world!"));
    print(z);
    free_mobject(z);
    return 0;
}
