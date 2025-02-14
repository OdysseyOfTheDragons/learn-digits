/** Opens and closes a file safely. */

#ifndef _FILE_H
#define _FILE_H
#include <stdio.h>

/**
 * Opens a file.
 *
 * @param filename the path to the file
 * @return a pointer to the file
 */
FILE* file_open(const char* filename);

/**
 * Closes a file.
 *
 * @param file a pointer to the file
 */
void file_close(FILE* file);
#endif
