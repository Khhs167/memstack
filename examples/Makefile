# EXAMPLE MAKEFILE
# BY KHHS
# TO BUILD AN EXAMPLE, DO "make [name].bin"
# TO RUN AN EXAMPLE, DO "make [name].run"
# OTHER FUNCTIONS ARE AVAILABLE AS USUAL

# EXAMPLES ARE SPAT OUT WITH A .BIN SO THAT THEY'RE EASILY GITIGNORED

SRC=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(SRC))
BIN=$(patsubst %.c,%.bin,$(SRC))
RUN=$(patsubst %.c,%.run,$(SRC))
HDR=../include/memstack.h

OUT_DIR=build

CC:=gcc
LD:=gcc

CFLAGS:=-I../include
LDFLAGS:=
LIBS:=-lmemstack

default: help

%.o: %.c $(HDR)
	$(CC) -c $< $(CFLAGS) -o $@

%.bin: %.o
	$(LD) -o $@ $< ${LDFLAGS} ${LIBS}

.PHONY: %.run all runall clean

%.run: %.bin
	./$<

all: $(BIN)

runall: $(RUN)

clean:
	$(RM) -f $(OBJ)
	$(RM) -f $(BIN)

help:
	@echo libmemstack example makefile.
	@echo to build an example, do make [name].bin
	@echo to run a target, do make [name].run
	@echo extra commands: all runall clean help
