SRC=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(SRC))
EXE=$(patsubst %.c,%.bin,$(SRC))
TST=$(patsubst %.c,%.test,$(SRC))
.PHONY: run

CC:=gcc
LD:=gcc

CFLAGS:=-I../include
LDFLAGS:=
LIBS:=
$(info ${obj})
default: all

.PHONY: %.test

libmemstack.so:
	$(MAKE) --directory=.. all
	mv ../libmemstack.so libmemstack.so

%.o: %.c $(HDR)
	$(CC) -c $< $(CFLAGS) -o $@

%.bin: %.o
	$(LD) -o $@ $^ ${LDFLAGS} ${LIBS}

%.test: %.bin libmemstack.so
	./$^ >> out/$@

outdir:
	mkdir -p out

all: outdir ${TST}

clean:
	$(RM) -f $(OBJ)
	$(RM) -f $(EXE)
	$(RM) -f $(TST)
