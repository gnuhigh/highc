//#include <highc/pointer.h>

static int test_pointer()
{
	int errors = 1;
	
	with_pointer(int, iptr, malloc(sizeof(*iptr) * 10)) {
		printf("%p\n", iptr);
		errors = 0;
	}

	autofree int *ints = malloc(sizeof(*ints) * 10);
	printf("%p\n", ints);
	return errors;
}
