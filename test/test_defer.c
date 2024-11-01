//#include "highc/defer.h"
#include <stdint.h>


int fn3(int flip)
{	
	printf("%s\n", __func__);
	defer {
		printf("%s second\n", __func__);
	}
	defer {
		printf("%s first\n", __func__);
		return 2;
	}
	printf("%s ret\n", __func__);
	if(flip)
		return 3;	
	else
		return 4;
		
}


void fn2()
{
	printf("%s\n", __func__);
	defer {
		printf("%s second\n", __func__);
	}
	int ret = fn3(2);
	printf("fn3 %d\n", ret);
	defer {
		printf("%s first\n", __func__);
	}
	printf("%s ret\n", __func__);
	return;
}


int fn()
{
	printf("%s\n", __func__);
	defer {
		printf("%s second\n", __func__);
	}
	fn2();
	fn3(1);
	defer {
		printf("%s first\n", __func__);
	}
	return 1;
}

void dummy()
{
	return;
}

void fn4()
{
	defer {};
	return;
}


void fn5()
{
	defer {};
	fn4();
	return;
}


void fn6()
{
	defer {};
	fn5();
	return;
}


void fn7()
{
	defer {};
	fn6();
	return;
}

void fn8()
{
	defer {};
	fn7();
	return;
}

int test_defer()
{
	printf("start\n");
	dummy();
	fn8();
	fn();
	return 0;
}
