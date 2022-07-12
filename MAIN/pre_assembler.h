#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <macro_table.h>
#include <files.h>

int check_macro(char* line,FILE* asFile,macro_table* head,FILE* amFile);
int in_macro_table(macro_table* head,char* macroName);
void replace_macro(macro_table* head,char* macroName,FILE* amFile,FILE* asFile);
void add_to_macro_table(macro_table* head,char* macroName,FILE* asFile,int startIndex);
void pre_assembler(char* fileNmae);