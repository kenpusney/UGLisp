
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "hash.h"
#include "object.h"
#include "stringutil.h"

#define storebuf()                       \
    buf[boffset] = '\0';                 \
    if (strlen(buf))                     \
    {                                    \
        this->next = make_atom_tok(buf); \
        this = this->next;               \
        boffset = 0;                     \
    }

typedef struct lexstate_t
{
    char *buf;
    int size;
    int index;
} * LexState;

static char *nextSymbol(LexState state);
static char *nextString(LexState state);

static char NON_IDENTIFIERS[] = "()'\"#`,;:";

static LexState makeLexState(char *source)
{
    LexState lexstate = (LexState)malloc(sizeof(struct lexstate_t));
    lexstate->size = strlen(source);
    lexstate->buf = source;
    lexstate->index = 0;
    return lexstate;
}

static int
isIdentifierChar(char c)
{
    for (int i = 0; i < strlen(NON_IDENTIFIERS); i++)
        if (c == NON_IDENTIFIERS[i])
            return 0;
    return 1;
}

static int
advance(LexState state)
{
    state->index++;
    return state->index < state->size;
}

static char
current(LexState state)
{
    return state->buf[state->index];
}

static int eof(LexState state)
{
    return state->index >= state->size;
}

TokenList lex(char *source)
{
    LexState state = makeLexState(source);
    TokenList list = malloc(sizeof(struct tokenlist_t));
    token_t *this = malloc(sizeof(struct token_t));
    list->head = this;
    this->next = NULL;
    this->t = TOK_NIL;
    while (1)
    {
        switch (current(state))
        {
        case '(':
            this->t = TOK_LPAR;
            this->v.symbol = '(';
            break;
        case ')':
            this->t = TOK_RPAR;
            this->v.symbol = ')';
            break;
        case '\'':
            this->t = TOK_QUOTE;
            this->v.symbol = '\'';
            break;
        case '\"':
            this->v.symbol = '\"';
            this->t = TOK_STR;
            advance(state);
            this->v.repr = nextString(state);
            advance(state);
            break;
        case '#':
            this->t = TOK_SHARP;
            this->v.symbol = '#';
            break;
        case '`':
            this->t = TOK_QUASHIQUOTE;
            this->v.symbol = '`';
            break;
        case ',':
            this->t = TOK_UNQUOTE;
            this->v.symbol = ',';
            break;
        case ';':
            this->t = TOK_SEMICOLOUN;
            this->v.symbol = ';';
            break;
        case '&':
            this->t = TOK_REF;
            this->v.symbol = '&';
            break;
        case ':':
            this->t = TOK_KEYWORDS;
            this->v.symbol = ':';
            break;
        default:
            if (isgraph(current(state)))
            {
                this->t = TOK_SYMBOL;
                this->v.repr = nextSymbol(state);
            }
            break;
        }
        if (this->t != TOK_SYMBOL)
        {
            advance(state);
        }
        if (eof(state))
        {
            break;
        }
        else if (this->t)
        {
            this->next = malloc(sizeof(struct token_t));
            this = this->next;
            this->next = NULL;
            this->t = TOK_NIL;
        }
    }
    free(state);
    return list;
}

static char *nextSymbol(LexState state)
{
    int start = state->index;
    while (!eof(state))
    {
        if (isgraph(current(state)) && isIdentifierChar(current(state)))
        {
            advance(state);
        }
        else
        {
            break;
        }
    }

    char *blob = copy_blob(state->buf + start, state->index - start + 1);
    blob[state->index - start] = '\0';
    return blob;
}

static int isEscape(char current)
{
    return current == '\\';
}

static int hexStringToValue(char c)
{
    return c >= '0' && c <= '9' ? c - '0' : tolower(c) - 'a';
}

static char unEscape(LexState state)
{
    int val = 0;
    switch (current(state))
    {
    case '\\':
    case '\"':
    case '\'':
        return current(state);
    case 'a':
        return '\a';
    case 'b':
        return '\b';
    case 't':
        return '\t';
    case 'v':
        return '\v';
    case 'n':
        return '\n';
    case 'r':
        return '\r';
    case 'x':
        for (int i = 0; i < 2; i++)
        {
            advance(state);
            val = val * 16 + hexStringToValue(current(state));
        }
        return (char)val;
    default:
        return current(state);
    }
}

static char *nextString(LexState state)
{
    StringBuffer sb = makeStringBuffer();
    char thisChar = '\0';

    while (!eof(state))
    {
        if (isEscape(current(state)))
        {
            advance(state);
            thisChar = unEscape(state);
        }
        else if (current(state) == '"')
        {
            break;
        }
        else
        {
            thisChar = current(state);
        }
        appendToStringBuffer(sb, thisChar);
        advance(state);
    }
    char *blob = copy_blob(sb->buffer, sb->size + 1);
    blob[sb->size] = '\0';
    freeStringBuffer(sb);

    return blob;
}

static void freeToken(token_t *token)
{
    switch (token->t)
    {
    case TOK_SYMBOL:
    case TOK_STR:
        if (token->v.repr != NULL)
            free(token->v.repr);
    default:
        break;
    }
    free(token);
}

void freeTokenList(TokenList tokens)
{
    if (tokens != NULL)
    {
        token_t *current = tokens->head;
        while (current != NULL)
        {
            token_t *next = current->next;
            freeToken(current);
            current = next;
        }
        free(tokens);
    }
}
