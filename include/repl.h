

#ifndef _REPL_H
#define _REPL_H

#include "mobject.h"

#define loop while(1)

void repl();
void print(MObject);
MObject eval(int expr);
int read();
#endif //_REPL_H
