#include "highc/array.h"
#include <stdio.h>
#include <string.h>

int iarr[] = {
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10
};

char *sarr[] = {
	"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"
};

void printi(unsigned index, int v)
{
	printf("%u:%d ", index, v);
}

int add1(unsigned index, int v)
{
	return v + 1;
}

#define add3(index, v) ((v) + 3)

int eq5(int index, char *a)
{
	return !strcmp(a, "5");
}

int test_array()
{
	int errors = 0;
	array_apply(iarr, add1);
	array_apply(iarr, add3);
	if(!array_contains(5, iarr)) {
		printf("5 not found in array\n");
		errors++;
	}
	if(array_contains(4, iarr)) {
		printf("4 was in array\n");
		errors++;
	}
	char *tmparr[sizeof(sarr) / sizeof(sarr[0])] = {0};
	int count = 0;
	array_filter(sarr, tmparr, count, eq5);
	if(count != 1) {
		printf("array filter failed\n");
		errors++;
	}
	for_array(txt, index, tmparr) {
		if(*txt) {
			printf("%s\n", *txt);
		}
	}
	return errors;
}
