
CC=gcc
OBJS=obj/main.o obj/mparser.o obj/mhash.o obj/msymtab.o obj/mobject.o obj/repl.o
TARGET=bin/ugl
CFLAGS=-Iinclude -Wall -pg -g3
RM=rm -rf


$(TARGET): bin $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

$(OBJS): obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean env

env: obj bin
	mkdir -p obj
	mkdir -p bin

clean:
	$(RM) $(OBJS)

