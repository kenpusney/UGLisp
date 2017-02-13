
CC=clang
CXX=clang++
OBJS=obj/mparser.o obj/mhash.o obj/msymtab.o obj/mobject.o obj/repl.o
MAIN=obj/main.o
TEST_OBJS=obj/TestRunner.o obj/TestSymtab.o obj/TestMHash.o
TARGET=bin/ugl
TEST_TARGET=bin/runTest
CFLAGS=-Iinclude -Wall -pg -g3
CXXFLAGS=$(CFLAGS) -std=c++14
RM=rm -rf


$(TARGET): bin $(MAIN) $(OBJS)
	$(CC) -o $(TARGET) $(MAIN) $(OBJS) $(CFLAGS)

$(MAIN): obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJS): obj/%.o: test/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_TARGET): bin $(OBJS) $(TEST_OBJS)
	$(CXX) -o $(TEST_TARGET) $(OBJS) $(TEST_OBJS) $(CFLAGS)

.PHONY: clean env test run $(TEST_TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)

env: 
	mkdir -p obj
	mkdir -p bin

clean:
	$(RM) $(OBJS)

