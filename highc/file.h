#pragma once
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

static void autoclosefile(void *refp)
{
	FILE **fptr = refp;
	FILE *f = *fptr;
	if(f)
		fclose(f);
}

#define autoclose __attribute__((cleanup(autoclosefile)))


/** @brief open, loop by line(\n) and close file
 * @param line[var] variable bound to current line
 * @param len length of the line got from getline()
 * @param file target
 */
#define file_lines(line, len, file)					\
	for (FILE * __func__##__LINE__##file_lines_n = fopen(file, "r"); \
	     __func__##__LINE__##file_lines_n;				\
	     fclose(__func__##__LINE__##file_lines_n), __func__##__LINE__##file_lines_n = 0) \
		for(size_t len = 0; ! len; len = 1)			\
			for(char * line = 0; !line && ! len; free(line), line = line ? 0 : (void*)1) \
				for(len = -1; !line ; len = 0)			\
					if(getline(&line, &len, __func__##__LINE__##file_lines_n) < 0) \
					{ free(line); line = 0; break; } \
					else

/** closure that handles file opening and closing.
 * @param file target
 * @param access string that is used in fopen()
 * @param line[var] variable bound to current line char*
 */
#define with_file(file, access, line)					\
	for (FILE * __func__##__LINE__##file = fopen(file, access);	\
	     __func__##__LINE__##file;					\
	     fclose(__func__##__LINE__##file), __func__##__LINE__##file = 0) \
		for(size_t highc__with_len = 0; ! highc__with_len; highc__with_len = 1)	\
			for(char * line = 0; !line && ! len; free(line), line = line ? 0 : (void*)1) \
				for(__func__##__LINE__##x2len = -1; ! __func__##__LINE__##x2len ; __func__##__LINE__##x2len = 0) \
					if(getline(&line, &__func__##__LINE__##x2len, __func__##__LINE__##file) < 0) \
					{ free(line); line = 0; break; } \
					else

/** @brief structure to hold data from fread */
typedef struct {
	char *data;
	size_t length;
} file_data;

	
/** @brief try to read file content, allocate memory for the data and set the length. You need to free returned value.
 * @param file[in] path
 * @return file_data*
 */
#define file_read(file) ({						\
	file_data *ret = 0;				\
	FILE *f = fopen(file, "r");					\
	if(file) {							\
		if(!fseek(f, 0, SEEK_END)) {				\
			long pos = ftell(f);				\
			if(pos >= 0) {					\
				ret = calloc(1, sizeof(file_data) + pos); \
				if(ret) {				\
					char *data = (char*)(ret + 1);	\
					ret->length = fread(data, 1, pos, f); \
					ret->data = data;		\
				}					\
			}						\
		}							\
		fclose(f);						\
	}								\
	ret;								\
})


/** @brief works like if, open and close directory
 * @param dir_name[var] variable bound to current element
 * @param path string, directory to open
 */
#define with_dir(dir_name, path)					\
	for(DIR * dir_name = opendir(path); dir_name;)			\
	for(int __func__ ## __LINE__ ## _with_dir_n = 0;		\
	    __func__ ## __LINE__ ## _with_dir_n < 3;			\
	    __func__ ## __LINE__ ## _with_dir_n ++)			\
		if(__func__ ## __LINE__ ## _with_dir_n >= 1) {		\
			closedir(dir_name);				\
			dir_name = 0;					\
			break;						\
		}							\
		else							\
			for(;__func__ ## __LINE__ ## _with_dir_n < 1; __func__ ## __LINE__ ## _with_dir_n ++)

/** @brief works like for, operate on open POSIX DIR
 * @param dir[in] dirent DIR
 * @param item[var] variable bound to opened dir element, skips item->d_name which are . or ..
 */
#define for_dir(dir, item)						\
	for(struct dirent * item = readdir((dir)); item; item = readdir((dir))) \
		if(!strcmp(item->d_name, ".") || !strcmp(item->d_name, "..")) \
			continue; \
		else
