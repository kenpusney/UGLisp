

#include <stdio.h>

#include "repl.h"
#include "mobject.h"


void print(MObject obj){
    printf("#=> ");
    switch(obj->t){
        case M_NUMBER:   printf("%f",obj->v.n);   break;
        case M_STRING:   printf("%s",obj->v.str); break;
        case M_CLOSURE:  printf("#<CLOSURE @%x>",(unsigned int)obj->v.unit);  break;
        case M_FUNCTION: printf("#<FUNCTION @%x>",(unsigned int)obj->v.unit); break;
        case M_LIST:     printf("#<LIST @%x>",(unsigned int)obj->v.unit);     break;
        case M_VECTOR:   printf("#<VECTOR @%x>", (unsigned int)obj->v.unit);  break;
        default:
            printf("#<OBJECT @%x>",(unsigned int)obj->v.unit);
    }
}

MObject eval(int expr){return NULL;}
int read(){return 0;}

void repl(){
	loop {
		print(eval(read()));
	}
}
