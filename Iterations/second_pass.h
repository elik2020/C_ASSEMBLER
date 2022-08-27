#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "../Utility/symbol_table.h"
#include "../Utility/general_functions.h"

void second_pass(char* fileName,int isEntry,int endIC,int endDC,symbolTable* head);
void addFinalICAndDC(int endIC, int endDC,FILE* operationFile);
void finish_second_pass(char *fileName,FILE* entFile,FILE* extFile,FILE* operationFile,FILE* dataFile,FILE* amFile);
void close_second_pass(char *fileName,FILE* entFile,FILE* extFile,FILE* operationFile,FILE* dataFile,FILE* amFile);
void deletingFile(char *fileName,char* fileExtension);
int directiveEncoder(symbolTable* head,int* IC,int lineNum,char* theDirectiv,FILE* entFile,FILE* dataFile);
int externCheck(symbolTable* head,int lineNum);
int entryCheck(symbolTable* head,int lineNum,FILE* entFile);
void dataEncoder(int* IC,FILE* dataFile,int lineNum);
void stringEncoder(int* IC,FILE* dataFile,int lineNum);
void structEncoder(int* IC,FILE* dataFile,int lineNum);
void convert_to_base32(unsigned int num,char* keepBase32);
void encoded_to_file(FILE* fileToWrite ,char* numBase32,int IC);
int getOperands(symbolTable* head,int* IC,FILE* operationFile,int lineNum,FILE* extFile,char* theOperation);
int encodeOperation(symbolTable* head,int* IC,int numOfOperands,char* firstOperand,char* secondOperand,int lineNum,FILE* operationFile,FILE* extFile,char* theOperation);
int encodeAddressingMethod(symbolTable* head,int* IC,int addressingMethod,char* theOperand,int destinationAddressing,int lineNum,FILE* operationFile,FILE* extFile);
int encodeDirectAddress(symbolTable* head,int* IC,char* theOperand,int lineNum,FILE* operationFile,FILE* extFile);
int encodeImmediateAddress(int* IC,char* theOperand,int lineNum,FILE* operationFile);
int encodeStructAddress(symbolTable* head,int* IC,char* theOperand,int lineNum,FILE* operationFile,FILE* extFile);

#endif 