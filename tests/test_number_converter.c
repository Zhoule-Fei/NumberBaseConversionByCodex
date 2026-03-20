#include <stdio.h>
#include <string.h>

#include "converter.h"

static int assert_equal(const char *label, const char *actual, const char *expected) {
    if (strcmp(actual, expected) != 0) {
        fprintf(stderr, "%s mismatch: expected '%s' but got '%s'\n", label, expected, actual);
        return 0;
    }

    return 1;
}

static int test_supported_inputs(void) {
    ConversionResult result;
    char error_message[ERROR_MESSAGE_SIZE];

    if (!convert_number("0x2a", &result, error_message, sizeof(error_message))) {
        fprintf(stderr, "unexpected conversion failure: %s\n", error_message);
        return 0;
    }

    return assert_equal("binary", result.binary, "0b101010") &&
           assert_equal("octal", result.octal, "0o52") &&
           assert_equal("decimal", result.decimal, "42") &&
           assert_equal("hexadecimal", result.hexadecimal, "0x2a");
}

static int test_negative_inputs(void) {
    ConversionResult result;
    char error_message[ERROR_MESSAGE_SIZE];

    if (!convert_number("-0b1111", &result, error_message, sizeof(error_message))) {
        fprintf(stderr, "unexpected conversion failure: %s\n", error_message);
        return 0;
    }

    return assert_equal("binary", result.binary, "-0b1111") &&
           assert_equal("octal", result.octal, "-0o17") &&
           assert_equal("decimal", result.decimal, "-15") &&
           assert_equal("hexadecimal", result.hexadecimal, "-0xf");
}

static int test_invalid_inputs(void) {
    ConversionResult result;
    char error_message[ERROR_MESSAGE_SIZE];

    if (convert_number("0b102", &result, error_message, sizeof(error_message))) {
        fprintf(stderr, "expected invalid binary input to fail\n");
        return 0;
    }

    if (convert_number("0x", &result, error_message, sizeof(error_message))) {
        fprintf(stderr, "expected missing hexadecimal digits to fail\n");
        return 0;
    }

    return 1;
}

int main(void) {
    if (!test_supported_inputs() || !test_negative_inputs() || !test_invalid_inputs()) {
        return 1;
    }

    printf("All tests passed.\n");
    return 0;
}
