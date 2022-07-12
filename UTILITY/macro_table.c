#include <macro_table.h>

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

int get_table_length(macro_table* head)
{
    int len = 0;
    if(head != NULL){
        len = 1 + get_list_length(head->next);
    }
    return len;
}

