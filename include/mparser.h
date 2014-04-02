
#ifndef _MPARSER_H
#define _MPARSER_H

struct MObject;
typedef struct MObject* MObject;

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

enum AST_TYPE {
	AST_LIST,
	AST_APPLY,
	AST_IF,
	AST_COND,
	AST_LAMBDA,
	AST_DEFINE,
	AST_ATOM
};

typedef struct token_t {
    enum TOKEN t;
    union {
        char* repr;
        char symbol;
    } v;
    struct token_t* next;
} token_t;

typedef struct ast_t{
	enum AST_TYPE t;
	MObject v;
	struct ast_t* next;
	struct ast_t* childs;
} ast_t;

void parser();
ast_t* gen_ast();
#endif //_MPARSER_H
