SRC=$(wildcard tests/*.c)
OBJ=$(patsubst %.c,%.o,$(SRC))
EXE=$(patsubst %.c,%.bin,$(SRC))
TST=$(patsubst %.bin,%.test,$(EXE))
.PHONY: run

CXX:=g++
CC:=gcc
LD:=gcc

CFLAGS:=
LDFLAGS:=
LIBS:=-lmemstack
$(info ${obj})
default: all

$(info Remember to install memstack before testing!)

testrunner:
	@$(CXX) testrunner.cc -o testrunner

%.o: %.c $(HDR)
	@$(CC) -c $< $(CFLAGS) -o $@

%.bin: %.o
	@$(LD) -o $@ $^ ${LDFLAGS} ${LIBS}

%.test: %.bin testrunner
	@./testrunner ./$<

outdir:
	@mkdir -p out

all: outdir ${TST}

clean:
	$(RM) -f testrunner
	$(RM) -f $(OBJ)
	$(RM) -f libmemstack.so
	$(RM) -f $(EXE)
	$(RM) -rf out
