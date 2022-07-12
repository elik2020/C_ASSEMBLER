#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 80

FILE* open_file(char* fileName,char* fileExtension);
void copy_line_to_file(char* line,FILE* fp);
char* get_line(FILE* fp);