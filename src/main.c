
#include <stdio.h>
#include "missions.h"
#include "mobject.h"
#include "mparser.h"
#include "mhash.h"
#include "msymtab.h"

#include "repl.h"

int main(){
	repl();
    //parser();
    MObject z = obj_ref(make_mstr("Hello,world!"));
    // symtab_init();
    // symtab_push("z",z);
    // printf("%f,%f",z->v.n,(symtab_fetch("z"))->v.n);
    print(z);
    free_mobject(z);
    return 0;
}
