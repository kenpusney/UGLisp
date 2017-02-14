
#include <stdio.h>
#include "mobject.h"
#include "mparser.h"
#include "mhash.h"
#include "msymtab.h"

#include "repl.h"

int main()
{
    MObject z = obj_ref(make_mstr("Hello,world!"));
    print(z);
    free_mobject(z);
    return 0;
}
