#ifndef FORMATTER_H
#define FORMATTER_H

#include <stddef.h>

#include "number_types.h"

int format_binary(long long value, char *buffer, size_t buffer_size);
int format_octal(long long value, char *buffer, size_t buffer_size);
int format_decimal(long long value, char *buffer, size_t buffer_size);
int format_hexadecimal(long long value, char *buffer, size_t buffer_size);

#endif
