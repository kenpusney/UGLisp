
#include "unittest.hpp"
#include <mhash.h>
#include <cstdio>

TestCase(Test_Should_Create_A_Hash_Successfully)
{
    htable_t *ht = make_shtable(100000);
    int x = 1;
    char key[] = "hello";
    char m[100] = "";

    hinsert(ht, key, &x);

    TestAssert(hfind(ht, key) == &x);
    double gg = 123;
    hinsert(ht, (char *)"world", &gg);
    hremove(ht, key);

    TestAssert(hfind(ht, key) == nullptr);
    TestAssert(hfind(ht, (char *)"world") == &gg);

    for (int i = 0; i < 1000000; i++)
    {
        std::sprintf(m, "key%d", i);
        x++;
        hinsert(ht, m, &x);
    }

    auto ptr = (int *)hfind(ht, (char *)"key24");
    TestAssert(ptr == &x);
    TestAssert(*ptr == x);

    hdestroy(ht);
}
