#include <stdio.h>
#include <stdlib.h>

#include "assets.h"
#include "file.h"

#define length 1000

int main(void) {
	// The CLI tool only supports the digits of pi initially.
	FILE* file = file_open(path_pi);

	char buffer[length + 1] = { 0 };
	fgets(buffer, length, file);
	file_close(file);

	printf("%s\n", buffer);

	return EXIT_SUCCESS;
}
