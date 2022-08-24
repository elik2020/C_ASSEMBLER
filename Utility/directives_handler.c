#include "../Utility/directives_handler.h"


int isDirective(char* word){
    int i = 0;
    const char *directives[] = {".data", ".string", ".struct", ".entry", ".extern"};

    if(word == NULL){
        return FALSE;
    }

    for(i = 0;i<NUM_OF_DIRECTIVES;i++){
        if(strcmp(word,directives[i]) == 0){
            return TRUE;
        }
    }
    return FALSE;
}

int dataHandler(int* DC,char* theDirectiv,symbolTable* currentSymbol,int lineNum){
    char* afterComma = NULL;
    /*char* afterDirectiv = NULL;*/
    

    if(currentSymbol != NULL){
        currentSymbol->address = (*DC);
        currentSymbol->symbolType = DATA_SYMBOL;
    }

    /*afterDirectiv = strtok(NULL,"");*/
    afterComma =  strtok(NULL,",");

    if(afterComma == NULL){
        printf("no numbers after .data in line: %d\n",lineNum);
        return -1;
    }

    while(afterComma != NULL){

        if(isEmpty(afterComma)){
            printf("nothing after coma in line : %d\n",lineNum);
            return -1;
        }

        if(isNumber(afterComma)){
            (*DC)++;
        }else{
            printf("ronge number in line: %d\n",lineNum);
        }
        afterComma =  strtok(NULL,",");
    }
    return 1;

}

int structHandler(int* DC,char* theDirectiv,symbolTable* currentSymbol,int lineNum){
    char* theStruct;

    theStruct = strtok(NULL,",");

    if(currentSymbol != NULL){
        currentSymbol->address = (*DC);
        currentSymbol->symbolType = STRUCT_SYMBOL;
    }

    if(theStruct != NULL){
        if(isNumber(theStruct)){
            (*DC)++;
        }else{
            printf("wrong number in struct in line %d\n",lineNum);
            return -1;
        }
        /*printf("the num is: %s in line : %d",theStruct,lineNum);*/
        return stringHandler(DC,theStruct,NULL,lineNum);
    }else{
        printf("Nothing after .struct declaration in line: %d\n",lineNum);
        return -1;
    }
}

int stringHandler(int* DC,char* theDirectiv,symbolTable* currentSymbol,int lineNum){
    int i = 0;
    int isString = 0;
    int stringLen = 0;
    char* theString;
    
    theString = strtok(NULL,"");
    /*printf("the string is: %s in line : %d\n",theString,lineNum);*/
    if(isEmpty(theString) || strlen(theString) == 0){
        printf("No string in line: %d\n",lineNum);
        return -1;
    }

    if(currentSymbol != NULL){
        currentSymbol->address = (*DC);
        currentSymbol->symbolType = DATA_SYMBOL;
    }
    
    removeRightWhiteSpaces(theString);
    removeLeftWhiteSpaces(theString);

    /*for(i = 0;i<strlen(theString);i++){
        if(theString[i] == '"'){
            break;
        }
    }*/
    
    
    if(theString[i] == '"'){
        while(!isString && theString[i] != '\0' &&  theString[i] != '\n'){
            i++;
            stringLen++;
            if(theString[i] == '"'){
                isString = 1;
            }
        }
    }else{
        printf("wrong declaration of string in line: %d\n",lineNum);
        return -1;
    }
    i++;
    if(isString){
        if(theString[i] == '\n' || i == strlen(theString)){
            (*DC) = (*DC) + stringLen;
            return 1;
        }else{
            printf("somthing after a string in line: %d\n",lineNum);
            return -1;
        }
    }

    printf("wrong string in line: %d\n",lineNum);
    return -1;

}

int externHandler(symbolTable** head,int* DC,char* theDirectiv,symbolTable* currentSymbol,int lineNum){
    char* labelAfterExtern;
    char* afterLabel;
    symbolTable* externSymbol = NULL;

    labelAfterExtern = strtok(NULL,SPACES);

    if(currentSymbol != NULL){
        deleteSymbol(head,currentSymbol->name);
    }
    if(isEmpty(labelAfterExtern)){
        printf("No label after .extern declaration in line: %d\n",lineNum);
        return -1;
    }

    if(checkLabelName(labelAfterExtern)){
        if(head != NULL){
            if(inSymbolTable(*head,labelAfterExtern)){
                printf("label already exist label name: %s in line: %d\n",labelAfterExtern,lineNum);
                return -1;
            }
        }
        externSymbol = insertSymbolAtEnd(head,labelAfterExtern,0);
        externSymbol->symbolType = EXTERNAL_SYMBOL;
    }else{
        printf("wrong label name after .extern in line: %d\n",lineNum);
        return -1;
    }

    afterLabel = strtok(NULL,SPACES);
    if(afterLabel == NULL){
        return 1;
    }else{
        printf("Found somthing after the label in the .extern declaration in line: %d\n",lineNum);
        return -1;
    }

}

int entryHandler(symbolTable** head,int* DC,char* theDirectiv,symbolTable* currentSymbol,int lineNum){
    char* labelAfterEntry;
    char* afterLabel;
    
    labelAfterEntry = strtok(NULL,SPACES);

    if(currentSymbol != NULL){
        deleteSymbol(head,currentSymbol->name);
    }

    if(isEmpty(labelAfterEntry)){
        printf("No label after .extern declaration in line: %d\n",lineNum);
        return -1;
    }

    if(!checkLabelName(labelAfterEntry)){
        printf("wrong label name after .entry in line: %d\n",lineNum);
        return -1;
    }

    afterLabel = strtok(NULL,SPACES);
    if(afterLabel == NULL){
        return 1;
    }else{
        printf("Found somthing after the label in the .entry declaration in line: %d\n",lineNum);
        return -1;
    }

}





