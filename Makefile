SRC=src/memstack.c
OBJ=src/memstack.o
HDR=include/memstack.h

INSTALL_PATH?=/usr

TARGET=libmemstack.so
.PHONY: run

CC:=gcc
LD:=gcc

CFLAGS:=-Iinclude -fPIC
LDFLAGS:=-shared
LIBS:=
$(info ${obj})
default: install

%.o: %.c $(HDR)
	$(CC) -c $< $(CFLAGS) -o $@

all: ${OBJ}
	$(LD) -o $(TARGET) $^ ${LDFLAGS} ${LIBS}


clean:
	$(RM) -f $(OBJ)
	$(RM) -f $(TARGET)

install: all
	mv $(TARGET) $(INSTALL_PATH)/lib/$(TARGET)
	cp include/memstack.h $(INSTALL_PATH)/include/memstack.h

uninstall:
	$(RM) -f $(INSTALL_PATH)/lib/$(TARGET) $(INSTALL_PATH)/include/memstack.h
