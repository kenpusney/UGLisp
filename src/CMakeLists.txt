set(UGL_LIB_SRC
    env.c
    eval.c
    hash.c
    lexer.c
    object.c
    parser.c
    repl.c
    stringutil.c
)

include_directories(../include)

add_library(libugl ${UGL_LIB_SRC})
