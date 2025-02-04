# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

CC = gcc
LINKERFLAG = -lm


SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%)

.PHONY = all clean test bison flex

all: ${BINS}

%: %.o
	@echo "Linking..."
	${CC} ${LINKERFLAG} $< -o $@

%.o: %.c
	@echo "Creating objects..."
	${CC} -c $<

%.c: bison

bison:
	bison -d -o ./src/parser.tab.c ./src/pnda.y

flex: bison
	flex -o ./src/lex.yy.c ./src/pnda.l

test: flex
	@echo "Generating test binaries..."
	${CC} -DEBUG_FLEX ./src/parser.tab.c ./src/token.tab.c ./src/lex.yy.c ./src/ast.c -o pnda_parse
	${CC} -DEBUG_BISON ./src/parser.tab.c ./src/token.tab.c ./src/lex.yy.c ./src/ast.c -o pnda_lex

clean:
	@echo "Cleaning up..."
	rm -rvf *.o ${BINS}
	
	@if [ -f ./src/lex.yy.c || -f ./src/parser.tab.c ]; then \
		rm -v ./src/lex.yy.c ./src/parser.tab.c ./src/parser.tab.h; \
	fi

