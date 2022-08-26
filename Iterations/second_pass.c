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
            if(directiveEncoder(head,&IC,lineNum,currentWord,entFile,dataFile) == -1){
                isError = 1;
            }
            
        }else{
            
            if(isOperation(currentWord)){
                /*printf("start IC is : %d in line: %d\n",IC,lineCount);*/
                if(getOperands(head,&IC,operationFile,lineNum,extFile,currentWord) == -1){
                    isError = 1;
                }
                
                /*printf("END IC is : %d in line: %d\n\n",IC,lineCount);*/
            }
            
        }
    }

    if(isError == 1){
        close_second_pass();
    }
    
    free_symbol_table(head);


}

int directiveEncoder(symbolTable* head,int* IC,int lineNum,char* theDirectiv,FILE* entFile,FILE* dataFile){

    if(strcmp(theDirectiv,".data") == 0){
        dataEncoder(IC,dataFile,lineNum);
    }

    if(strcmp(theDirectiv,".string") == 0){
        stringEncoder(IC,dataFile,lineNum);
    }

    if(strcmp(theDirectiv,".struct") == 0){
        structEncoder(IC,dataFile,lineNum);
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
        
        stringToNumber(&num,numAfterComma);
        
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

void structEncoder(int* IC,FILE* dataFile,int lineNum){
    char* theStruct;
    char* numBase32[3] = {0};
    int num = 0;
    theStruct = strtok(NULL,",");

    
    if(isNumber(theStruct)){
        (*IC)++;
        stringToNumber(&num,theStruct);
        convert_to_base32(num,numBase32);
        encoded_to_file(dataFile,numBase32,(*IC));
    }

    stringEncoder(IC,dataFile,lineNum);
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

int getOperands(symbolTable* head,int* IC,FILE* operationFile,int lineNum,FILE* extFile,char* theOperation){

    char firstOperand[LINE_LEN] = {0};
    char secondOperand[LINE_LEN] = {0};
    char* theOperands;

    int numOfOperands = 0,i = 0,j = 0;

    numOfOperands = amountOfOperands(theOperation);
    theOperands = strtok(NULL,"");

    if(numOfOperands == 1){
        removeRightWhiteSpaces(theOperands);
        for(i = 0;i<strlen(theOperands);i++){
            firstOperand[i] = theOperands[i];
        }
        removeRightWhiteSpaces(firstOperand);
        removeLeftWhiteSpaces(firstOperand);
        
        return encodeOperation(head,IC,numOfOperands,firstOperand,secondOperand,lineNum,operationFile,extFile,theOperation);
    }

    if(numOfOperands == 2){
        for(i = 0;i<strlen(theOperands) && theOperands[i] != ',';i++){
            firstOperand[i] = theOperands[i];
        }
        
        removeRightWhiteSpaces(firstOperand);
        removeLeftWhiteSpaces(firstOperand);

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
        return encodeOperation(head,IC,numOfOperands,firstOperand,secondOperand,lineNum,operationFile,extFile,theOperation);
    }
}

int encodeOperation(symbolTable* head,int* IC,int numOfOperands,char* firstOperand,char* secondOperand,int lineNum,FILE* operationFile,FILE* extFile,char* theOperation){
    char toBase32[3] = {0};

    int firstAddressingMethod = 0,secondAddressingMethod = 0,opCode = 0;
    unsigned int combinedRegister = 0;

    opCode = getOpCode(theOperation);

    if(numOfOperands == 0){
        (*IC)++;
        convert_to_base32(opCode << 6,toBase32);
        encoded_to_file(operationFile,toBase32,(*IC));
        return 1;
    }

    if(numOfOperands == 1){
        (*IC)++;
        firstAddressingMethod = addressingMethodType(firstOperand,lineNum);
        convert_to_base32(opCode << 6 | firstAddressingMethod << 2,toBase32);
        encoded_to_file(operationFile,toBase32,(*IC));

        return encodeAddressingMethod(head,IC,firstAddressingMethod,firstOperand,TRUE,lineNum,operationFile,extFile);

    }

    if(numOfOperands == 2){
        firstAddressingMethod = addressingMethodType(firstOperand,lineNum);
        secondAddressingMethod = addressingMethodType(secondOperand,lineNum);
        (*IC)++;

        convert_to_base32(opCode << 6 | firstAddressingMethod << 4 | secondAddressingMethod << 2,toBase32);
        encoded_to_file(operationFile,toBase32,(*IC));

        if(firstAddressingMethod == REGISTER_ADDRESS && secondAddressingMethod == REGISTER_ADDRESS){
            (*IC)++;
            combinedRegister = registerNum(firstOperand) << 6 | registerNum(secondOperand) << 2;
            convert_to_base32(combinedRegister,toBase32);
            encoded_to_file(operationFile,toBase32,(*IC));
            return 1;
        }

        if(encodeAddressingMethod(head,IC,firstAddressingMethod,firstOperand,FALSE,lineNum,operationFile,extFile) == -1){
            return -1;
        }

        if(encodeAddressingMethod(head,IC,secondAddressingMethod,secondOperand,TRUE,lineNum,operationFile,extFile) == -1){
            return -1;
        }

        return 1;
    }
}

int encodeAddressingMethod(symbolTable* head,int* IC,char* addressingMethod,char* theOperand,int destinationAddressing,int lineNum,FILE* operationFile,FILE* extFile){
    char registerNumBase32[3] = {0};
    if(addressingMethod == DIRECT_ADDRESS){
        return encodeDirectAddress(head,IC,theOperand,lineNum,operationFile,extFile);
    }
    if(addressingMethod == IMMEDIATE_ADDRESS){
        return encodeImmediateAddress(IC,theOperand,lineNum,operationFile);
    }

    if(addressingMethod == STRUCT_ADDRESS){
        return encodeStructAddress(head,IC,theOperand,lineNum,operationFile,extFile);
    }

    if(addressingMethod == REGISTER_ADDRESS){
        (*IC)++;
        if(destinationAddressing){
            convert_to_base32(theOperand[1] << 2,registerNumBase32);
            encoded_to_file(operationFile,registerNumBase32,(*IC));
        }else{
            convert_to_base32(theOperand[1] << 6,registerNumBase32);
            encoded_to_file(operationFile,registerNumBase32,(*IC));
        }
        return 0;
    }
    
}

int encodeDirectAddress(symbolTable* head,int* IC,char* theOperand,int lineNum,FILE* operationFile,FILE* extFile){
    char toBase32[3] = {0};
    int ARE = 0;

    if(inSymbolTable(head,theOperand)){
        if(is_extern(theOperand)){
            ARE = 1;
            (*IC)++;
            encoded_to_file(operationFile,theOperand,(*IC));
            convert_to_base32(symbol_address(head,theOperand) << 8 | ARE,toBase32);
            encoded_to_file(operationFile,toBase32,(*IC));
            return 1;

        }else{
            ARE = 2;
            (*IC)++;
            convert_to_base32(symbol_address(head,theOperand) << 8 | ARE,toBase32);
            encoded_to_file(operationFile,toBase32,(*IC));
            return 1;
        }

    }else{
        printf("Non existing symbol in line: %d",lineNum);
        return -1;
    }
}

int encodeImmediateAddress(int* IC,char* theOperand,int lineNum,FILE* operationFile){
    char numBase32[3] = {0};
    int numInAddress = 0;
    char numInString[LINE_LEN] = {0};
    int i = 0,j = 0;

    for(i = 1;i<strlen(theOperand) && theOperand[i] != '\n';i++){
        numInString[j] = theOperand[i];
        j++;
    }
    (*IC)++;
    stringToNumber(&numInAddress,numInString);

    convert_to_base32(numInAddress << 2,numBase32);
    encoded_to_file(operationFile,numBase32,(*IC));

    return 1;



}

int encodeStructAddress(symbolTable* head,int* IC,char* theOperand,int lineNum,FILE* operationFile,FILE* extFile){
    char numBase32[3] = {0};
    char* afterDot;
    char* beforeDot;

    int numInStruct = 0;

    beforeDot = strtok(theOperand, ".");
    afterDot = strtok(NULL, ".");

    if(encodeDirectAddress(head,IC,theOperand,lineNum,operationFile,extFile) == -1){
        return -1;
    } 
    (*IC)++;
    stringToNumber(&numInStruct,afterDot);
    convert_to_base32(numInStruct << 2,numBase32);
    encoded_to_file(operationFile,numBase32,(*IC));

    return 1;

}


