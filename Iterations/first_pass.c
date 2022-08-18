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

            directiveHandler(&head,&DC,lineCount,currentWord,currentSymbol);
        }else{
            if(isOperation(currentWord)){
                IC++;
                operationHandler(&IC,lineCount,currentWord);
            }else{
                printf("bad in line %s",lineCount);
            }
            
        }



        currentSymbol = NULL;
        memset(line,0,LINE_LEN);

    }

}

int operationHandler(int* IC,int lineNum,char* currentWord){

    char firstOperand[LINE_LEN] = {0};
    char secondOperand[LINE_LEN] = {0};

    char* theOperands;
    int expectedOperands;

    expectedOperands = amountOfOperands(currentWord);
    theOperands = strtok(NULL,"");

}

int checkOperationCommand(int numOfOperands,char* firstOperand,char* secondOperand,int lineNum,char* theOperands){
    int i;
    int j;
    if(numOfOperands == 0){
        if(/**/){
            return 1;
        }else{
            printf("eror in line %d",lineNum);
            return 0;
        }
    }

    if(numOfOperands == 1){
        removeRightWhiteSpaces(theOperands);
        for(i = 0;i<strlen(theOperands);i++){
            firstOperand[i] = theOperands[i];
            if(theOperands[i] == ','){
                printf("error need be only one operand in line %d",lineNum);
                return 0;
            }
            return isOperand(firstOperand);
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
        if(operandError(firstOperand)){
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

        if(operandError(secondOperand)){
            return 0;
        }

        return 1;


    }
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
    if(strlen(operand) == 0){
        printf("operand missing in line %d",lineNum);
        return 1;
    }
    if(is_system_word(operand)){
        printf("operand cant be reserved word line: %d",lineNum);
        return 1;
    }
    if(operand[0] == ','){
        printf("to many commas in line : %d",lineNum);
        return 1;
    }

    return 0;
}