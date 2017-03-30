
#include "unittest.hpp"
#include <parser.h>
#include <repl.h>
#include <cstdlib>
#include <cstring>

static LexState makeLexState(char *source)
{
    LexState lexstate = (LexState)std::malloc(sizeof(struct lexstate_t));
    lexstate->size = std::strlen(source);
    lexstate->buf = source;
    lexstate->index = 0;
    return lexstate;
}

static void printList(MList list)
{
    MListNode node = list->head;

    while (node != NULL)
    {
        print(node->v);
        node = node->next;
    }
}

TestCase(Parse_Simple_Object)
{
    char source[] = "123";

    auto lexstate = makeLexState(source);

    auto tokens = lex(lexstate);

    auto object = parse(tokens);

    print(object);

    TestAssert(object->t == M_NUMBER);
}

TestCase(Parse_Simple_Atom)
{
    char source[] = "atom";

    auto lexstate = makeLexState(source);

    auto tokens = lex(lexstate);

    auto object = parse(tokens);

    print(object);

    TestAssert(object->t == M_ATOM);
}

TestCase(Parse_Simple_List)
{
    char source[] = "(hello world)";

    auto lexstate = makeLexState(source);

    auto tokens = lex(lexstate);

    auto object = parse(tokens);

    print(object);
    printList(object->v.l);

    TestAssert(object->t == M_LIST);
}
