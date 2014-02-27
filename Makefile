
CC=gcc
OBJS=obj/main.o obj/mparser.o obj/mhash.o obj/msymtab.o
TARGET=bin/ugl
CFLAGS=-Iinclude
RM=rm -rf


$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

$(OBJS): obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) $(TARGET) $(OBJS)
