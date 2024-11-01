
# What
highc consist mostly of macros that try to provide high level operations that some other programming languages have.  
*Note that this library depend on GCC/Clang extensions and POSIX*
- foreach
- with
- others...


# Using highc in your project

highc/ directory has each component as it's own.  
highc.h contains all the headers as single header file.  
You can include this as git submodule or just copy the highc.h file into your project.


## Examples
See test/*.c files for examples.

pointer.h
```
void fn() {
	with_pointer(int, iptr, malloc(sizeof(*iptr) * 10)) {
		printf("%p\n", iptr);
	}
	
	// attribute cleanup
	autofree int *ints = malloc(sizeof(*ints) * 10):
}

```

file.h
```

autoclose FILE *f = fopen("test/main.c", "r");

with_file("highc.h", "r", linevar) {
	printf("%s\n", linevar);
}

with_dir(dirvar, ".") {
	for_dir(dirvar, item) {
		printf("%s\n", item->d_name);
	}
}
```

array.h, operations on static arrays.  
vector.h works like array.h but also takes buffer length as variable. 

```
int iarr[] = {
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10
};

int add1(unsigned index, int v)
{
	return v + 1;
}

#define lessthan3(x) ((x) < 3)

void fn()
{
	array_apply(iarr, add1);
	int filtered[array_length(iarr)] = {0};
	int filtered_count = 0;
	array_filter(iarr, filtered, filtered_count, lessthan3);
}
```

defer.h
```
int fn()
{
	printf("%s\n", __func__);
	defer {
		printf("%s third\n", __func__);
	}
	defer {
		printf("%s second\n", __func__);
	}
	printf("%s first\n", __func__);
	return 1;
}

```

# Goals

- Easy to use
- Testable
- Valgrind clean

# Conventions

- Return 0 = success, otherwise errno

