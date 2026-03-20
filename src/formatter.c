#include "formatter.h"

#include <stdio.h>

static int write_prefixed(unsigned long long magnitude, const char *prefix, const char *digits,
                          int is_negative, char *buffer, size_t buffer_size) {
    int written;

    (void)magnitude;
    written = snprintf(buffer, buffer_size, "%s%s%s", is_negative ? "-" : "", prefix, digits);
    return written >= 0 && (size_t)written < buffer_size;
}

static unsigned long long absolute_value(long long value) {
    return value < 0 ? 0ULL - (unsigned long long)value : (unsigned long long)value;
}

int format_decimal(long long value, char *buffer, size_t buffer_size) {
    int written = snprintf(buffer, buffer_size, "%lld", value);
    return written >= 0 && (size_t)written < buffer_size;
}

int format_octal(long long value, char *buffer, size_t buffer_size) {
    char digits[NUMBER_BUFFER_SIZE];
    unsigned long long magnitude = absolute_value(value);
    int written = snprintf(digits, sizeof(digits), "%llo", magnitude);

    if (written < 0 || (size_t)written >= sizeof(digits)) {
        return 0;
    }

    return write_prefixed(magnitude, "0o", digits, value < 0, buffer, buffer_size);
}

int format_hexadecimal(long long value, char *buffer, size_t buffer_size) {
    char digits[NUMBER_BUFFER_SIZE];
    unsigned long long magnitude = absolute_value(value);
    int written = snprintf(digits, sizeof(digits), "%llx", magnitude);

    if (written < 0 || (size_t)written >= sizeof(digits)) {
        return 0;
    }

    return write_prefixed(magnitude, "0x", digits, value < 0, buffer, buffer_size);
}

int format_binary(long long value, char *buffer, size_t buffer_size) {
    char digits[NUMBER_BUFFER_SIZE];
    unsigned long long magnitude = absolute_value(value);
    int index = NUMBER_BUFFER_SIZE - 1;
    int is_negative = value < 0;

    digits[index] = '\0';
    if (magnitude == 0ULL) {
        digits[--index] = '0';
    } else {
        while (magnitude > 0ULL && index > 0) {
            digits[--index] = (char)('0' + (magnitude & 1ULL));
            magnitude >>= 1U;
        }
    }

    return write_prefixed(0ULL, "0b", &digits[index], is_negative, buffer, buffer_size);
}
