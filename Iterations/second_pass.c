#include "../Iterations/second_pass.h"
#include "../Utility/files.h"
#include "../Utility/symbol_table.h"
#include "../Utility/operation_handler.h"
#include "../Utility/general_functions.h"
#include "../Utility/directives_handler.h"
#include "../Iterations/first_pass.h"

void second_pass(char* fileName,int isEntry,int endIC,int endDC,symbolTable* head){

    int lineNum = 0;
    int isError = 0;
    char line[LINE_LEN] = {0};
    char* currentWord = NULL;
    int IC = 99;
    FILE* entFile = NULL,*extFile = NULL,*operationFile = NULL,*dataFile = NULL,*amFile = NULL;
    /*opening all the files*/
    if(table_contain_extern(head)){
        extFile = open_file(fileName,".ext","w");
    }
    if(isEntry){
        entFile = open_file(fileName,".ent","w");
    }
    amFile = open_file(fileName,".am","r");
    operationFile = open_file(fileName,".oper","w+");
    dataFile = open_file(fileName,".data","w+");
    /*add the finel IC and DC to file*/
    addFinalICAndDC(endIC,endDC,operationFile);




    while(!feof(amFile)){
        fgets(line, LINE_LEN, amFile); 
        lineNum++;

        if(ignoreLine(line)){/*Check if line is empty or if it start with ;*/
            continue;
        }


        currentWord = strtok(line, SPACES);/*get the first word in the line*/

        if(isEmpty(currentWord)){
            continue;
        }
        
        if(checkLabel(currentWord)){/*if the first word is a label we skeep it*/
            currentWord = strtok(NULL, SPACES);
        }
        
        if(isDirective(currentWord)){/*we check if its a directive*/

            if(directiveEncoder(head,&IC,lineNum,currentWord,entFile,dataFile) == -1){
                isError = 1;
            }
            
        }else{
            
            if(isOperation(currentWord)){/*we check if its a operation*/

                if(getOperands(head,&IC,operationFile,lineNum,extFile,currentWord) == -1){
                    isError = 1;
                }
                
            }
            
        }
    }

    if(isError == 1){/*if we found an error we close all the files we created*/
        close_second_pass(fileName,entFile,extFile,operationFile,dataFile,amFile);
        printf("error detact\n\n");
    }else{
        finish_second_pass(fileName,entFile,extFile,operationFile,dataFile,amFile);/*if ther was no errors we create the object file*/
    }

    free_symbol_table(head);/*free the sembol tabel we created in the first pass*/


}

void addFinalICAndDC(int endIC, int endDC,FILE* operationFile){
    char ICToBase32[3] = {0};
    char DCToBase32[3] = {0};
    
    convert_to_base32((endIC-100),ICToBase32);
    convert_to_base32(endDC,DCToBase32);
    
    /*if the number of the finel IC or DC is lower than 32 so we delet the ! in the start of the encode of the numbers to base 32*/
    if(endDC< 32){
        DCToBase32[0] = DCToBase32[1];
        DCToBase32[1] = '\0';
    }

    if(endIC-100 < 32){
        ICToBase32[0] = ICToBase32[1];
        ICToBase32[1] = '\0';
    }

    fprintf(operationFile, "%s\t%s\n\n", ICToBase32,DCToBase32);

}

void finish_second_pass(char *fileName,FILE* entFile,FILE* extFile,FILE* operationFile,FILE* dataFile,FILE* amFile){
    FILE* obFile = NULL;
    char ch;
    obFile = open_file(fileName,".ob","w");

    fseek(operationFile, 0, SEEK_SET);
    fseek(dataFile, 0, SEEK_SET);

    while((ch = fgetc(operationFile)) != EOF){
        fputc(ch,obFile);
    }

 
    while((ch = fgetc(dataFile)) != EOF){
        fputc(ch,obFile);
    }

    fclose(obFile);
    fclose(operationFile);
    fclose(dataFile);
    fclose(amFile);
    deletingFile(fileName,".oper");
    deletingFile(fileName,".data");
    if(entFile != NULL){
        fclose(entFile);
    }
    if(extFile != NULL){
        fclose(extFile);
    }

}

void close_second_pass(char *fileName,FILE* entFile,FILE* extFile,FILE* operationFile,FILE* dataFile,FILE* amFile){
    fclose(operationFile);
    fclose(dataFile);
    fclose(amFile);
    if(entFile != NULL){
        fclose(entFile);
        deletingFile(fileName,".ent");
    }
    if(extFile != NULL){
        fclose(extFile);
        deletingFile(fileName,".ext");
    }
    deletingFile(fileName,".oper");
    deletingFile(fileName,".data");

}

void deletingFile(char *fileName,char* fileExtension){
    char* tempName = (char*)malloc(sizeof(fileName) + sizeof(fileExtension)+1);

    strcpy(tempName,fileName);
    strcat(tempName,fileExtension);

    remove(tempName);

    free(tempName);
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

    return 1;
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

    numAfterComma = strtok(NULL,",");

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
    char numBase32[3] = {0};
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
    rightSide = num & mask;

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

    if(numOfOperands == 0){
        return encodeOperation(head,IC,numOfOperands,firstOperand,secondOperand,lineNum,operationFile,extFile,theOperation);
    }

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

        removeRightWhiteSpaces(secondOperand);
        removeLeftWhiteSpaces(secondOperand);

        return encodeOperation(head,IC,numOfOperands,firstOperand,secondOperand,lineNum,operationFile,extFile,theOperation);
    }
    return -1;
}

int encodeOperation(symbolTable* head,int* IC,int numOfOperands,char* firstOperand,char* secondOperand,int lineNum,FILE* operationFile,FILE* extFile,char* theOperation){
    char toBase32[3] = {0};
    char firstOperandCopy[LINE_LEN] = {0};
    char secondOperandCopy[LINE_LEN] = {0};

    int firstAddressingMethod = 0,secondAddressingMethod = 0,opCode = 0,registerNum1 = 0,registerNum2 = 0;
    

    opCode = getOpCode(theOperation);


    if(numOfOperands == 0){
        (*IC)++;
        convert_to_base32(opCode << 6,toBase32);
        encoded_to_file(operationFile,toBase32,(*IC));
        return 1;
    }

    if(numOfOperands == 1){
        strcpy(firstOperandCopy,firstOperand);
        (*IC)++;
        firstAddressingMethod = addressingMethodType(firstOperandCopy,lineNum);
        convert_to_base32(opCode << 6 | firstAddressingMethod << 2,toBase32);
        encoded_to_file(operationFile,toBase32,(*IC));

        return encodeAddressingMethod(head,IC,firstAddressingMethod,firstOperand,TRUE,lineNum,operationFile,extFile);

    }

    if(numOfOperands == 2){
        strcpy(firstOperandCopy,firstOperand);
        strcpy(secondOperandCopy,secondOperand);
        
        firstAddressingMethod = addressingMethodType(firstOperandCopy,lineNum);
        secondAddressingMethod = addressingMethodType(secondOperandCopy,lineNum);
        
        (*IC)++;


        convert_to_base32(opCode << 6 | firstAddressingMethod << 4 | secondAddressingMethod << 2,toBase32);
        encoded_to_file(operationFile,toBase32,(*IC));

        if(firstAddressingMethod == REGISTER_ADDRESS && secondAddressingMethod == REGISTER_ADDRESS){
            (*IC)++;
            registerNum1 = firstOperand[1] - '0';
            registerNum2 = secondOperand[1] - '0';
            convert_to_base32( registerNum1 << 6 | registerNum2 << 2,toBase32);
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

    return -1;
}

int encodeAddressingMethod(symbolTable* head,int* IC,int addressingMethod,char* theOperand,int destinationAddressing,int lineNum,FILE* operationFile,FILE* extFile){
    char registerNumBase32[3] = {0};
    int registerNum = 0;

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
            registerNum = theOperand[1] - '0';
            convert_to_base32(registerNum << 2,registerNumBase32);
            encoded_to_file(operationFile,registerNumBase32,(*IC));
        }else{
            registerNum = theOperand[1] - '0';
            convert_to_base32(registerNum << 6,registerNumBase32);
            encoded_to_file(operationFile,registerNumBase32,(*IC));
        }
        return 0;
    }

    return -1;
    
}

int encodeDirectAddress(symbolTable* head,int* IC,char* theOperand,int lineNum,FILE* operationFile,FILE* extFile){
    char toBase32[3] = {0};
    int ARE = 0;

    if(inSymbolTable(head,theOperand)){
        if(is_extern(head,theOperand)){
            ARE = 1;
            (*IC)++;
            convert_to_base32((*IC),toBase32);
            fprintf(extFile, "%s\t%s\n", theOperand,toBase32);
            convert_to_base32(symbol_address(head,theOperand) << 2 | ARE,toBase32);
            encoded_to_file(operationFile,toBase32,(*IC));
            return 1;

        }else{
            ARE = 2;
            (*IC)++;
            convert_to_base32(symbol_address(head,theOperand) << 2 | ARE,toBase32);
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
    char toBase32[3] = {0};
    char* afterDot;
    char* beforeDot;

    int numInStruct = 0;
    int ARE = 0;

    beforeDot = strtok(theOperand, ".");
    afterDot = strtok(NULL, ".");

    

    if(inSymbolTable(head,beforeDot)){
        if(is_extern(head,beforeDot)){
            ARE = 1;
            (*IC)++;
            convert_to_base32((*IC),toBase32);
            fprintf(extFile, "%s\t%s\n", theOperand,toBase32);
            convert_to_base32(symbol_address(head,theOperand) << 2| ARE,toBase32);
            encoded_to_file(operationFile,toBase32,(*IC));
            

        }else{
            if(is_struct(head,beforeDot)){
                ARE = 2;
                (*IC)++;
                convert_to_base32(symbol_address(head,theOperand) << 2 | ARE,toBase32);
                encoded_to_file(operationFile,toBase32,(*IC));
                
            }else{
                printf("Not using a struct symbol in line: %d",lineNum);
                return -1;
            }
            
        }

    }else{
        printf("Non existing symbol in line: %d",lineNum);
        return -1;
    }
    
    (*IC)++;
    stringToNumber(&numInStruct,afterDot);
    convert_to_base32(numInStruct << 2,toBase32);
    encoded_to_file(operationFile,toBase32,(*IC));

    return 1;

}



