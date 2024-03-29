#include "../Iterations/first_pass.h"


symbolTable* first_pass(char* fileName,int* errorFound,int* entryFound,int* IC,int* DC){

    FILE* amFile = NULL;
    symbolTable* head = NULL;
    symbolTable* currentSymbol = NULL;
    char line[LINE_LEN] = {0};
    char* currentWord = NULL;
    int lineCount =  0;
    amFile = open_file(fileName,".am","r");

    while(!feof(amFile)){

        fgets(line, LINE_LEN, amFile); 
        lineCount++;
        
        if(ignoreLine(line)){/*Check if line is empty or if it start with ;*/
            continue;
        }

        
        currentWord = strtok(line, SPACES);

        if(isEmpty(currentWord)){
            continue;
        }

        
        
        if(checkLabel(currentWord)){/*check if it's label acceleration*/
            
            if(checkLabelName(currentWord)){/*If the label is correct*/
                if(inSymbolTable(head,currentWord)){
                    printf("label already exist label name: %s in line: %d\n",currentWord,lineCount);
                    *errorFound = 1;
                }else{
                    currentSymbol = insertSymbolAtEnd(&head,currentWord,*IC);
                    currentWord = strtok(NULL,SPACES);
                }
            }else{
                printf("wrong label name in line: %d the name of the label is: %s \n",lineCount,currentWord);
                *errorFound= 1;
            }
            
        }

        

        if(isDirective(currentWord)){/*we check if its a directive*/
            if(strcmp(currentWord,".entry") == 0){
                *entryFound = 1;
            }

            if(directiveHandler(&head,DC,lineCount,currentWord,currentSymbol) == -1){
                *errorFound= 1;
            }
        }else{
            
            if(isOperation(currentWord)){/*we check if its a operation*/
                
                (*IC)++;
                if(currentSymbol != NULL){
                    currentSymbol->symbolType = CODE_SYMBOL;
                }
                if(operationHandler(IC,lineCount,currentWord) == -1){
                    *errorFound= 1;
                }
                
            }else{
                printf("invalid comend in line %d\n",lineCount);
                
            }
            
        }

        currentSymbol = NULL;
        memset(line,0,LINE_LEN);

    }

    if(*errorFound == 1){
        printf("WAS ERROR\n");
    }else{
        AddICToData(&head,*IC);
    }
    
    return head;



}

int operationHandler(int* IC,int lineNum,char* theOperation){

    char firstOperand[LINE_LEN] = {0};
    char secondOperand[LINE_LEN] = {0};

    char* theOperands;
    int expectedOperands;

    expectedOperands = amountOfOperands(theOperation);
    theOperands = strtok(NULL,"");

    /*Checking if operation is valid*/
    if(checkOperationLine(expectedOperands,firstOperand,secondOperand,lineNum,theOperands)){
        if(expectedOperands == 0){
            return 1;
        }
        /*Changing the IC according to the operation*/
        return changeICByCommand(expectedOperands,IC,firstOperand,secondOperand,lineNum,theOperation);
    }
    return -1;

}

int checkOperationLine(int numOfOperands,char* firstOperand,char* secondOperand,int lineNum,char* theOperands){
    int i;
    int j;
    if(numOfOperands == 0){
        if(!isEmpty(theOperands)){
            printf("cant be a operation with no operands that have more after the operation in line %d\n",lineNum);
            return 0;
        }

    }

    if(numOfOperands == 1){
        /*We get the first operand*/
        removeRightWhiteSpaces(theOperands);
        for(i = 0;i<strlen(theOperands);i++){
            firstOperand[i] = theOperands[i];
        }
        removeRightWhiteSpaces(firstOperand);
        removeLeftWhiteSpaces(firstOperand);
        if(operandError(firstOperand,lineNum)){
            return 0;/*The operand contains errors*/
        }
        
    }

    if(numOfOperands == 2){
        /*We get the operands*/
        for(i = 0;i<strlen(theOperands) && theOperands[i] != ',';i++){
            firstOperand[i] = theOperands[i];
        }
        if(i == (strlen(theOperands)-1)){
            printf("need be 2 operands in line %d\n",lineNum);
            return 0;
        }
        
        removeRightWhiteSpaces(firstOperand);
        removeLeftWhiteSpaces(firstOperand);
        if(operandError(firstOperand,lineNum)){
            return 0;/*The operand contains errors*/
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
            return 0;/*The operand contains errors*/
        }

    }

    return 1;
}

int operandError(char* operand,int lineNum){
    int i;

    for(i = 0;i<strlen(operand);i++){
        if(operand[i] == '\t' || operand[i] == ' '){
            printf("spaces in operand line : %d\n",lineNum);
            return 1;
        }
        if(operand[i] == ','){
            printf("to many operands in line : %d\n",lineNum);
            return 1;
        }
    }
    if(strlen(operand) == 0 || endOfLine(operand)){
        printf("operand missing in line %d\n",lineNum);
        return 1;
    }
    if(isOperation(operand)){
        printf("operand cant be a operation line: %d\n",lineNum);
        return 1;
    }
    if(isDirective(operand)){
        printf("operand cant be a directive line: %d\n",lineNum);
        return 1;
    }
    if(operand[0] == ','){
        printf("to many commas in line : %d\n",lineNum);
        return 1;
    }

    return 0;
}

int changeICByCommand(int numOfOperands,int* IC,char* firstOperand,char* secondOperand,int lineNum,char* theOperation){

    int firstAddressingMethod = 0;
    int secondAddressingMethod = 0;

    if(numOfOperands == 1){
        firstAddressingMethod = addressingMethodType(firstOperand,lineNum);

        if(firstAddressingMethod == -1){/* -1 is an error of  addressing method*/
            return -1;
        }
        
        if(!isDestinationAddressingMethod(theOperation,firstAddressingMethod)){
            printf("not the right adressing Method to the destination Operand in line: %d\n",lineNum);
            return -1;
        }
        
        addToIC(IC,firstAddressingMethod,0);/*is for no previous addressing method*/
        
    }

    if(numOfOperands == 2){
        
        firstAddressingMethod = addressingMethodType(firstOperand,lineNum);
        secondAddressingMethod = addressingMethodType(secondOperand,lineNum);
        
        if(firstAddressingMethod == -1 || secondAddressingMethod == -1){/* -1 is an error of  addressing method*/
            return -1;
        }

        if(!isSourceAddressingMethod(theOperation,firstAddressingMethod)){
            printf("not the right adressing Method to the source Operand in line: %d \n",lineNum);
            return -1;
        }

        addToIC(IC,firstAddressingMethod,0);/*is for no previous addressing method*/


        if(!isDestinationAddressingMethod(theOperation,secondAddressingMethod)){
            printf("not the right adressing Method to the destination Operand in line: %d \n",lineNum);
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

int directiveHandler(symbolTable** head,int *DC,int lineCount,char* theDirectiv,symbolTable* currentSymbol){


    if(strcmp(theDirectiv,".data") == 0){
        return dataHandler(DC,theDirectiv,currentSymbol,lineCount);
    }

    if(strcmp(theDirectiv,".string") == 0){
        return stringHandler(DC,theDirectiv,currentSymbol,lineCount);
    }

    if(strcmp(theDirectiv,".struct") == 0){
        return structHandler(DC,theDirectiv,currentSymbol,lineCount);
    }

    if(strcmp(theDirectiv,".extern") == 0){
        return externHandler(head,DC,theDirectiv,currentSymbol,lineCount);
    }

    if(strcmp(theDirectiv,".entry") == 0){
        return entryHandler(head,DC,theDirectiv,currentSymbol,lineCount);
    }

    printf("invalid directiv in line: %d\n",lineCount);
    return -1;
}





