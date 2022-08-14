
#include "../Utility/symbol_table.h"



symbolTable* createSymbol(char* symbolName,int IC)
{
	symbolTable* newNode = (symbolTable*)malloc(sizeof(symbolTable));
    strcpy(newNode->name,symbolName);
    newNode->address = IC;
    newNode->next = NULL;
	return newNode;
}


void insertSymbolAtEnd(symbolTable** head,char* symbolName,int IC){

    symbolTable* newNode = createSymbol(symbolName,IC);

    if (!*head)
	{
	    *head = newNode;
	}
	else
	{
	    symbolTable* temp = *head;
        while (temp->next) 
        {
            temp = temp->next;
        }
        temp->next = newNode;
	}

}

int inSymbolTable(symbolTable* head,char* symbolName){
    while(head){
        if(strcmp(head->name,symbolName) == 0){
            return 1;
        }
        head = head->next;
    }
    return 0;
}

