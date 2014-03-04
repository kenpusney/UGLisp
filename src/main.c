
#include <stdio.h>
#include "missions.h"
#include "mobject.h"
#include "mparser.h"
#include "mhash.h"
#include "msymtab.h"

#include "repl.h"

int main(){
    //parser();
    MObject z = obj_ref(make_mnum(5));
    // symtab_init();
    // symtab_push("z",z);
    // printf("%f,%f",z->v.n,(symtab_fetch("z"))->v.n);
    print(z);
}
