
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "mparser.h"
#include "mhash.h"
#include "mobject.h"

#define storebuf()                       \
    buf[boffset] = '\0';                 \
    if (strlen(buf))                     \
    {                                    \
        this->next = make_atom_tok(buf); \
        this = this->next;               \
        boffset = 0;                     \
    }

static char *nextSymbol(LexState state);

static char NON_IDENTIFIERS[] = "()'\"#`,;:.";

static int isIdentifierChar(char c)
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

static char current(LexState state)
{
    return state->buf[state->index];
}

static int eof(LexState state)
{
    return state->index >= state->size;
}

TokenList lex(LexState state)
{
    TokenList list = malloc(sizeof(struct tokenlist_t));
    token_t *this = malloc(sizeof(struct token_t));
    list->head = this;
    this->next = NULL;
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
        }
    }
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
