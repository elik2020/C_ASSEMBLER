
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
#define NUM_OF_OPERATIONS 16
#define NUM_OF_DIRECTIVES 5
#define SPACES " \t\n\v\f\r"
#define SPACES_AND_COMMA " \t\n\v\f\r,"


typedef enum boolean{FALSE,TRUE} boolean;

enum error{missingComma=1,extraComma,missingSpace,wrongCommaPlace,extraChars,extraSpace};
enum addressingMethods{IMMEDIATE_ADDRESS,DIRECT_ADDRESS,STRUCT_ADDRESS,REGISTER_ADDRESS,addressingError = -1};
enum typeOfSymbol {
    CODE_SYMBOL=1,/* Contains an action like move */
    DATA_SYMBOL,/*.string or .data*/
    EXTERNAL_SYMBOL, /* .extern */
    STRUCT_SYMBOL /* .struct */};





const char base32chars[] = "!@#$%^&*<>abcdefghijklmnopqrstuv";












#endif 