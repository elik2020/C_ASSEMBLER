#include "../Iterations/first_pass.h"


symbolTable first_pass(char* fileName,int* errorFound,int* entryFound){

    int IC = 100;
    int DC = 0;
    FILE* amFile = NULL;
    symbolTable* head = NULL;
    char line[LINE_LEN] = {0};
    char current_word[LINE_LEN] = {0};
    char labelName[LABEL_LEN] = {0};
    int checkError = 0;
    int lineCount =  0;
    amFile = open_file(fileName,".am","r");

    while(!feof(amFile)){

        fgets(line, LINE_LEN, amFile); 
        lineCount++;

        if(ignoreLine(line)){
            continue;
        }

        printf("line is: %s",line);
        copyCurrentWord(current_word,line);

        if(checkLabel(current_word)){
            strcpy(labelName,current_word);
            insertSymbolAtEnd(&head,current_word,IC);
            
            toNextWord(line);
            copyCurrentWord(current_word,line);
        }

        

        if(isDirective(current_word)){
            if(strcmp(current_word,".entry") == 0){
                *entryFound = 1;
            }

            directiveHandler(&head,&DC,lineCount,current_word,labelName);
        }else{
            if(isOperation(current_word)){
                IC++;
                operationHandler(&head,&IC,lineCount,current_word,labelName);
            }else{
                printf("bad in line %s",lineCount);
            }
            
        }



        memset(labelName,0,LABEL_LEN);
        memset(line,0,LINE_LEN);

    }

}