#ifndef CONVERTER_H
#define CONVERTER_H

#include <stddef.h>

#include "number_types.h"

int convert_number(const char *input, ConversionResult *result, char *error_message, size_t error_size);

#endif
