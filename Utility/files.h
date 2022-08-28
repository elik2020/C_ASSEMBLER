#ifndef FILES_H
#define FILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 81
#define MAX_FILE_NAME_SIZE 255

/**
 * @brief a function to open a file
 * 
 * @param fileName - the name of the file
 * @param fileExtension - the file's extension
 * @param openingMode - the opening mode that we use to open the file
 * @return FILE* returns the file that we've created
 */
FILE* open_file(char* fileName,char* fileExtension,char* openingMode);

/**
 * @brief copies the line into the file
 * 
 * @param line - the current line
 * @param fp - the file that we copy from
 */
void copy_line_to_file(char* line,FILE* fp);
/**
 * @brief gets the next line in the file
 * 
 * @param fp - the file that we copy from
 * @return char* the line that we copied
 */
char* get_line(FILE* fp);

#endif 