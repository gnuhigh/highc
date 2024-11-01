//#include "highc/enum.h"
//#include "highc/array.h"
#include <stdio.h>

def_enum_string(teste,
		F_2,
		F_3,
		F_4,
		F_5,
		F_6);


int test_enum()
{
#define print(field) printf(#field ": %s\n", teste_str(field))
	int F_NEG = -1;
	int F_BIG = 100;
	print(F_NEG);
	print(F_BIG);
	print(F_2);
	print(F_3);
	print(F_4);
	print(F_5);
	print(F_6);
	return 0;
}
