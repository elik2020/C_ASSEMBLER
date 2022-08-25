#include "../Iterations/second_pass.h"

void second_pass(char* fileNmae,int isEntry,int endIC,int endDC,symbolTable* head){

    int lineNum = 0;
    int isError = 0;
    char line[LINE_LEN] = {0};
    char* currentWord = NULL;
    int IC = 99;
    FILE* obFile = NULL,*entFile = NULL,*extFile = NULL,*operationFile = NULL,*dataFile = NULL,*amFile = NULL;

    if(table_contain_extern(head)){
        extFile = open_file(fileNmae,".ext","w");
    }
    if(isEntry){
        entFile = open_file(fileNmae,".ent","w");
    }
    amFile = open_file(fileNmae,".am","r");
    operationFile = open_file(fileNmae,".oper","w+");
    dataFile = open_file(fileNmae,".data","w+");

    while(!feof(amFile)){
        fgets(line, LINE_LEN, amFile); 
        lineNum++;
        /*printf("line is: %s\n",line);*/
        if(ignoreLine(line)){
            continue;
        }

        /*printf("line after is: %s\n\n",line);*/
        currentWord = strtok(line, SPACES);

        if(isEmpty(currentWord)){
            continue;
        }

        if(checkLabel(currentWord)){
            currentWord = strtok(line, SPACES);
        }

        if(isDirective(currentWord)){
            /*printf("the word is: %s\n\n",currentWord);*/
            if(directiveEncoder(head,&IC,lineNum,currentWord,entFile) == -1){
                *errorFound= 1;
            }
        }else{
            
            if(isOperation(currentWord)){
                /*printf("start IC is : %d in line: %d\n",IC,lineCount);*/
                IC++;
                if(currentSymbol != NULL){
                    currentSymbol->symbolType = CODE_SYMBOL;
                }
                if(operationHandler(&IC,lineCount,currentWord) == -1){
                    *errorFound= 1;
                }
                /*printf("END IC is : %d in line: %d\n\n",IC,lineCount);*/
            }else{
                printf("invalid comend in line %d\n",lineCount);
                
            }
            
        }
    }


}

int directiveEncoder(symbolTable* head,int* IC,int lineNum,char* theDirectiv,FILE* entFile,FILE* dataFile){

    if(strcmp(theDirectiv,".data") == 0){
        dataEncoder();
    }

    if(strcmp(theDirectiv,".string") == 0){
        stringEncoder();
    }

    if(strcmp(theDirectiv,".struct") == 0){
        structEncoder();
    }

    if(strcmp(theDirectiv,".extern") == 0){
        return externCheck(head,lineNum);
    }

    if(strcmp(theDirectiv,".entry") == 0){
        return entryCheck(head,lineNum,entFile);
    }

    printf("invalid directiv in line: %d\n",lineNum);
    return -1;
}

int externCheck(symbolTable* head,int lineNum){
    char* label;
    label = strtok(NULL, SPACES);
    if(inSymbolTable(head,label) && !(is_extern(head,label))){
        printf("Declaration of .extern of sembol that was declared in the code already line: %d",lineNum);
        return -1;
    }
    return 1;
}

int entryCheck(symbolTable* head,int lineNum,FILE* entFile){
    char* label;
    char addressBase32[2] = {0};

    label = strtok(NULL, SPACES);

    if(is_extern(head,label)){
        printf("Declaration of .entry of a label that was declared as extarn label line: %d",lineNum);
        return -1;
    }

    if(!inSymbolTable(head,label)){
        printf("Declaration of .entry of a label that wasn't declared in the code line: %d",lineNum);
        return -1;
    }

    convert_to_base32(symbol_address(head,label),addressBase32);
    fprintf(entFile, "%s\t%s\n", label, addressBase32);

    return 1;

    
}

void dataEncoder(int* IC,FILE* dataFile,int lineNum){
    char* numAfterComma;
    char numBase32[3] = {0};
    int num = 0;

    numAfterComma = strtok(NULL,SPACES_AND_COMMA);

    while(numAfterComma != NULL){
        (*IC)++;
        charToNum(numAfterComma,num);
        /*CONVERT NUM*/
        convert_to_base32(num,numBase32);
        encoded_to_file(dataFile,numBase32,(*IC));
        numAfterComma = strtok(NULL,SPACES_AND_COMMA);
    }
}

void stringEncoder(int* IC,FILE* dataFile,int lineNum){
    int i = 0;
    int isString = 0;
    char stringBase32[3] = {0};
    char* theString;
    
    theString = strtok(NULL,"");

    removeRightWhiteSpaces(theString);
    removeLeftWhiteSpaces(theString);

    if(theString[i] == '"'){
        i++;
        while(!isString && theString[i] != '\0' &&  theString[i] != '\n'){
            (*IC)++;
            convert_to_base32(theString[i],stringBase32);
            encoded_to_file(dataFile,stringBase32,(*IC));
            i++;
            if(theString[i] == '"'){
                (*IC)++;
                encoded_to_file(dataFile,"!!",(*IC));/* !! is 0 for the line of 0s in the end of string*/
                isString = 1;
            }
        }
    }
    
}

void convert_to_base32(unsigned int num,char* keepBase32){
    unsigned int leftSide;
    unsigned int rightSide;
    const char base32[] = "!@#$%^&*<>abcdefghijklmnopqrstuv";
    unsigned int mask = (int) pow(2,5) - 1; /* mask of '11111'*/

    leftSide = num&(mask << 5);
    leftSide>>=5;
    rightSide = num << mask;

    keepBase32[0] = base32[leftSide];
    keepBase32[1] = base32[rightSide];
    keepBase32[2] = '\0';
}

void encoded_to_file(FILE* fileToWrite ,char* numBase32,int IC){
    char ICBase32[3] = {0};
    convert_to_base32(IC,ICBase32);
    fprintf(fileToWrite, "%s\t%s\n", ICBase32,numBase32);
}


