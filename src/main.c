
#include <stdio.h>
#include "object.h"
#include "parser.h"
#include "hash.h"
#include "symtab.h"

#include "repl.h"

#define BUFFSIZE 65536

int main()
{
    char buf[BUFFSIZE];
    printf("=> ");
    while (fgets(buf, BUFFSIZE, stdin) != NULL)
    {
        TokenList tokens = lex(buf);
        MObject object = parse(tokens);
        // TODO: fix bug
        // freeTokenList(tokens);
        print(object);
        printf("=> ");
    }
    return 0;
}
