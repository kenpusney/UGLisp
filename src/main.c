
#include <stdio.h>
#include "missions.h"
#include "mobject.h"
#include "mparser.h"
#include "mhash.h"

int main(){
    htable_t* tbl = make_shtable(15);
//    parser();
    hinsert(tbl,"Kimmy","Leo");
    hinsert(tbl,"Joy","Chou");
    printf("%s,%s,%s",hfind(tbl,"Kimmy"),hfind(tbl,"Joy"),hremove(tbl,"Joy"));
	
}

