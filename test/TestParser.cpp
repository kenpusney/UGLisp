
#include "unittest.hpp"
#include <parser.h>
#include <repl.h>
#include <cstdlib>
#include <cstring>

TestCase(Parse_Simple_Object)
{
    char source[] = "123";

    auto tokens = lex(source);

    auto object = parse(tokens);

    print(object);

    TestAssert(object->t == M_NUMBER);
}

TestCase(Parse_Simple_Atom)
{
    char source[] = "atom";

    auto tokens = lex(source);

    auto object = parse(tokens);

    print(object);

    TestAssert(object->t == M_ATOM);
}

TestCase(Parse_Simple_List)
{
    char source[] = "(hello world)";

    auto tokens = lex(source);

    auto object = parse(tokens);

    print(object);

    TestAssert(object->t == M_LIST);
}

TestCase(Parse_Nested_List)
{
    char source[] = "(I (have (a)) (dream))";

    auto tokens = lex(source);

    auto object = parse(tokens);

    print(object);

    TestAssert(object->t == M_LIST);
}
