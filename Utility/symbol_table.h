
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define MAX_LINE_SIZE 81

typedef struct symbolTable{
    char name[MAX_LINE_SIZE];
    int address;
    int symbolType;/*auction ,data directive,struct or external*/
    struct symbolTable* next;
} symbolTable;

/*typedef struct entryTable{
    char name[LABEL_LEN];
    int lineNum;
    struct entryTable* next;
} entryTable;*/

symbolTable* createSymbol(char* symbolName,int IC);
symbolTable* insertSymbolAtEnd(symbolTable** head,char* symbolName,int IC);
int inSymbolTable(symbolTable* head,char* symbolName);
int checkLabel(char* word);
int checkLabelName(char* name);
void deleteSymbol(symbolTable** head, char* name);
void print_symbol_table(symbolTable* head);
void free_symbol_table(symbolTable* head);
void AddICToData(symbolTable** head,int IC);

#endif 