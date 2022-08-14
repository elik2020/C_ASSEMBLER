
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "../Utility/all_definitions.h"

typedef struct symbolTable{
    char name[LABEL_LEN];
    int address;
    int symbolType;/*auction ,data directive or external*/
    struct symbolTable* next;
} symbolTable;


#endif 