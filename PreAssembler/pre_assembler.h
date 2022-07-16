#ifndef PRE_ASSEMBLER_H
#define PRE_ASSEMBLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../PreAssembler/macro_table.h"
#include "../Utility/files.h"

int check_macro(char* line,FILE* asFile,macro_table** head,FILE* amFile);
void replace_macro(macro_table* head,char* macroName,FILE* amFile,FILE* asFile);
void add_to_macro_table(macro_table** head,char* macroName,FILE* asFile,int startIndex);
void pre_assembler(char* fileNmae);

#endif 