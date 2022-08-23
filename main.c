#include "main.h"

int main(int argc, char** argv){
    int i;
    int errorFound = 0;
    int entryFound = 0;
    symbolTable* head = NULL;
    if(argc == 1){
        printf("No file was given\n");
        return 0;
    }else{
        for(i = 1;i<argc;i++){
            /*pre_assembler(argv[i]);*/
            errorFound = 0;
            entryFound = 0;
            head = first_pass(argv[i],&errorFound,&entryFound);
            print_symbol_table(head);
        }
    }
    return 0;
}
