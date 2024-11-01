#include "../highc.h"

#include "test_enum.c"
#include "test_file.c"
#include "test_array.c"
#include "test_defer.c"
#include "test_pointer.c"
#include "test_vector.c"

int main()
{
	int errors = 0;
	int efile = test_file();
	int eenum = test_enum();
	int aerr = test_array();
	int derr = test_defer();
	int perr = test_pointer();
	int verr = test_vector();

	printf("file: %s\n", efile ? "fail" : "pass");
	printf("enum: %s\n", eenum ? "fail" : "pass");
	printf("array: %s\n", aerr ? "fail" : "pass");
	printf("defer: %s\n", derr ? "fail" : "pass");
	printf("pointer: %s\n", perr ? "fail" : "pass");
	printf("vector: %s\n", verr ? "fail" : "pass");
	
	errors = efile + eenum + aerr + derr + verr;
	return errors;
}
