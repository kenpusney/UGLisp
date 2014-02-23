
#ifndef _MPARSER_H
#define _MPARSER_H

enum TOKEN {
    TOK_ATOM = 0,
    TOK_KEYWORDS, // ':'
    TOK_LPAR, // `(`
    TOK_RPAR, // ')'
    TOK_QUOTE,  // `'`
    TOK_QUASHIQUOTE, // '`'
    TOK_UNQUOTE,  // ','
    TOK_SHARP,    // '#'
    TOK_SEMICOLOUN,  // ';'
    TOK_REF,  // '&'
    TOK_DEREF,  // '@'
    TOK_STR,    // '"'
    TOK_BEGIN
};

typedef struct token_t {
    enum TOKEN t;
    union {
        char* repr;
        char symbol;
    } v;
    struct token_t* next;
} token_t;

void parser();

#endif //_MPARSER_H
