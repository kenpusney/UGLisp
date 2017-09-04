
#include <runtime.h>
#include <repl.h>
#include <string>
#include <parser.h>

#include "unittest.hpp"

TestCase(Should_Eval_A_Value_Successfully)
{
    Environment env = make_environment(NULL);
    char str[] = "hello world";

    MObject theNumber = eval(env, make_mnum(1));

    MObject theString = eval(env, make_mstr(str));

    TestAssert(theNumber->v.n == 1);
    TestAssert(std::string{theString->v.str} == std::string{str});
}

TestCase(Should_Eval_The_Object_Value)
{
    Environment env = make_environment(NULL);

    char str[] = "hello world";
    char name[] = "str";

    push_symbol(env, name, make_object_symbol(make_mstr(str)));

    MObject theString = eval(env, make_matom(name));

    print(theString);

    TestAssert(std::string{theString->v.str} == std::string{str});
}

TestCase(Should_Eval_Define)
{
    Environment env = make_environment(NULL);
    char source[] = "(def x 1)";
    char var[] = "x";

    initEnv(env);

    MObject result = eval(env, parse(lex(source)));

    TestAssert(lookup_symbol(env, var)->v.object->v.n == 1);
    TestAssert(result->v.n == 1);
}
