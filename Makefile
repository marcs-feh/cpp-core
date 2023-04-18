CC := clang++ -std=c++17
LD := clang++ -fuse-ld=mold
AR := ar
override CFLAGS := -O2 -pipe -Wall -Wextra -fPIC -I. $(CFLAGS)
override LDFLAGS := -L. $(LDFLAGS)

.PHONY: clean run list

list:
	@echo 'Available targets: run, build, list, clean'
	@echo 'Current build options:'
	@echo "CC = $(CC)"
	@echo "LD = $(LD)"
	@echo "AR = $(AR)"
	@echo "CFLAGS = $(CFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"

run: bin/test.bin
	@./bin/test.bin

bin/test.bin: bin/main.o bin/libc++base.a
	$(LD) bin/main.o bin/libc++base.a -o bin/test.bin $(LDFLAGS)

bin/libc++base.a: bin/mem.bump_allocator.o
	$(AR) rcs bin/libc++base.a bin/mem.bump_allocator.o

bin/main.o: main.cpp _tests/*.cpp
	$(CC) $(CFLAGS) -c main.cpp -o bin/main.o

bin/mem.bump_allocator.o: mem/bump_allocator.cpp
	$(CC) $(CFLAGS) -c mem/bump_allocator.cpp -o bin/mem.bump_allocator.o

clean:
	rm -f bin/*
