#include "main.h"

int main(int argc, char** argv){
    int i;
    int errorFound = 0;
    int entryFound = 0;
    int endIC = 0;
    int endDC = 0;
    symbolTable* head = NULL;
    if(argc == 1){
        printf("No file was given\n");
        return 0;
    }else{
        for(i = 1;i<argc;i++){
            /*pre_assembler(argv[i]);*/
            endIC = 100;
            endDC = 0;
            errorFound = 0;
            entryFound = 0;
            printf("\n\nstarted assembler on file %s\n\n",argv[i]);

            head = first_pass(argv[i],&errorFound,&entryFound,&endIC,&endDC);
            print_symbol_table(head);
            if(errorFound == 1){
                continue;
            }
            second_pass(argv[i],entryFound,endIC,endDC,head);
        }
    }
    return 0;
}
