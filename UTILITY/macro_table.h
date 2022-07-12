
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_SIZE 80

typedef struct macro_table {
    char* name;
    int startIndex;
    int endIndex;
    struct macro_table* next;
} macro_table;


macro_table* createMacro(char* macroName,int startIndex,int endIndex);
void free_macro_table(macro_table* head);
void insertAtEnd(macro_table** head, macro_table* newNode);
int get_table_length(macro_table* head);