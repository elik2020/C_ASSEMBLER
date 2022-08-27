
#include "../Utility/symbol_table.h"
#include "../Utility/general_functions.h"
#include "../Iterations/first_pass.h"


symbolTable* createSymbol(char* symbolName,int IC)
{
	symbolTable* newNode = (symbolTable*)malloc(sizeof(symbolTable));
    strcpy(newNode->name,symbolName);
    newNode->address = IC;
    newNode->next = NULL;
	return newNode;
}


symbolTable* insertSymbolAtEnd(symbolTable** head,char* symbolName,int IC){

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

    return newNode;

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

int is_extern(symbolTable* head,char* symbolName){
    while(head){
        if(strcmp(head->name,symbolName) == 0 && head->symbolType == EXTERNAL_SYMBOL){
            return 1;
        }
        head = head->next;
    }
    return 0;
}

int is_struct(symbolTable* head,char* symbolName){
    while(head){
        if(strcmp(head->name,symbolName) == 0 && head->symbolType == STRUCT_SYMBOL){
            return 1;
        }
        head = head->next;
    }
    return 0;
}


int symbol_address(symbolTable* head,char* symbolName){
    while(head){
        if(strcmp(head->name,symbolName) == 0){
            return head->address;
        }
        head = head->next;
    }
    return 0;
}


int checkLabel(char* word){
    if(word[strlen(word)-1] == ':'){
        word[strlen(word)-1] = '\0';
        return 1;
    }
    return 0;
    
}

int checkLabelName(char* name){
    int i = 0;

    if(!is_system_word(name) && isalpha(name[0]) && strlen(name) <= LABEL_LEN){
        for(i = 0;i<strlen(name);i++){
            if(!isalpha(name[i]) && !isdigit(name[i])){
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

void deleteSymbol(symbolTable** head, char* name)
{

    symbolTable* p = *head;
    symbolTable* dNode = NULL;

    if (*head)
    {
        if (0 == strcmp((*head)->name, name))
        {
            *head = (*head)->next;
            free(p);
        }
        else
        {
            while (p->next &&
                0 != strcmp(p->next->name, name))
            {
                p = p->next;
            }
            if (p->next)
            {
                dNode = p->next;
                p->next = dNode->next;
                free(dNode);
            }
        }
    }
}

void print_symbol_table(symbolTable* head){
    while (head != NULL)
    {
        printf("The label name: %s ; The address: %d ; The label type: %d\n",head->name,head->address,head->symbolType);
        head = head->next;
    }
}

void free_symbol_table(symbolTable* head){
    symbolTable* tmp;

    while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

void AddICToData(symbolTable** head,int IC){
    symbolTable* temp = *head;
    while(temp != NULL){
        if(temp->symbolType == 2 || temp->symbolType == 4){
            temp->address += IC;
        }
        temp = temp->next;
    }
}

int table_contain_extern(symbolTable* head){
    while (head != NULL)
    {
        if(head->symbolType == EXTERNAL_SYMBOL){
            return 1;
        }
       head = head->next;
    }
    return 0;
}


