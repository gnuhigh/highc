#pragma once
#include "generic.h"
#include "macromap.h"


#define M_ENUMSTR(x) case x : return #x;
#define M_ENUM_ARRAY_STR(x) [x] = #x,

#define def_enum_string(name, ...) typedef enum { MAP_LIST(M_IDENTITY, __VA_ARGS__) } name; \
	static const char *name ## _str(name e) {			\
	static const char *txt[] = {					\
		MAP(M_ENUM_ARRAY_STR, __VA_ARGS__)			\
	};								\
	const char *ret = "N/A";					\
	if(e >= 0 && e < sizeof(txt) / sizeof(txt[0]))			\
		ret = txt[e];						\
	return ret;							\
	}

//static const char * name ## _str (name e) { switch(e) { MAP(M_ENUMSTR, __VA_ARGS__) default: return "N/A"; } }

