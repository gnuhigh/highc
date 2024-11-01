

hfiles = highc/generic.h highc/macromap.h highc/file.h highc/array.h highc/defer.h highc/vector.h highc/enum.h highc/pointer.h

tests += $(wildcard test/*.c)

.PHONY: dist
dist:
	grep -h "\#include <" $(hfiles) > highc.h && grep "\#pragma" -hv $(hfiles) | grep -hv "\#include" >> highc.h

tests: test/main.c $(hfiles)
	@echo "$^"
	gcc -g -I. -std=gnu11 $^ -o test.bin && ./test.bin

all: dist tests
