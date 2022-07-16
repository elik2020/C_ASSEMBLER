#include "files.h"

/**
 * @brief The function open files with different extensions and opening modes
 * 
 * @param fileName The name of the file we want to open
 * @param fileExtension The extension of the file we want to open
 * @param openingMode The opening mode we will open the file with
 * @return FILE* The opend file if the file didn't open the function return NULL
 */
FILE* open_file(char* fileName,char* fileExtension,char* openingMode){
    FILE * file = NULL;
    char* tempName = (char*)malloc(sizeof(fileName) + sizeof(fileExtension)+1);

    strcpy(tempName,fileName);
    strcat(tempName,fileExtension);
    file = fopen(tempName,openingMode);

    free(tempName);

    return file;
}
/**
 * @brief The function copys line to a file
 * 
 * @param line the line we want to copy to the file
 * @param fp the file we want to copy to
 */
void copy_line_to_file(char* line,FILE* fp){
    fprintf(fp, "%s", line);
}

/**
 * @brief The function gets the next line in a file
 * 
 * @param fp the file we get the line from
 * @return char* the next line in the file null if there no line
 */
char* get_line(FILE* fp){
    char *line = (char *)calloc(MAX_LINE_SIZE+1, sizeof(char));
    if(fgets(line,MAX_LINE_SIZE, fp)) {
        return line;
    }
    free(line);
    return NULL;
}

