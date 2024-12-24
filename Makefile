# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

CC = gcc
LINKERFLAG = -lm

SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%)

.PHONY = all clean test

all: ${BINS}

%: %.o
	@echo "Linking..."
	${CC} ${LINKERFLAG} $< -o $@

%.o: %.c
	@echo "Creating objects..."
	${CC} -c $<

%.c: %.y
	@echo "Generating parser..."

test:
	@echo "Generating test binaries..."
	flex ./src/pnda.l
	${CC} -DEBUG ./lex.yy.c -o lexer


clean:
	@echo "Cleaning up..."
	rm -rvf *.o ${BINS} lex.yy.c

