#ifndef OPERATION_HANDLER_H
#define OPERATION_HANDLER_H


#include "../Utility/general_functions.h"

int isOperation(char* name);
int amountOfOperands(char* name);
int isSourceAddressingMethod(char* operation,int addressingMethod);
int isDestinationAddressingMethod(char* operation,int addressingMethod);


#endif