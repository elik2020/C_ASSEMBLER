#ifndef DIRECTIVES_HANDLER_H
#define DIRECTIVES_HANDLER_H


#include "../Utility/all_definitions.h"
#include "../Utility/symbol_table.h"

int isDirective(char* word);
int dataHandler(int* DC,char* theDirectiv,symbolTable* currentSymbol,int lineNum);
int structHandler(int* DC,char* theDirectiv,symbolTable* currentSymbol,int lineNum);
int stringHandler(int* DC,char* theDirectiv,symbolTable* currentSymbol,int lineNum);
int externHandler(symbolTable** head,int* DC,char* theDirectiv,symbolTable* currentSymbol,int lineNum);
int entryHandler(symbolTable** head,int* DC,char* theDirectiv,symbolTable* currentSymbol,int lineNum);


#endif