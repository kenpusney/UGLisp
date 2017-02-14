
#include "unittest.hpp"
#include <mparser.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>

TestCase(Should_Lex_Plain_Symbols)
{
    char source[] = "();',:`";

    LexState lexstate = (LexState)std::malloc(sizeof(struct lexstate_t));
    lexstate->size = std::strlen(source);
    lexstate->buf = source;
    lexstate->index = 0;

    auto tokens = lex(lexstate);

    TestAssert(tokens->head->t == TOK_LPAR);

    int index = 0;
    for (token_t *token = tokens->head; token != NULL; token = token->next)
    {
        TestAssert(token->v.symbol == source[index]);
        index++;
    }
}

TestCase(Should_Lex_Symbols)
{
    // TODO: Finish this;
}
