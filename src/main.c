#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#include "assets.h"
#include "file.h"

int main(void) {
	// The CLI tool only supports the digits of pi initially.
	FILE *file = file_open(path_pi);

	printf("# Learn digits #\n");

	// Use immediate mode terminal.
	struct termios old;
	struct termios new;

	tcgetattr(0, &old);

	new = old;
	new.c_lflag &= ~(ICANON | ECHO);

	tcsetattr(0, TCSANOW, &new);

	// Get the pre-. digits.
	int buffer = fgetc(file);

	printf("\n>>> ");
	int offset = 1; // number of pre-. + . characters
	while (buffer != EOF && buffer != '.') {
		printf("%c", buffer);
		buffer = fgetc(file);
		offset++;
	}
	printf(".\n");

	size_t cursor = 1;
	buffer = fgetc(file);

	char user_input;
	while (buffer != EOF && buffer >= '0' && buffer <= '9') {
		printf("(%d) ", cursor);

		user_input = getchar();

		// If this is no digit, skip it.
		if (user_input < '0' || user_input > '9') {
			printf("\r");
			continue;
		}

		// If the digit is the wrong one, stop the game.
		if (buffer != user_input) {
			printf("Too bad! %d-th digit was %d, not %d.\n", cursor,
			       buffer - '0', user_input - '0');
			tcsetattr(0, TCSANOW, &old);
			return EXIT_SUCCESS;
		}

		// If everything is good,
		// - we go up one line
		// - we go end of line and add new char
		// - we go back to the input line
		// - we clear the line
		printf("\033[1A"); // go up
		printf("\033[%dC", offset + cursor - 1); // go right
		printf("%c", buffer); // print new char
		printf("\033[1B"); // go down
		printf("\033[2K"); // clear entire line
		printf("\r"); // go to begin of line

		cursor++;
		buffer = fgetc(file);
	}

	// Restore old terminal state.
	tcsetattr(0, TCSANOW, &old);

	file_close(file);
	return EXIT_SUCCESS;
}
