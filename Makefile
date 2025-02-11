# Usage:
# make        # Compile all binaries

# Compiler and Flags
CC := gcc
CFLAGS := -Wall -Wextra -Ilib -Isrc
LDFLAGS := -lm

# Directories
SRC_DIR := src
LIB_DIR := lib
BUILD_DIR := build
BIN_DIR := bin

# Source files
C_SOURCES := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(LIB_DIR)/*.c)
LEX_SOURCES := $(wildcard $(SRC_DIR)/*.l)
YACC_SOURCES := $(wildcard $(SRC_DIR)/*.y)

# Generated files
LEX_C := $(SRC_DIR)/lex.yy.c
YACC_C := $(SRC_DIR)/parser.tab.c
YACC_H := $(SRC_DIR)/parser.tab.h

# Object files
C_OBJS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(C_SOURCES)))
LEX_OBJ := $(BUILD_DIR)/lex.yy.o
YACC_OBJ := $(BUILD_DIR)/parser.tab.o

OBJS := $(C_OBJS) $(LEX_OBJ) $(YACC_OBJ)

# Executable
TARGET := $(BIN_DIR)/pnda

# Run from make
.PHONY = all clean test

# Default target
all: $(TARGET)

# Create directories if not exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compile C files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(LIB_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Generate and compile Flex file (lex.yy.c)
$(LEX_C): $(LEX_SOURCE)
	flex -o $(LEX_C) $<

# Generate and compile Bison files (parser.tab.c, parser.tab.h)
$(YACC_C) $(YACC_H): $(YACC_SOURCE)
	bison -d -o $(YACC_C) $<

# Compile Flex file (lex.yy.c)
$(LEX_OBJ): $(LEX_C) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(LEX_C) -o $(LEX_OBJ)

# Compile Bison file (parser.tab.c, parser.tab.h)
$(YACC_OBJ): $(YACC_C) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(YACC_C) -o $(YACC_OBJ)

# Link everything
$(TARGET): $(BIN_DIR) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

test_bins: $(BIN_DIR) $(LEX_C) $(YACC_C)
	@echo "Generating test binaries..."
	$(CC) $(CFLAGS) -DEBUG_FLEX $(LEX_C) $(YACC_C) ./src/token.tab.c ./src/ast.c -o $(BIN_DIR)/debug_parse
	$(CC) $(CFLAGS) -DEBUG_BISON $(LEX_C) $(YACC_C) ./src/token.tab.c ./src/ast.c -o $(BIN_DIR)/debug_lex

test: test_bins
	@echo "Testing..."

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

