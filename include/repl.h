

#ifndef _REPL_H
#define _REPL_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "mobject.h"

void repl();
void print(MObject);
//MObject eval(ast_t* expr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //_REPL_H
