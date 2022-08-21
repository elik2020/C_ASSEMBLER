#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include "../Utility/all_definitions.h"
#include "../Utility/files.h"
#include "../Utility/symbol_table.h"
#include "../Utility/operation_handler.h"
#include "../Utility/general_functions.h"
#include "../Utility/directives_handler.h"

symbolTable first_pass(char* fileName,int* errorFound,int* entryFound);
int operationHandler(int* IC,int lineNum,char* theOperation);
int checkOperationLine(int numOfOperands,char* firstOperand,char* secondOperand,int lineNum,char* theOperands);
int operandError(char* operand,int lineNum);
int changeICByCommand(int numOfOperands,int* IC,char* firstOperand,char* secondOperand,int lineNum,char* theOperation);
void addToIC(int* IC,int currMethod,int prevMethod);
int directiveHandler(symbolTable** head,int *DC,int lineCount,char* theDirectiv,symbolTable* currentSymbol);

#endif 