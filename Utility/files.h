#ifndef FILES_H
#define FILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 80
#define MAX_FILE_NAME_SIZE 255

FILE* open_file(char* fileName,char* fileExtension,char* openingMode);
void copy_line_to_file(char* line,FILE* fp);
char* get_line(FILE* fp);

#endif 