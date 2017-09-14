set(UGL_TEST_SRC
    TestEval.cpp
    TestLexer.cpp
    TestMHash.cpp
    TestParser.cpp
    TestRunner.cpp
)

include_directories(../include)

add_executable(ugltest ${UGL_TEST_SRC})

target_link_libraries(ugltest libugl)
