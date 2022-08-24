#include "../Iterations/first_pass.h"


symbolTable* first_pass(char* fileName,int* errorFound,int* entryFound){

    int IC = 100;
    int DC = 0;
    FILE* amFile = NULL;
    symbolTable* head = NULL;
    symbolTable* currentSymbol = NULL;
    char line[LINE_LEN] = {0};
    char* currentWord = NULL;
    /*char labelName[LABEL_LEN] = {0};*/
    int lineCount =  0;
    amFile = open_file(fileName,".am","r");

    while(!feof(amFile)){

        fgets(line, LINE_LEN, amFile); 
        lineCount++;
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
            /*printf(" the word is: %s\n",currentWord);*/
            if(checkLabelName(currentWord)){
                if(inSymbolTable(head,currentWord)){
                    printf("label already exist label name: %s in line: %d\n",currentWord,lineCount);
                    *errorFound = 1;
                }else{
                    currentSymbol = insertSymbolAtEnd(&head,currentWord,IC);
                    currentWord = strtok(NULL,SPACES);
                }
            }else{
                printf("wrong label name in line: %d the name of the label is: %s \n",lineCount,currentWord);
                *errorFound= 1;
            }
            
        }

        

        if(isDirective(currentWord)){
            if(strcmp(currentWord,".entry") == 0){
                *entryFound = 1;
            }
            /*printf("the word is: %s\n\n",currentWord);*/
            if(directiveHandler(&head,&DC,lineCount,currentWord,currentSymbol) == -1){
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

        currentSymbol = NULL;
        memset(line,0,LINE_LEN);

    }

    if(*errorFound == 1){
        printf("IS ERROR\n");
    }else{
        AddICToData(&head,IC);
    }

    printf("finel IC: %d finle DC: %d\n",IC,DC);
    
    return head;



}

int operationHandler(int* IC,int lineNum,char* theOperation){

    char firstOperand[LINE_LEN] = {0};
    char secondOperand[LINE_LEN] = {0};

    char* theOperands;
    int expectedOperands;

    expectedOperands = amountOfOperands(theOperation);
    theOperands = strtok(NULL,"");
    /*printf("the IC is : %d",*IC);*/

    if(checkOperationLine(expectedOperands,firstOperand,secondOperand,lineNum,theOperands)){
        if(expectedOperands == 0){
            return 1;
        }
        /*printf("first operand is: %s second operand is: %s in line: %d\n",firstOperand,secondOperand,lineNum);*/
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
        removeRightWhiteSpaces(theOperands);
        for(i = 0;i<strlen(theOperands);i++){
            firstOperand[i] = theOperands[i];
        }
        removeRightWhiteSpaces(firstOperand);
        removeLeftWhiteSpaces(firstOperand);
        if(operandError(firstOperand,lineNum)){
            return 0;
        }
        
    }

    if(numOfOperands == 2){
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
            return 0;
        }
        ++i;
        j = 0;
        for(;i<strlen(theOperands)-1;i++){
            secondOperand[j] = theOperands[i];
            j++;
        }
        /*printf("the operand is: %s int line : %d\n",secondOperand,lineNum);*/
        removeRightWhiteSpaces(secondOperand);
        removeLeftWhiteSpaces(secondOperand);
        /*printf("the operand after is: %s int line : %d\n\n",secondOperand,lineNum);*/
        if(operandError(secondOperand,lineNum)){
            return 0;
        }

    }

    return 1;
}

int operandError(char* operand,int lineNum){
    int i;
    /*printf("the operand is: %s int line : %d\n",operand,lineNum);*/
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

        if(firstAddressingMethod == -1){
            return -1;
        }
        
        if(!isDestinationAddressingMethod(theOperation,firstAddressingMethod)){
            printf("not the right adressing Method to the destination Operand in line: %d\n",lineNum);
            return -1;
        }
        /*printf("the IC before is: %d the only adrresing mode is: %d in line: %d\n",*IC,firstAddressingMethod,lineNum);*/
        addToIC(IC,firstAddressingMethod,0);
        /*printf("ONLY after IC is: %d in line: %d\n\n",*IC,lineNum);*/
    }

    if(numOfOperands == 2){
        
        firstAddressingMethod = addressingMethodType(firstOperand,lineNum);
        secondAddressingMethod = addressingMethodType(secondOperand,lineNum);
        
        if(firstAddressingMethod == -1 || secondAddressingMethod == -1){
            return -1;
        }

        if(!isSourceAddressingMethod(theOperation,firstAddressingMethod)){
            printf("not the right adressing Method to the source Operand in line: %d \n",lineNum);
            return -1;
        }
        /*printf("the IC before is: %d the first adrresing mode is: %d in line: %d\n",*IC,firstAddressingMethod,lineNum);*/
        addToIC(IC,firstAddressingMethod,0);
        /*printf("FIRST after IC is: %d in line: %d\n\n",*IC,lineNum);*/

        if(!isDestinationAddressingMethod(theOperation,secondAddressingMethod)){
            printf("not the right adressing Method to the destination Operand in line: %d \n",lineNum);
            return -1;
        }
        /*printf("the IC before is: %d the second adrresing mode is: %d in line: %d\n",*IC,secondAddressingMethod,lineNum);*/
        addToIC(IC,secondAddressingMethod,firstAddressingMethod);
        /*printf("SECOND after IC is: %d in line: %d\n\n",*IC,lineNum);*/

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





