#ifndef FIRST_PASS_H
#define FIRST_PASS_H


#include "../Utility/files.h"
#include "../Utility/symbol_table.h"
#include "../Utility/operation_handler.h"
#include "../Utility/general_functions.h"
#include "../Utility/directives_handler.h"

/**
 * @brief first pass, makes the first ineration, makes the symbol table and returns it to the main function.
 * 
 * @param fileName - the name of the file that we are processing
 * @param errorFound - int which checks if there was an error found
 * @param entryFound - int to check if there was a declaration of "entry"
 * @param IC - the IC of the assembler
 * @param DC - the DC of the assembler
 * @return symbolTable* returns the symbol table at the end of the iteration
 */
symbolTable* first_pass(char* fileName,int* errorFound,int* entryFound,int* IC,int* DC);
/**
 * @brief if we encounter an operation, the function uses another functions to deal with it
 * 
 * @param IC - the IC of the assembler
 * @param lineNum - the number of the current line
 * @param theOperation - the operation which was found
 * @return int we return -1 if there was an error, 1 if there was not
 */
int operationHandler(int* IC,int lineNum,char* theOperation);
/**
 * @brief the function gets the operands in the line and checks for errors in them
 * 
 * @param numOfOperands - the amount of operands which are needed for the operation
 * @param firstOperand - the second operand which was found
 * @param secondOperand - the first operand which was found
 * @param lineNum - the number of the current line
 * @param theOperands - the operands which were found
 * @return int we return 0 if there was an error, 1 if there was not
 */
int checkOperationLine(int numOfOperands,char* firstOperand,char* secondOperand,int lineNum,char* theOperands);
/**
 * @brief the function checks if there are errors in the operands
 * 
 * @param operand - the operand which we deal with
 * @param lineNum - the number of the current line
 * @return int we return 1 if there was an error, 0 if there was not
 */
int operandError(char* operand,int lineNum);
/**
 * @brief the function gets the addressing methods and checks if they fit the operation or not and we use a different function to change the IC according to the addresing methods
 * 
 * @param numOfOperands - the amount of operands which are needed for the operation
 * @param IC - the IC of the assembler
 * @param firstOperand - the first operand which was found
 * @param secondOperand - the second operand which was found
 * @param lineNum - the number of the current line
 * @param theOperation - the operation which was found
 * @return int we return -1 if there was an error, 1 if there was not
 */
int changeICByCommand(int numOfOperands,int* IC,char* firstOperand,char* secondOperand,int lineNum,char* theOperation);
/**
 * @brief the function changed the IC according to the addressing method
 * 
 * @param IC - the IC of the assembler
 * @param currMethod - the current addressing method
 * @param prevMethod - the previous addressing method
 */
void addToIC(int* IC,int currMethod,int prevMethod);
/**
 * @brief the function calls the right function if we found a directive
 * 
 * @param head - the pointer to the head of the function
 * @param DC - the DC of the assembler
 * @param lineCount - the line that we're at
 * @param theDirectiv - the directive that we have found
 * @param currentSymbol - the currect symbol that we are dealing with
 * @return int we return -1 if there was an error, 1 if there was not
 */
int directiveHandler(symbolTable** head,int *DC,int lineCount,char* theDirectiv,symbolTable* currentSymbol);

#endif 