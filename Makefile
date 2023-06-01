CC := clang++ -std=c++20
LD := clang++
AR := ar
override CFLAGS := -O2 -pipe -march=native -Wall -Wextra -fPIC -I. $(CFLAGS)
override LDFLAGS := $(LDFLAGS) -lm -L.

.PHONY: clean run list

list:
	@echo 'Available targets: run, build, list, clean'
	@echo 'Current build options:'
	@echo "CC = $(CC)"
	@echo "LD = $(LD)"
	@echo "AR = $(AR)"
	@echo "CFLAGS = $(CFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"

build:
	@mkdir -p bin

run: bin/test.bin
	@mkdir -p bin
	@./bin/test.bin

bin/test.bin: main.cpp _tests/*.cpp
	$(CC) $(CFLAGS) main.cpp -o bin/test.bin $(LDFLAGS)

clean:
	rm -f bin/*
