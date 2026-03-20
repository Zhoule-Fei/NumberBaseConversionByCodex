#include "converter.h"

#include <stdio.h>

#include "formatter.h"
#include "parser.h"

static int write_error(char *error_message, size_t error_size, const char *message) {
    if (error_message == NULL || error_size == 0U) {
        return 0;
    }

    (void)snprintf(error_message, error_size, "%s", message);
    return 0;
}

int convert_number(const char *input, ConversionResult *result, char *error_message, size_t error_size) {
    if (result == NULL) {
        return write_error(error_message, error_size, "Conversion result pointer cannot be null.");
    }

    if (!parse_number(input, &result->source, error_message, error_size)) {
        return 0;
    }

    if (!format_binary(result->source.value, result->binary, sizeof(result->binary)) ||
        !format_octal(result->source.value, result->octal, sizeof(result->octal)) ||
        !format_decimal(result->source.value, result->decimal, sizeof(result->decimal)) ||
        !format_hexadecimal(result->source.value, result->hexadecimal, sizeof(result->hexadecimal))) {
        return write_error(error_message, error_size, "Failed to format one or more output values.");
    }

    return 1;
}
