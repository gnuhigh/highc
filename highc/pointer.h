#pragma once
#include <stdlib.h>

static void autofreeptr(void *refp)
{
	void **p = (void**)refp;
	free(*p);
}

#define autofree __attribute__((cleanup(autofreeptr)))


static void *with_pointer_free(void *p)
{
	free(p);
	return NULL;
}


/** @brief set ptrvar to ptrvalue and free the ptrvar after.
 * @param type pointer base type
 * @param ptrvar[var] variable name
 * @param ptrvalue[function/variable/macro] something that returns pointer.
 */
#define with_pointer(type, ptrvar, ptrvalue)				\
	for(type * ptrvar = ptrvalue; ptrvar; ptrvar = with_pointer_free(ptrvar)) \
		for(int __func__##__LINE__## with_pointer = 0;		\
		    __func__##__LINE__## with_pointer < 1;		\
		    __func__##__LINE__## with_pointer++)		\

/** @brief set ptrvar to ptrvalue and free the ptrvar after.
 * @param ptrvar[var] variable to void pointer
 * @param ptrvalue[function/variable/macro] something that returns pointer.
 */
#define with_pointerv(ptrvar, ptrvalue)					\
	for(void * ptrvar = ptrvalue; ptrvar; ptrvar = with_pointer_free(ptrvar)) \
		for(int __func__##__LINE__## with_pointer = 0;		\
		    __func__##__LINE__## with_pointer < 1;		\
		    __func__##__LINE__## with_pointer++)		\

