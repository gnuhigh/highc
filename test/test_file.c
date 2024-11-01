//#include <highc/file.h>

#define TEST_FILE_DIR "_test_dir"
#define TEST_DIR_MODE  S_IRWXO | S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH

#define touch(path, data) ({			\
	int ret = 0;				\
	FILE f = fopen(path, "w");		\
	if(f) {					\
	if (fwrite(data, sizeof(data), f)	\
	}					\
	else {					\
		ret = errno;			\
	}					\

static int test_file_dir_loop()
{
	int err = 0;
	rmdir(TEST_FILE_DIR "/subdir");
	rmdir(TEST_FILE_DIR);
	if((err = mkdir(TEST_FILE_DIR, TEST_DIR_MODE)))
		goto err;
	if((err = mkdir(TEST_FILE_DIR "/subdir", TEST_DIR_MODE)))
		goto err;
	
	rmdir(TEST_FILE_DIR);
	return 0;
err:
	printf("path %s: error %d %s\n", TEST_FILE_DIR, err, strerror(err));
	return err;
}

static int test_file_read()
{
	file_data *tmp = file_read("test/test_file.c");
	if(tmp) {
		puts(tmp->data);
		free(tmp);
		return 0;
	}
	return -1;
}

static int test_file()
{
	int errors = 0;
	if(test_file_dir_loop())
		errors++;
	if(test_file_read())
		errors++;

	autoclose FILE *f = fopen("test/main.c", "r");
	return errors;
}

