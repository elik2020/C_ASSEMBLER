#ifndef DIRECTIVES_HANDLER_H
#define DIRECTIVES_HANDLER_H



#include "../Utility/general_functions.h"
#include "../Utility/symbol_table.h"

/**
 * @brief checks if the command is directive
 * 
 * @param word - the command
 * @return int we return 1 if it is, 0 if it is not
 */
int isDirective(char* word);
/**
 * @brief deals in case that we encounter ".data"
 * 
 * @param DC - the DC of the assembler
 * @param theDirectiv - the directive that we have found
 * @param currentSymbol - if there's a declaration of a symbol, this is the symbol that we are on
 * @param lineNum - the current line
 * @return int we return -1 if there's an error, 1 if there's no error
 */
int dataHandler(int* DC,char* theDirectiv,symbolTable* currentSymbol,int lineNum);
/**
 * @brief deals in case that we encounter ".struct"
 * 
 * @param DC - the DC of the assembler
 * @param theDirectiv - the directive that we have found
 * @param currentSymbol - if there's a declaration of a symbol, this is the symbol that we are on
 * @param lineNum - the current line
 * @return int we return -1 if there's an error, 1 if there's no error
 */
int structHandler(int* DC,char* theDirectiv,symbolTable* currentSymbol,int lineNum);
/**
 * @brief deals in case that we encounter ".string"
 * 
 * @param DC - the DC of the assembler
 * @param theDirectiv - the directive that we have found
 * @param currentSymbol - if there's a declaration of a symbol, this is the symbol that we are on
 * @param lineNum - the current line
 * @return int we return -1 if there's an error, 1 if there's no error
 */
int stringHandler(int* DC,char* theDirectiv,symbolTable* currentSymbol,int lineNum);
/**
 * @brief deals in case that we encounter ".extern"
 * 
 * @param head - double pointer to the head of the symbol table
 * @param DC - the DC of the assembler
 * @param theDirectiv - the directive that we have found
 * @param currentSymbol - if there's a declaration of a symbol, this is the symbol that we are on
 * @param lineNum - the current line
 * @return int we return -1 if there's an error, 1 if there's no error
 */
int externHandler(symbolTable** head,int* DC,char* theDirectiv,symbolTable* currentSymbol,int lineNum);
/**
 * @brief deals in case that we encounter ".entry"
 * 
 * @param head - double pointer to the head of the symbol table
 * @param DC - the DC of the assembler
 * @param theDirectiv - the directive that we have found
 * @param currentSymbol - if there's a declaration of a symbol, this is the symbol that we are on
 * @param lineNum - the current line
 * @return int we return -1 if there's an error, 1 if there's no error
 */
int entryHandler(symbolTable** head,int* DC,char* theDirectiv,symbolTable* currentSymbol,int lineNum);

#endif