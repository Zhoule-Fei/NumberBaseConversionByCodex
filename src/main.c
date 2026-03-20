#include <stdio.h>

#include "converter.h"
#include "parser.h"

int main(int argc, char **argv) {
    ConversionResult result;
    char error_message[ERROR_MESSAGE_SIZE];

    if (argc != 2) {
        fprintf(stderr,
                "Usage: %s <value>\n"
                "Use 0b for binary, 0o for octal, 0x for hexadecimal, and no prefix for decimal.\n",
                argv[0]);
        return 1;
    }

    if (!convert_number(argv[1], &result, error_message, sizeof(error_message))) {
        fprintf(stderr, "Error: %s\n", error_message);
        return 1;
    }

    printf("Input: %s\n", argv[1]);
    printf("Detected base: %s\n", base_name(result.source.detected_base));
    printf("Binary: %s\n", result.binary);
    printf("Octal: %s\n", result.octal);
    printf("Decimal: %s\n", result.decimal);
    printf("Hexadecimal: %s\n", result.hexadecimal);
    return 0;
}
