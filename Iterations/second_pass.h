#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "../Utility/symbol_table.h"
#include "../Utility/general_functions.h"

/**
 * @brief does the second pass on the am file
 * 
 * @param fileName - the name of the file that we're dealing with
 * @param isEntry - int which shows if we found an entry in the first iteration
 * @param endIC - the final IC by the end of the first iteration
 * @param endDC - the final DC by the end of the first iteration
 * @param head - the pointer to the head of the symbol table
 */
void second_pass(char* fileName,int isEntry,int endIC,int endDC,symbolTable* head);
/**
 * @brief adds to the start of the output file the final IC and DC
 * 
 * @param endIC - the final IC by the end of the first iteration
 * @param endDC - the final DC by the end of the first iteration
 * @param operationFile - the file to which we translate all the operation commands
 */
void addFinalICAndDC(int endIC, int endDC,FILE* operationFile);
/**
 * @brief it unites the data and operation files into the object file, and closes all the rest of the files
 * 
 * @param fileName - the name of the file that we're dealing with
 * @param entFile - the file in which we write all the ".entry" which we've found
 * @param extFile - the file in which we write all the extern symbols which we've found in the code
 * @param operationFile - the file to which we translate all the operation commands
 * @param dataFile - the file to which we translate all the data commands
 * @param amFile - the am file which we get from the pre assembler
 */
void finish_second_pass(char *fileName,FILE* entFile,FILE* extFile,FILE* operationFile,FILE* dataFile,FILE* amFile); 
/**
 * @brief closes all the files in case we found an error
 * 
 * @param fileName - the name of the file that we're dealing with
 * @param entFile - the file in which we write all the ".entry" which we've found
 * @param extFile - the file in which we write all the extern symbols which we've found in the code
 * @param operationFile - the file to which we translate all the operation commands
 * @param dataFile - the file to which we translate all the data commands
 * @param amFile - the am file which we get from the pre assembler
 */
void close_second_pass(char *fileName,FILE* entFile,FILE* extFile,FILE* operationFile,FILE* dataFile,FILE* amFile);
/**
 * @brief removes a file
 * 
 * @param fileName - the name of the file that we're dealing with
 * @param fileExtension - the extention of the file
 */
void deletingFile(char *fileName,char* fileExtension);
/**
 * @brief if we find a directive, we deal with it using multiple functions
 * 
 * @param head - the pointer to the head of the symbol table
 * @param IC - the pointer to the IC
 * @param lineNum - the current line
 * @param theDirectiv - the directive which was found
 * @param entFile - the file in which we write all the ".entry" which we've found
 * @param dataFile - the file to which we translate all the data commands
 * @return int we return -1 if there's an error, 1 if there is not
 */
int directiveEncoder(symbolTable* head,int* IC,int lineNum,char* theDirectiv,FILE* entFile,FILE* dataFile);
/**
 * @brief checks if there's errors in the extern
 * 
 * @param head - the pointer to the head of the symbol table
 * @param lineNum - the current line
 * @return int we return -1 if there's an error, 1 if there is not
 */
int externCheck(symbolTable* head,int lineNum);
/**
 * @brief deals in case we encounter ".entry"
 * 
 * @param head - the pointer to the head of the symbol table
 * @param lineNum - the current line
 * @param entFile - the file in which we write all the ".entry" which we've found
 * @return int we return -1 if there's an error, 1 if there is not
 */
int entryCheck(symbolTable* head,int lineNum,FILE* entFile);
/**
 * @brief encodes in case we found ".data" 
 * 
 * @param IC - the pointer to the IC
 * @param dataFile - the file to which we translate all the data commands
 * @param lineNum - the current line
 */
void dataEncoder(int* IC,FILE* dataFile,int lineNum);
/**
 * @brief encodes in case we found ".string" 
 * 
 * @param IC - the pointer to the IC
 * @param dataFile - the file to which we translate all the data commands
 * @param lineNum - the current line
 */
void stringEncoder(int* IC,FILE* dataFile,int lineNum);
/**
 * @brief encodes in case we found ".struct" 
 * 
 * @param IC - the pointer to the IC
 * @param dataFile - the file to which we translate all the data commands
 * @param lineNum - the current line
 */
void structEncoder(int* IC,FILE* dataFile,int lineNum);
/**
 * @brief converts a number to base 32 and saves it in a string
 * 
 * @param num - the number that we want to convert
 * @param keepBase32 - the string to which we save the converted number
 */
void convert_to_base32(unsigned int num,char* keepBase32);
/**
 * @brief writes in a file the translated word and the translated IC
 * 
 * @param fileToWrite - the file that we write in
 * @param numBase32 - the translation of a word (to base 32)
 * @param IC - the pointer to the IC
 */
void encoded_to_file(FILE* fileToWrite ,char* numBase32,int IC);
/**
 * @brief gets the operands of the command and uses the functions that deal with the operands
 * 
 * @param head - the pointer to the head of the symbol table
 * @param IC - the pointer to the IC
 * @param operationFile - the file to which we translate all the operation commands
 * @param lineNum - the current line
 * @param extFile - the file in which we write all the extern symbols which we've found in the code
 * @param theOperation - the operation that we've found
 * @return int we return -1 if there's an error, 1 if there is not
 */
int getOperands(symbolTable* head,int* IC,FILE* operationFile,int lineNum,FILE* extFile,char* theOperation);
/**
 * @brief gets the addressing methods of the operands and translates the first word of the command and uses a function to deal with the operands
 * 
 * @param head - the pointer to the head of the symbol table
 * @param IC - the pointer to the IC
 * @param numOfOperands - the amount of operands needed for the operation
 * @param firstOperand - the first operand that we deal with
 * @param secondOperand - the second operand that we deal with
 * @param lineNum - the current line
 * @param operationFile - the file to which we translate all the operation commands
 * @param extFile - the file in which we write all the extern symbols which we've found in the code
 * @param theOperation - the operation that we've found
 * @return int we return -1 if there's an error, 1 if there is not
 */
int encodeOperation(symbolTable* head,int* IC,int numOfOperands,char* firstOperand,char* secondOperand,int lineNum,FILE* operationFile,FILE* extFile,char* theOperation);
/**
 * @brief calls the right functions for the addressing method that we've found
 * 
 * @param head - the pointer to the head of the symbol table
 * @param IC - the pointer to the IC
 * @param addressingMethod - the addressing method
 * @param theOperand - the operand
 * @param destinationAddressing - represents whether the addressing method is destination or not
 * @param lineNum - the current line
 * @param operationFile - the file to which we translate all the operation commands
 * @param extFile - the file in which we write all the extern symbols which we've found in the code
 * @return int we return -1 if there's an error, 1 if there is not
 */
int encodeAddressingMethod(symbolTable* head,int* IC,int addressingMethod,char* theOperand,int destinationAddressing,int lineNum,FILE* operationFile,FILE* extFile);
/**
 * @brief deals in case we have a direct address
 * 
 * @param head - the pointer to the head of the symbol table
 * @param IC - the pointer to the IC
 * @param theOperand - the operand
 * @param lineNum - the current line
 * @param operationFile - the file to which we translate all the operation commands
 * @param extFile - the file in which we write all the extern symbols which we've found in the code
 * @return int we return -1 if there's an error, 1 if there is not
 */
int encodeDirectAddress(symbolTable* head,int* IC,char* theOperand,int lineNum,FILE* operationFile,FILE* extFile);
/**
 * @brief deals in case we have an immediate address
 * 
 * @param IC - the pointer to the IC
 * @param theOperand - the operand
 * @param lineNum - the current line
 * @param operationFile - the file to which we translate all the operation commands
 * @return int we return -1 if there's an error, 1 if there is not
 */
int encodeImmediateAddress(int* IC,char* theOperand,int lineNum,FILE* operationFile);
/**
 * @brief deals in case we have a struct address
 * 
 * @param head - the pointer to the head of the symbol table
 * @param IC - the pointer to the IC
 * @param theOperand - the operand
 * @param lineNum - the current line
 * @param operationFile - the file to which we translate all the operation commands
 * @param extFile - the file in which we write all the extern symbols which we've found in the code
 * @return int we return -1 if there's an error, 1 if there is not
 */
int encodeStructAddress(symbolTable* head,int* IC,char* theOperand,int lineNum,FILE* operationFile,FILE* extFile);


#endif 