# NumberBaseConversionByCodex

A small C project for converting numbers between:

- binary (`0b`)
- octal (`0o`)
- decimal (no prefix)
- hexadecimal (`0x`)

## Project Layout

- `include/parser.h`: input parsing and validation
- `include/formatter.h`: base-specific output formatting
- `include/converter.h`: conversion service API
- `src/parser.c`: prefix detection and numeric parsing
- `src/formatter.c`: binary, octal, decimal, and hexadecimal formatting
- `src/converter.c`: orchestration layer
- `src/main.c`: CLI entry point
- `tests/test_number_converter.c`: lightweight test executable

## Build

```bash
make
```

## Run

```bash
./bin/number_converter 42
./bin/number_converter 0b101010
./bin/number_converter 0o52
./bin/number_converter 0x2a
```

## Test

```bash
make test
```

## Example Output

```text
Input: 0x2a
Detected base: hexadecimal
Binary: 0b101010
Octal: 0o52
Decimal: 42
Hexadecimal: 0x2a
```

