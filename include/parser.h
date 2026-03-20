#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>

#include "number_types.h"

int parse_number(const char *input, ParsedNumber *parsed, char *error_message, size_t error_size);
const char *base_name(NumberBase base);

#endif
