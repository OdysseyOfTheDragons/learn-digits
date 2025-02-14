#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"

FILE* file_open(const char* filename) {
	FILE* file = fopen(filename, "r");

	if (file == NULL) {
		perror("Cannot open file");
		exit(errno);
	}

	return file;
}

void file_close(FILE* file) {
	fclose(file);
	file = NULL;
}
