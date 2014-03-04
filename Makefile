
CC=gcc
OBJS=obj/main.o obj/mparser.o obj/mhash.o obj/msymtab.o obj/mobject.o obj/repl.o
TARGET=bin/ugl
CFLAGS=-Iinclude -Wall
RM=rm -rf


$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

$(OBJS): obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) $(TARGET) $(OBJS)

