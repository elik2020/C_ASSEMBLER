#include "../Utility/operation_handler.h"

static const struct operationTable{

    const char *name;
    unsigned int opcode;
    unsigned int numOfOperands;
    unsigned int first_operand_valid[NUM_OF_ADDRESSINGS];
    unsigned int second_operand_valid[NUM_OF_ADDRESSINGS];
} operationTable[] = {{"mov",0,2,{1,1,1,1},{0,1,1,1}},
                      {"cmp",1,2,{1,1,1,1},{1,1,1,1}},
                      {"add",2,2,{1,1,1,1},{0,1,1,1}},
                      {"sub",3,2,{1,1,1,1},{0,1,1,1}},
                      {"not",4,1,{0,0,0,0},{0,1,1,1}},
                      {"clr",5,1,{0,0,0,0},{0,1,1,1}},
                      {"lea",6,2,{0,1,1,0},{0,1,1,1}},
                      {"inc",7,1,{0,0,0,0},{0,1,1,1}},
                      {"dec",8,1,{0,0,0,0},{0,1,1,1}},
                      {"jmp",9,1,{0,0,0,0},{0,1,1,1}},
                      {"bne",10,1,{0,0,0,0},{0,1,1,1}},
                      {"get",11,1,{0,0,0,0},{0,1,1,1}},
                      {"prn",12,1,{0,0,0,0},{1,1,1,1}},
                      {"jsr",13,1,{0,0,0,0},{0,1,1,1}},
                      {"rts",14,0,{0,0,0,0},{0,0,0,0}},
                      {"hlt",15,0,{0,0,0,0},{0,0,0,0}}};

int isOperation(char* name){
    int i;
    if(name == NULL){
        return FALSE;
    }
    for(i = 0;i<NUM_OF_OPERATIONS;i++){
        if(strcmp(name,operationTable[i].name) == 0){
            return TRUE;
        }
    }
    return FALSE;
}

int amountOfOperands(char* operation){
    int i;
    for(i = 0;i<NUM_OF_OPERATIONS;i++){
        if(strcmp(operation,operationTable[i].name) == 0){
            return operationTable[i].numOfOperands;
        }
    }
    return -1;
}

int isSourceAddressingMethod(char* operation,int addressingMethod){
    int i;
    for(i = 0;i<NUM_OF_OPERATIONS;i++){
        if(strcmp(operation,operationTable[i].name) == 0){
            return operationTable[i].first_operand_valid[addressingMethod] == 1;
        }
    }
    return -1;
}

int isDestinationAddressingMethod(char* operation,int addressingMethod){
    int i;
    for(i = 0;i<NUM_OF_OPERATIONS;i++){
        if(strcmp(operation,operationTable[i].name) == 0){
            return operationTable[i].second_operand_valid[addressingMethod] == 1;
        }
    }
    return -1;
}