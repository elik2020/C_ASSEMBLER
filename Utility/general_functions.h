#ifndef GENERAL_FUNCTIONS_H
#define GENERAL_FUNCTIONS_H
/*this is the place where we store all the enums and include of repositories for the assembler*/

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
enum typeOfSymbol {CODE_SYMBOL=1,/* Contains an action like move */DATA_SYMBOL,/*.string or .data*/EXTERNAL_SYMBOL, /* .extern */STRUCT_SYMBOL /* .struct */};

/**
 * @brief checks if the current word is a register
 * 
 * @param name - the word we check
 * @return int if it is a register we return 1, otherwise 0
 */
int isRegister(char *name);
/**
 * @brief checks if the number is legal
 * 
 * @param number - the number we check
 * @return int if it is a register we return 1, otherwise 0
 */
int isNumber(char* number);
/**
 * @brief removes all the white spaces from the left of the line
 * 
 * @param line - the current line
 */
void removeLeftWhiteSpaces(char line[LINE_LEN]);
/**
 * @brief removes all the white spaces from the right of the line
 * 
 * @param line - the current line
 */
void removeRightWhiteSpaces(char line[LINE_LEN]);
/**
 * @brief if we encounter a line that we should ignore, we ignore it
 * 
 * @param line - the current line
 * @return int we return 1 if we need to ignore the line, otherwise we return 0
 */
int ignoreLine(char* line);

void copyCurrentWord(char *word, char *line);

void toNextWord(char *line);

void printError(char* error,int line,char* fileName);
/**
 * @brief checks if the word is a register, operation or a directive
 * 
 * @param word - the word we check 
 * @return int we return 1 if we need it is, otherwise we return 0
 */
int is_system_word(char* word);
/**
 * @brief checks if it is an end of a line
 * 
 * @param line - the current line
 * @return int we return 1 if it is, otherwise we return 0
 */
int endOfLine(char *line);
/**
 * @brief returns the addressing method according to the operand
 * 
 * @param operand - the operand
 * @param lineNum - the current line number
 * @return int the number of the addressing methods
 */
int addressingMethodType(char* operand,int lineNum);
/**
 * @brief checks if the line is empty
 * 
 * @param word - the line
 * @return int we return 1 if it is, otherwise we return 0
 */
int isEmpty(char* word);
/**
 * @brief returns the register number
 * 
 * @param theRegister - the register 
 * @return int the number of the register
 */
int registerNum(char* theRegister);
/**
 * @brief convers a string to a number
 * 
 * @param num -  the converted to number string
 * @param numString - the string that we convert
 */
void stringToNumber(int* num,char* numString);

#endif 