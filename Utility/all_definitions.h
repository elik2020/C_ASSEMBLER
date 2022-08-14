
#ifndef ALL_DEFINITIONS_H
#define ALL_DEFINITIONS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define LINE_LEN 82  
#define LABEL_LEN 31
#define NUM_OF_ADDRESSINGS 4
#define REGISTER_NAME_LENGTH 2


typedef enum boolean{FALSE,TRUE} boolean;

enum error{missingComma=1,extraComma,missingSpace,wrongCommaPlace,extraChars,extraSpace};
enum addressingMethods{IMMEDIATE_ADDRESS,DIRECT_ADDRESS,STRUCT_ADDRESS,REGISTER_ADDRESS,addressingError = -1};
enum directives {DATA, STRING, STRUCT, ENTRY, EXTERN,UNKNOWN_TYPE};
typedef enum typeOfSymbol {
    CODE_SYMBOL=1,/* Contains an action like move */
    DATA_SYMBOL,/*.string or .data*/
    EXTERNAL_SYMBOL, /* .extern */
    STRUCT_SYMBOL /* .struct */} typeOfSymbol;


static const struct operationTable{

    const char *name;
    unsigned int opcode;
    unsigned int operandNum;
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
                      {"prn",12,1,{0,0,0,0},{0,1,1,1}},
                      {"jsr",13,1,{0,0,0,0},{0,1,1,1}},
                      {"rts",14,0,{0,0,0,0},{0,0,0,0}},
                      {"hlt",15,0,{0,0,0,0},{0,0,0,0}}};


const char base32chars[] = "!@#$%^&*<>abcdefghijklmnopqrstuv";
const char *directives[] = {".data", ".string", ".struct", ".entry", ".extern"};











#endif 