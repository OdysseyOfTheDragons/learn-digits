#include <stdio.h>
#include <stdlib.h>

#include "assets.h"
#include "file.h"

#define length 1000

int main(void) {
	// The CLI tool only supports the digits of pi initially.
	FILE* file = file_open(path_pi);

	printf("# Learn digits #\n");

	int buffer = fgetc(file);

	printf(">>> ");
	while (buffer != EOF && buffer != '.') {
		printf("%c", buffer);
		buffer = fgetc(file);
	}
	printf(".\n\n");

	size_t cursor = 1;
	buffer = fgetc(file);

	char user_input;
	while (buffer != EOF) {
	   printf("(%d) ", cursor);

	   user_input = getchar();

	   // If there is a line feed, skip it.
	   if (user_input == 10) {
		   continue;
	   }

	   // If the digit is the wrong one, stop the game.
	   if (buffer != user_input) {
		   printf("Too bad! %d-th digit was %d, not %d.\n",
				   cursor, buffer - '0', user_input - '0');
		   return EXIT_SUCCESS;
	   }

	   cursor++;
	   buffer = fgetc(file);
	}

	file_close(file);
	return EXIT_SUCCESS;
}
