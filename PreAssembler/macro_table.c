#include "macro_table.h"

/**
 * @brief The function creates new macro table node
 * 
 * @param macroName The name of the new macro 
 * @param startIndex The index where the macro content start in the as file
 * @param endIndex The index where the macro content end in the as file
 * @return macro_table* The new macro
 */
macro_table* createMacro(char* macroName,int startIndex,int endIndex)
{
	macro_table* newNode = (macro_table*)malloc(sizeof(macro_table));
    newNode->name = (char*)malloc(strlen(macroName)+1);
    strcpy(newNode->name,macroName);
    newNode->startIndex = startIndex;
    newNode->endIndex = endIndex;
    newNode->next = NULL;
	return newNode;
}
/**
 * @brief The function free all of the dynamic allocations that was done for the macro table
 * 
 * @param head The pointer to the start of the macro table
 */
void free_macro_table(macro_table* head)
{
    macro_table* tmp;

    while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp->name);
       free(tmp);
    }
}

/**
 * @brief The function add a node to the end of the macro table
 * 
 * @param head double pointer to the start of the macro table
 * @param newNode the node we want to add to the end of the macro table
 */
void insertAtEnd(macro_table** head, macro_table* newNode)
{
	if (!*head)
	{
	    *head = newNode;
	}
	else
	{
	    macro_table* p = *head;
        while (p->next) 
        {
            p = p->next;
        }
        p->next = newNode;
	}
}
/**
 * @brief The function print the values of the nodes in the macro table
 * 
 * @param head The pointer to the start of the macro table
 */
void print_macro_table(macro_table* head){
    while (head != NULL)
    {
        printf("macro name: %s,start: %d,end: %d",head->name,head->startIndex,head->endIndex);
        head = head->next;
    }
}
/**
 * @brief The function check the size of the macro_table
 * 
 * @param head The pointer to the start of the macro table
 * @return int the length of the macro table
 */
int get_table_length(macro_table* head)
{
    int len = 0;
    if(head != NULL){
        len = 1 + get_table_length(head->next);
    }
    return len;
}
/**
 * @brief The function check if there a macro by a macro certain name in the macro table 
 * 
 * @param head The pointer to the start of the macro table
 * @param macroName The name of the macro we try to search in the macro table
 * @return int 
 */
int in_macro_table(macro_table* head,char* macroName){
    while(head){
        if(strcmp(head->name,macroName) == 0){
            return 1;
        }
        head = head->next;
    }
    return 0;
}

