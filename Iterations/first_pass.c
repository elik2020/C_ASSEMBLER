#include "../Iterations/first_pass.h"


symbolTable first_pass(char* fileName,int* errorFound,int* entryFound){

    int IC = 100;
    int DC = 0;
    FILE* amFile = NULL;
    symbolTable* head = NULL;
    symbolTable* currentSymbol = NULL;
    char line[LINE_LEN] = {0};
    char* currentWord = NULL;
    char labelName[LABEL_LEN] = {0};
    int checkError = 0;
    int lineCount =  0;
    amFile = open_file(fileName,".am","r");

    while(!feof(amFile)){

        fgets(line, LINE_LEN, amFile); 
        lineCount++;

        if(ignoreLine(line)){
            continue;
        }

        printf("line is: %s",line);
        currentWord = strtok(line, SPACES);

        if(checkLabel(currentWord)){
            strcpy(labelName,currentWord);
            currentSymbol = insertSymbolAtEnd(&head,currentWord,&IC);

            currentWord = strtok(NULL,SPACES);
            
        }

        

        if(isDirective(currentWord)){
            if(strcmp(currentWord,".entry") == 0){
                *entryFound = 1;
            }

            directiveHandler(&DC,lineCount,currentWord,currentSymbol);
        }else{
            if(isOperation(currentWord)){
                IC++;
                if(operationHandler(&IC,lineCount,currentWord) == -1){
                    (*entryFound) = 1;
                }
            }else{
                printf("invalid comend in line %d",lineCount);
            }
            
        }



        currentSymbol = NULL;
        memset(line,0,LINE_LEN);

    }

}

int operationHandler(int* IC,int lineNum,char* theOperation){

    char firstOperand[LINE_LEN] = {0};
    char secondOperand[LINE_LEN] = {0};

    char* theOperands;
    int expectedOperands;

    expectedOperands = amountOfOperands(theOperation);
    theOperands = strtok(NULL,"");

    if(checkOperationLine(expectedOperands,firstOperand,secondOperand,lineNum,theOperands)){
        if(expectedOperands == 0){
            (*IC)++;
            return 1;
        }
        return changeICByCommand(expectedOperands,IC,firstOperand,secondOperand,lineNum,theOperation);
    }
    return -1;

}

int checkOperationLine(int numOfOperands,char* firstOperand,char* secondOperand,int lineNum,char* theOperands){
    int i;
    int j;
    if(numOfOperands == 0){
        if(!isEmpty(theOperands)){
            printf("cant be a operation with no operands that have more after the operation in line %d",lineNum);
            return 0;
        }

    }

    if(numOfOperands == 1){
        removeRightWhiteSpaces(theOperands);
        for(i = 0;i<strlen(theOperands);i++){
            firstOperand[i] = theOperands[i];
        }
        if(operandError(firstOperand,lineNum)){
                return 0;
        }
        
    }

    if(numOfOperands == 2){
        for(i = 0;i<strlen(theOperands) && theOperands[i] != ',';i++){
            firstOperand[i] = theOperands[i];
        }
        if(i = strlen(theOperands)-1){
            printf("need be 2 operands in line %d",lineNum);
            return 0;
        }
        removeRightWhiteSpaces(firstOperand);
        if(operandError(firstOperand,lineNum)){
            return 0;
        }
        ++i;
        j = 0;
        for(;i<strlen(theOperands)-1;i++){
            secondOperand[j] = theOperands[i];
            j++;
        }
        removeRightWhiteSpaces(secondOperand);
        removeLeftWhiteSpaces(secondOperand);

        if(operandError(secondOperand,lineNum)){
            return 0;
        }

    }

    return 1;
}

int operandError(char* operand,int lineNum){
    int i;
    for(i = 0;i<strlen(operand);i++){
        if(operand[i] == '\t' || operand[i] == ' '){
            printf("spaces in operand line : %d",lineNum);
            return 1;
        }
        if(operand[i] == ','){
            printf("to many operands in line : %d",lineNum);
            return 1;
        }
    }
    if(strlen(operand) == 0 || endOfLine(operand)){
        printf("operand missing in line %d",lineNum);
        return 1;
    }
    if(isOperation(operand)){
        printf("operand cant be a operation line: %d",lineNum);
        return 1;
    }
    if(isDirective(operand)){
        printf("operand cant be a directive line: %d",lineNum);
        return 1;
    }
    if(operand[0] == ','){
        printf("to many commas in line : %d",lineNum);
        return 1;
    }

    return 0;
}

int changeICByCommand(int numOfOperands,int* IC,char* firstOperand,char* secondOperand,int lineNum,char* theOperation){

    int firstAddressingMethod = 0;
    int secondAddressingMethod = 0;

    if(numOfOperands == 1){
        firstAddressingMethod = addressingMethodType(firstOperand,lineNum);

        if(firstAddressingMethod == -1){
            return -1;
        }
        
        if(!isSourceAddressingMethod(theOperation,firstAddressingMethod)){
            printf("not the right ddressing Method to the source Operand in line ",lineNum);
            return -1;
        }
        addToIC(IC,firstAddressingMethod,0);
    }

    if(numOfOperands == 2){

        firstAddressingMethod = addressingMethodType(firstOperand,lineNum);
        secondAddressingMethod = addressingMethodType(firstOperand,lineNum);

        if(firstAddressingMethod == -1 || secondAddressingMethod == -1){
            return -1;
        }

        if(!isSourceAddressingMethod(theOperation,firstAddressingMethod)){
            printf("not the right ddressing Method to the source Operand in line ",lineNum);
            return -1;
        }

        addToIC(IC,firstAddressingMethod,0);

        if(!isDestinationAddressingMethod(theOperation,secondAddressingMethod)){
            printf("not the right ddressing Method to the destination Operand in line ",lineNum);
            return -1;
        }

        addToIC(IC,secondAddressingMethod,firstAddressingMethod);

    }

    return 1;



}

void addToIC(int* IC,int currMethod,int prevMethod){
    if(currMethod == REGISTER_ADDRESS && prevMethod != REGISTER_ADDRESS){
        (*IC)++;
    }
    if(currMethod == IMMEDIATE_ADDRESS){
        (*IC)++;
    }
    if(currMethod == STRUCT_ADDRESS){
        (*IC) += 2;
    }
    if(currMethod == DIRECT_ADDRESS){
        (*IC)++;
    }

}

int directiveHandler(int *DC,int lineCount,char* theDirectiv,symbolTable* currentSymbol){
    char* afterDirectiv;

    afterDirectiv = strtok(NULL,"");

    if(strcmp(theDirectiv,".data") == 0){
        return dataHandler();
    }

    if(strcmp(theDirectiv,".string") == 0){
        return stringHandler();
    }

    if(strcmp(theDirectiv,".struct") == 0){
        return structHandler();
    }

    if(strcmp(theDirectiv,".extern") == 0){
        return externHandler();
    }

    if(strcmp(theDirectiv,".entry") == 0){

    }

    printf("invalid directiv in line: %d",lineCount);
    return -1;
}

