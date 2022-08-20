#include "../Utility/directives_handler.h"


int isDirective(char* word){
    int i = 0;
    const char *directives[] = {".data", ".string", ".struct", ".entry", ".extern"};

    for(i = 0;i<NUM_OF_DIRECTIVES;i++){
        if(strcmp(word,directives[i]) == 0){
            return TRUE;
        }
    }
    return FALSE;
}

int dataHandler(int* DC,char* theDirectiv,symbolTable* currentSymbol,int lineNum)(
    char* afterComma = NULL;
    char* afterDirectiv = NULL;

    if(currentSymbol != NULL){
        currentSymbol->address = (*DC)
        currentSymbol->symbolType = DATA;
    }

    afterDirectiv = strtok(NULL,"");
    afterComma =  strtok(NULL,",");

    if(afterComma == NULL){
        printf("no numbers after .data in line: %d",lineNum)
        return -1;
    }

    while(afterComma != NULL){

        if(isEmpty(afterComma)){
            printf("nothing after coma in line : %d",lineNum);
            return -1;
        }

        if(isNumber(afterComma)){
            (*DC)++;
        }else{
            printf("ronge number in line: %d",lineNum);
        }
        afterComma =  strtok(NULL,",");
    }
    return 1;

)