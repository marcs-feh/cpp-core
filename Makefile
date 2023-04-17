CC      := clang++ -std=c++17
LD      := clang++ -fuse-ld=mold
AR      := ar
CFLAGS  := -O2 -pipe -Wall -Wextra -fPIC -I. $(CFLAGS)
LDFLAGS := -L.

.PHONY: clean run list

list:
	@echo CC = $(CC)
	@echo LD = $(LD)
	@echo AR = $(AR)
	@echo CFLAGS = $(CFLAGS)
	@echo LDFLAGS = $(LDFLAGS)

run: bin/test.bin
	@./bin/test.bin

bin/test.bin: bin/main.o bin/libcppcore.a
	$(LD) bin/main.o bin/libcppcore.a -o bin/test.bin

bin/libcppcore.a: bin/mem.bump_allocator.o
	$(AR) rcs bin/libcppcore.a bin/mem.bump_allocator.o

bin/main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o bin/main.o

bin/mem.bump_allocator.o: mem/bump_allocator.cpp
	$(CC) $(CFLAGS) -c mem/bump_allocator.cpp -o bin/mem.bump_allocator.o

clean:
	rm -f bin/*
