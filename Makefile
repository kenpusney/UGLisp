
CC=clang
CXX=clang++
OBJS=obj/parser.o obj/lexer.o obj/hash.o obj/object.o 
OBJS+=obj/repl.o obj/stringutil.o
OBJS+=obj/env.o obj/eval.o
MAIN=obj/main.o
TEST_OBJS=obj/TestRunner.o obj/TestMHash.o 
TEST_OBJS+=obj/TestLexer.o obj/TestParser.o
TEST_OBJS+=obj/TestEval.o
TARGET=bin/ugl
TEST_TARGET=bin/runTest
CFLAGS=-Iinclude -Wall -pg -g3
CXXFLAGS=$(CFLAGS) -std=c++1y
RM=rm -rf


$(TARGET): clean bin $(MAIN) $(OBJS)
	$(CC) -o $(TARGET) $(MAIN) $(OBJS) $(CFLAGS)

$(MAIN): obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJS): obj/%.o: test/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_TARGET): clean bin $(OBJS) $(TEST_OBJS)
	$(CXX) -o $(TEST_TARGET) $(OBJS) $(TEST_OBJS) $(CFLAGS)

.PHONY: clean env test run $(TEST_TARGET)

test: clean $(TEST_TARGET)
	./$(TEST_TARGET)

run: clean $(TARGET)
	./$(TARGET)

env: 
	mkdir -p obj
	mkdir -p bin

clean:
	$(RM) obj/*.o bin/ugl bin/runTest

analyse:
	scan-build -o report make
	make test
	valgrind --leak-check=yes ./bin/runTest
