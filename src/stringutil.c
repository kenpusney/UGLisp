
#include "stringutil.h"

StringBuffer makeStringBuffer()
{
    StringBuffer sb = malloc(sizeof(struct string_buffer_t));
    sb->capacity = 256;
    sb->size = 0;
    sb->buffer = malloc(sizeof(char) * 256);
    return sb;
}

void freeStringBuffer(StringBuffer sb)
{
    free(sb->buffer);
    free(sb);
}

static int extendingRequired(StringBuffer sb)
{
    return sb->size >= sb->capacity;
}

static void extendStringBuffer(StringBuffer sb)
{
    sb->buffer = realloc(sb->buffer, sb->capacity * 2);
    sb->capacity *= 2;
}

void appendToStringBuffer(StringBuffer sb, char c)
{
    if (extendingRequired(sb))
    {
        extendStringBuffer(sb);
    }

    sb->buffer[sb->size] = c;
    sb->size++;
}
