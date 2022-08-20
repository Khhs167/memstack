# EXAMPLE MAKEFILE
# BY KHHS
# TO BUILD AN EXAMPLE, DO "make [name]"
# TO RUN AN EXAMPLE, DO "make [name].run"
# OTHER FUNCTIONS ARE AVAILABLE AS USUAL

SRC=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(SRC))
BIN=$(patsubst %.c,%,$(SRC))
RUN=$(patsubst %.c,%.run,$(SRC))
HDR=../include/memstack.h

CC:=gcc
LD:=gcc

CFLAGS:=-I../include
LDFLAGS:=
LIBS:=-lmemstack

default: help

%.o: %.c $(HDR)
	$(CC) -c $< $(CFLAGS) -o $@

$(BIN): %: %.o
	$(LD) -o $@ $< ${LDFLAGS} ${LIBS}

.PHONY: %.run all runall clean

%.run: %
	./$<

all: $(BIN)

runall: $(RUN)

clean:
	$(RM) -f $(OBJ)
	$(RM) -f $(BIN)

help:
	@echo libmemstack example makefile.
	@echo to build an example, do make [name]
	@echo to run a target, do make [name].run
	@echo extra commands: all runall clean help
