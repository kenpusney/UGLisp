
#include "unittest.hpp"
#include <parser.h>
#include <repl.h>
#include <cstdlib>
#include <string>

TestCase(Parse_Simple_Object)
{
    char source[] = "123";

    auto tokens = lex(source);

    auto object = parse(tokens);

    print(object);

    TestAssert(object->t == M_NUMBER);

    freeAst(object);
    freeTokenList(tokens);
}

TestCase(Parse_Simple_Atom)
{
    char source[] = "atom";

    auto tokens = lex(source);

    auto object = parse(tokens);

    print(object);

    TestAssert(object->t == M_ATOM);

    freeAst(object);
    freeTokenList(tokens);
}

TestCase(Parse_Simple_List)
{
    char source[] = "(hello world)";

    auto tokens = lex(source);

    auto object = parse(tokens);

    print(object);

    TestAssert(object->t == M_LIST);

    freeAst(object);
    freeTokenList(tokens);
}

TestCase(Parse_Nested_List)
{
    char source[] = "(I (have (a)) (dream))";

    auto tokens = lex(source);

    auto object = parse(tokens);

    print(object);

    TestAssert(object->t == M_LIST);

    freeAst(object);
    freeTokenList(tokens);
}

TestCase(Parse_Strin)
{
    char source[] = "(\"hello \\n world\" 1 \"list\")";

    auto tokens = lex(source);

    auto object = parse(tokens);

    print(object);

    TestAssert(object->t == M_LIST);

    TestAssert(std::string{object->v.l->head->v->v.str} == std::string{"hello \n world"});
    TestAssert(object->v.l->head->next->v->v.n == 1);
    TestAssert(std::string{object->v.l->tail->v->v.str} == std::string{"list"});

    freeAst(object);
    freeTokenList(tokens);
}
