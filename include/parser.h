
#ifndef _MPARSER_H
#define _MPARSER_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "object.h"

enum TOKEN
{
    TOK_NIL = 0,
    TOK_KEYWORDS,    // ':'
    TOK_LPAR,        // `(`
    TOK_RPAR,        // ')'
    TOK_QUOTE,       // `'`
    TOK_QUASHIQUOTE, // '`'
    TOK_UNQUOTE,     // ','
    TOK_SHARP,       // '#'
    TOK_SEMICOLOUN,  // ';'
    TOK_REF,         // '&'
    TOK_DEREF,       // '@'
    TOK_STR,         // '"'
    TOK_SYMBOL
};

typedef struct token_t
{
    enum TOKEN t;
    union {
        char *repr;
        char symbol;
    } v;
    struct token_t *next;
} token_t;

typedef struct tokenlist_t
{
    token_t *head;
} * TokenList;

TokenList lex(char *source);
void freeTokenList(TokenList tokens);

MObject parse(TokenList tokens);
void freeAst(MObject object);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif //_MPARSER_H
