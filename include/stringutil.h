
#ifndef _STRING_BUFFER_H
#define _STRING_BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdlib.h>

typedef struct string_buffer_t
{
    size_t capacity;
    size_t index;
    size_t size;
    char *buffer;
} * StringBuffer;

StringBuffer makeStringBuffer();
void freeStringBuffer(StringBuffer sb);
void appendToStringBuffer(StringBuffer sb, char c);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //_STRING_BUFFER_H
