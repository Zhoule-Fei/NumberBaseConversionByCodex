#include "parser.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void write_error(char *error_message, size_t error_size, const char *message) {
    if (error_message == NULL || error_size == 0U) {
        return;
    }

    (void)snprintf(error_message, error_size, "%s", message);
}

const char *base_name(NumberBase base) {
    switch (base) {
        case BASE_BINARY:
            return "binary";
        case BASE_OCTAL:
            return "octal";
        case BASE_DECIMAL:
            return "decimal";
        case BASE_HEXADECIMAL:
            return "hexadecimal";
        default:
            return "unknown";
    }
}

int parse_number(const char *input, ParsedNumber *parsed, char *error_message, size_t error_size) {
    const char *cursor;
    const char *digits_start;
    const char *digits_end;
    NumberBase base;
    int is_negative;
    char *end = NULL;
    unsigned long long magnitude;
    char digits_buffer[NUMBER_BUFFER_SIZE];
    size_t digits_length;

    if (input == NULL || parsed == NULL) {
        write_error(error_message, error_size, "Parser received a null argument.");
        return 0;
    }

    while (*input != '\0' && isspace((unsigned char)*input)) {
        input++;
    }

    if (*input == '\0') {
        write_error(error_message, error_size, "Input cannot be empty.");
        return 0;
    }

    cursor = input;
    is_negative = (*cursor == '-');
    if (*cursor == '+' || *cursor == '-') {
        cursor++;
    }

    if (*cursor == '\0') {
        write_error(error_message, error_size, "Input must contain digits.");
        return 0;
    }

    base = BASE_DECIMAL;
    if (cursor[0] == '0' && (cursor[1] == 'b' || cursor[1] == 'B')) {
        base = BASE_BINARY;
    } else if (cursor[0] == '0' && (cursor[1] == 'o' || cursor[1] == 'O')) {
        base = BASE_OCTAL;
    } else if (cursor[0] == '0' && (cursor[1] == 'x' || cursor[1] == 'X')) {
        base = BASE_HEXADECIMAL;
    }

    digits_start = cursor;
    if (base != BASE_DECIMAL) {
        digits_start += 2;
    }

    if (*digits_start == '\0') {
        write_error(error_message, error_size, "Missing digits after base prefix.");
        return 0;
    }

    digits_end = digits_start;
    while (*digits_end != '\0' && !isspace((unsigned char)*digits_end)) {
        digits_end++;
    }

    while (*digits_end != '\0' && isspace((unsigned char)*digits_end)) {
        digits_end++;
    }

    if (*digits_end != '\0') {
        write_error(error_message, error_size, "Input contains invalid trailing characters.");
        return 0;
    }

    digits_length = (size_t)(digits_end - digits_start);
    while (digits_length > 0U && isspace((unsigned char)digits_start[digits_length - 1U])) {
        digits_length--;
    }

    if (digits_length == 0U) {
        write_error(error_message, error_size, "Input must contain digits.");
        return 0;
    }

    if (digits_length >= sizeof(digits_buffer)) {
        write_error(error_message, error_size, "Input is too long to parse safely.");
        return 0;
    }

    (void)memcpy(digits_buffer, digits_start, digits_length);
    digits_buffer[digits_length] = '\0';

    errno = 0;
    magnitude = strtoull(digits_buffer, &end, (int)base);
    if (end == digits_buffer || *end != '\0') {
        write_error(error_message, error_size, "Input does not contain a valid number.");
        return 0;
    }

    if (errno == ERANGE) {
        write_error(error_message, error_size, "Input is outside the supported long long range.");
        return 0;
    }

    if ((!is_negative && magnitude > (unsigned long long)LLONG_MAX) ||
        (is_negative && magnitude > (unsigned long long)LLONG_MAX + 1ULL)) {
        write_error(error_message, error_size, "Input is outside the supported long long range.");
        return 0;
    }

    parsed->detected_base = base;
    if (is_negative) {
        parsed->value = (magnitude == (unsigned long long)LLONG_MAX + 1ULL)
                            ? LLONG_MIN
                            : -(long long)magnitude;
    } else {
        parsed->value = (long long)magnitude;
    }

    return 1;
}
