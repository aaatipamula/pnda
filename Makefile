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
CPP_SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
LEX_SOURCES := $(wildcard $(SRC_DIR)/*.l)
YACC_SOURCES := $(wildcard $(SRC_DIR)/*.y)

# Object files
C_OBJS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(C_SOURCES)))
LEX_OBJS := $(patsubst %.l, $(BUILD_DIR)/%.o, $(notdir $(LEX_SOURCES)))
YACC_OBJS := $(patsubst %.y, $(BUILD_DIR)/%.o, $(notdir $(YACC_SOURCES)))

OBJS := $(C_OBJS) $(LEX_OBJS) $(YACC_OBJS)

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

# Compile Flex (Lex) files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.l | $(BUILD_DIR)
	flex -o $(BUILD_DIR)/$*.c $<
	$(CC) $(CFLAGS) -c $(BUILD_DIR)/$*.c -o $@

# Compile Bison (Yacc) files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.y | $(BUILD_DIR)
	bison -d -o $(BUILD_DIR)/$*.c $<
	$(CC) $(CFLAGS) -c $(BUILD_DIR)/$*.c -o $@

# Link everything
$(TARGET): $(BIN_DIR) $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

bison:
	bison -d -o ./src/parser.tab.c ./src/pnda.y

flex: bison
	flex -o ./src/lex.yy.c ./src/pnda.l

test_bins: flex
	@echo "Generating test binaries..."
	${CC} -DEBUG_FLEX ./src/parser.tab.c ./src/token.tab.c ./src/lex.yy.c ./src/ast.c -o debug_parse
	${CC} -DEBUG_BISON ./src/parser.tab.c ./src/token.tab.c ./src/lex.yy.c ./src/ast.c -o debug_lex

test: flex
	./debug_lex test.pd | tee _test_lexer.out
	./debug_parse test.pd | tee _test_parser.out

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

	@if [ -f ./debug_lex || -f ./src/debug_parse ]; then \
		rm -v ./debug_parse ./debug_lex;  \
	fi

