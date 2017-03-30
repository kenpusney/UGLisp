
#include "unittest.hpp"
#include <parser.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>

static void printToken(token_t *token)
{
    char format[256];
    switch (token->t)
    {
    case TOK_STR:
        std::strcpy(format, "String<%s>\n");
        break;
    case TOK_SYMBOL:
        std::strcpy(format, "Symbol<%s>\n");
        break;
    default:
        std::printf("Char<%c>\n", token->v.symbol);
        return;
    }

    std::printf(format, token->v.repr);
}

static LexState makeLexState(char *source)
{
    LexState lexstate = (LexState)std::malloc(sizeof(struct lexstate_t));
    lexstate->size = std::strlen(source);
    lexstate->buf = source;
    lexstate->index = 0;
    return lexstate;
}

TestCase(Should_Lex_Plain_Symbols)
{
    char source[] = "();',:`";

    std::printf("source: %s\n", source);

    LexState lexstate = makeLexState(source);

    auto tokens = lex(lexstate);

    TestAssert(tokens->head->t == TOK_LPAR);

    int index = 0;
    for (token_t *token = tokens->head; token != NULL; token = token->next)
    {
        TestAssert(token->v.symbol == source[index]);
        index++;
    }

    free(lexstate);
}

TestCase(Should_Lex_Symbols)
{
    char source[] = "(#\\hello #world `123 :1+ ,3-' 2*; 666)";

    std::printf("source: %s\n", source);

    LexState lexstate = makeLexState(source);

    auto tokens = lex(lexstate);

    for (auto token = tokens->head; token != NULL; token = token->next)
        printToken(token);
}

TestCase(Should_Lex_Strings)
{
    char source[] = " \"123\\n456\" '123 \" 444444 \x86 \" ";

    std::printf("source: %s\n", source);

    LexState lexstate = makeLexState(source);

    auto tokens = lex(lexstate);

    for (auto token = tokens->head; token != NULL; token = token->next)
        printToken(token);
}
