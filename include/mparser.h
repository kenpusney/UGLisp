
#ifndef _MPARSER_H
#define _MPARSER_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct MObject_t;
typedef struct MObject_t *MObject;

enum TOKEN
{
    TOK_ATOM = 0,
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

enum AST_TYPE
{
    AST_LIST,
    AST_APPLY,
    AST_IF,
    AST_COND,
    AST_LAMBDA,
    AST_DEFINE,
    AST_ATOM
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

typedef struct lexstate_t
{
    char *buf;
    int size;
    int index;
} * LexState;

TokenList lex(LexState state);

void parser();

#ifdef __cplusplus
}
#endif // __cplusplus
#endif //_MPARSER_H
