
#include <stdio.h>
#include "object.h"
#include "parser.h"
#include "hash.h"

#include "repl.h"
#include "runtime.h"

#define BUFFSIZE 65536

int main()
{
    char buf[BUFFSIZE];
    printf("=> ");
    Environment env = make_environment(NULL);
    initEnv(env);
    while (fgets(buf, BUFFSIZE, stdin) != NULL)
    {
        TokenList tokens = lex(buf);
        MObject object = parse(tokens);
        // TODO: fix bug
        freeTokenList(tokens);
        MObject result = eval(env, object);
        print(result);
        freeAst(object);
        printf("=> ");
    }
    return 0;
}
