
#include <runtime.h>
#include <repl.h>
#include <string>

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
    // Environment env = make_environment(NULL);

    // char str[] = "hello world";
    // char name[] = "str";
}
