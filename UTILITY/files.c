#include <files.h>

FILE* open_file(char* fileName,char* fileExtension){
    FILE * file = NULL;
    char* tempName = (char*)malloc(sizeof(fileName) + sizeof(fileExtension)+1);

    strcpy(tempName,fileName);
    strcat(tempName,fileExtension);
    if(strcmp(fileExtension,".as") == 0){
        file = fopen(tempName,"r");
    }else{
        file = fopen(tempName,"w");
    }
    
    free(tempName);

    return file;
}

void copy_line_to_file(char* line,FILE* fp){
    fprintf(fp, "%s", line);
}

char* get_line(FILE* fp){
    char *line = (char *)calloc(MAX_LINE_SIZE+1, sizeof(char));
    if(fgets(line,MAX_LINE_SIZE, fp)) {
        return line;
    }
    free(line);
    return NULL;
}