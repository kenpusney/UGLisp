
#include "unittest.hpp"
#include <mhash.h>

TestCase(Test_Should_Create_A_Hash_Successfully)
{
    htable_t *ht = make_shtable(10);
    int x = 1;
    char key[] = "hello";
    hinsert(ht, key, &x);

    TestAssert(hfind(ht, key) == &x);
}
