#ifndef OPERATION_HANDLER_H
#define OPERATION_HANDLER_H


#include "../Utility/general_functions.h"

/**
 * @brief checks if the word we got is an operation
 * 
 * @param name - the word we check
 * @return int we return 0 if it is not, 1 if it is
 */
int isOperation(char* name);
/**
 * @brief checks the amount of operands that we need for the operation
 * 
 * @param name - the operation
 * @return int the amount of operands that we need for the operation
 */
int amountOfOperands(char* name);
/**
 * @brief checks if the addressing method fits the source addressing method of the operation
 * 
 * @param operation - the operation
 * @param addressingMethod - the addressing method
 * @return int we return 0 if it is not, 1 if it is
 */
int isSourceAddressingMethod(char* operation,int addressingMethod);
/**
 * @brief checks if the addressing method fits the destination addressing method of the operation
 * 
 * @param operation - the operation
 * @param addressingMethod - the addressing method
 * @return int we return 0 if it is not, 1 if it is
 */
int isDestinationAddressingMethod(char* operation,int addressingMethod);
/**
 * @brief returns the op code of the operation
 * 
 * @param operation - the operation
 * @return int the opcode 
 */
int getOpCode(char* operation);

#endif