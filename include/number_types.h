#ifndef NUMBER_TYPES_H
#define NUMBER_TYPES_H

#include <limits.h>

#define NUMBER_BUFFER_SIZE (CHAR_BIT * (int)sizeof(long long) + 4)
#define ERROR_MESSAGE_SIZE 128

typedef enum {
    BASE_BINARY = 2,
    BASE_OCTAL = 8,
    BASE_DECIMAL = 10,
    BASE_HEXADECIMAL = 16
} NumberBase;

typedef struct {
    NumberBase detected_base;
    long long value;
} ParsedNumber;

typedef struct {
    ParsedNumber source;
    char binary[NUMBER_BUFFER_SIZE];
    char octal[NUMBER_BUFFER_SIZE];
    char decimal[NUMBER_BUFFER_SIZE];
    char hexadecimal[NUMBER_BUFFER_SIZE];
} ConversionResult;

#endif
