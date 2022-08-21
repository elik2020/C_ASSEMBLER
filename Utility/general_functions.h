#ifndef GENERAL_FUNCTIONS_H
#define GENERAL_FUNCTIONS_H


#include "../Utility/all_definitions.h"
#include "../Utility/directives_handler.h"
#include "../Utility/operation_handler.h"

int isRegister(char *name);
int isNumber(char* number);
void removeLeftWhiteSpaces(char line[LINE_LEN]);
void removeRightWhiteSpaces(char line[LINE_LEN]);
int ignoreLine(char* line);
void copyCurrentWord(char *word, char *line);
void toNextWord(char *line);
int is_system_word(char* word);
void printError(char* error,int line,char* fileName);
int endOfLine(char *line);
int addressingMethodType(char* operand,int lineNum);
int isEmpty(char* word);

#endif 