#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define MAX_LINE_SIZE 81

typedef struct symbolTable{
    char name[MAX_LINE_SIZE];
    int address;
    int symbolType;/*auction ,data directive,struct or external*/
    struct symbolTable* next;
} symbolTable;

/**
 * @brief creates a symbol for the symbol table
 * 
 * @param symbolName - the symbol name
 * @param IC - the address of the symbol
 * @return symbolTable* returns the symbol we created
 */
symbolTable* createSymbol(char* symbolName,int IC);
/**
 * @brief inserts a new symbol to the end of the symbol table
 * 
 * @param head - the double pointer to the head of the symbol table
 * @param symbolName - the symbol name
 * @param IC - the address of the symbol
 * @return symbolTable* returns the symbol we created
 */
symbolTable* insertSymbolAtEnd(symbolTable** head,char* symbolName,int IC);
/**
 * @brief checks if a symbol is in the symbol table
 * 
 * @param head - the double pointer to the head of the symbol table
 * @param symbolName - the symbol name 
 * @return int returns 1 if it is, otherwise returns 0
 */
int inSymbolTable(symbolTable* head,char* symbolName);
/**
 * @brief checks if a symbol is an extern symbol
 * 
 * @param head - the double pointer to the head of the symbol table
 * @param symbolName - the symbol name 
 * @return int returns 1 if it is, otherwise returns 0
 */
int is_extern(symbolTable* head,char* symbolName);
/**
 * @brief checks if a symbol is a struct symbol
 * 
 * @param head - the double pointer to the head of the symbol table
 * @param symbolName - the symbol name 
 * @return int returns 1 if it is, otherwise returns 0
 */
int is_struct(symbolTable* head,char* symbolName);
/**
 * @brief returns the address of the symbol
 * 
 * @param head - the double pointer to the head of the symbol table
 * @param symbolName - the symbol name 
 * @return int returns the address of the symbol
 */
int symbol_address(symbolTable* head,char* symbolName);
/**
 * @brief checks if the word that we've found is a label
 * 
 * @param word - the word that we check
 * @return int returns 1 if it is, otherwise returns 0
 */
int checkLabel(char* word);
/**
 * @brief checks if the label is legal or not
 * 
 * @param name - the label we check
 * @return int returns 1 if it is, otherwise returns 0
 */
int checkLabelName(char* name);
/**
 * @brief deletes the symbol from the symbol table
 * 
 * @param head - the double pointer to the head of the symbol table
 * @param name - the label we delete
 */
void deleteSymbol(symbolTable** head, char* name);
/**
 * @brief prints the symbol table
 * 
 * @param head - the pointer to the head of the symbol table
 */
void print_symbol_table(symbolTable* head);
/**
 * @brief frees the symbol table
 * 
 * @param head - the pointer to the head of the symbol table
 */
void free_symbol_table(symbolTable* head);
/**
 * @brief adds the final IC to the symbols that were declared as data
 * 
 * @param head - the double pointer to the head of the symbol table
 * @param IC - the final IC of the first iteration
 */
void AddICToData(symbolTable** head,int IC);
/**
 * @brief checks if the symbol table contains an extern symbol
 * 
 * @param head - the pointer to the head of the symbol table
 * @return int returns 1 if it is, otherwise returns 0
 */
int table_contain_extern(symbolTable* head);

#endif 