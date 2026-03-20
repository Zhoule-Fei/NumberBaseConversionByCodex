CC := cc
CFLAGS := -std=c11 -Wall -Wextra -Werror -pedantic -Iinclude
BUILD_DIR := build
BIN_DIR := bin
TARGET := $(BIN_DIR)/number_converter
TEST_TARGET := $(BIN_DIR)/test_number_converter

LIB_SOURCES := src/parser.c src/formatter.c src/converter.c
APP_SOURCES := src/main.c
TEST_SOURCES := tests/test_number_converter.c

LIB_OBJECTS := $(LIB_SOURCES:src/%.c=$(BUILD_DIR)/%.o)
APP_OBJECTS := $(APP_SOURCES:src/%.c=$(BUILD_DIR)/%.o)
TEST_OBJECTS := $(TEST_SOURCES:tests/%.c=$(BUILD_DIR)/test_%.o)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(LIB_OBJECTS) $(APP_OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_TARGET): $(LIB_OBJECTS) $(TEST_OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/test_%.o: tests/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
