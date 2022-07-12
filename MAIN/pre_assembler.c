#include <pre_assembler.h>

int check_macro(char* line,FILE* asFile,macro_table* head,FILE* amFile){
    char* lineSeparated;
    int startIndex;

    lineSeparated = strtok(line," ");
    if(lineSeparated != 0 && strcmp(lineSeparated,"macro") != 0){
        if(in_macro_table(head,lineSeparated)){
            replace_macro(head,lineSeparated,amFile,asFile);
            return 1;
        }
        return 0;
    }else if(strcmp(lineSeparated,"macro") == 0){
        lineSeparated = strtok(NULL,"\n");
        startIndex = ftell(asFile);
        add_to_macro_table(head,lineSeparated,asFile,startIndex);
        return 1;
    }

    return 0;

}


int in_macro_table(macro_table* head,char* macroName){
    while(head){
        if(strcmp(head->name,macroName) == 0){
            return 1;
        }
        head = head->next;
    }
    return 0;
}

void replace_macro(macro_table* head,char* macroName,FILE* amFile,FILE* asFile){
    char* c;
    int currPlace;
    
    while(strcmp(head->name,macroName)){
        head = head->next;
    }
    
    fseek(asFile,head->startIndex, SEEK_END);
    currPlace = head->startIndex;
    c = fgetc(asFile);
    while(currPlace != head->endIndex){
        fputc(c, amFile);
        c = fgetc(asFile);
        currPlace++;
    }
}

void add_to_macro_table(macro_table* head,char* macroName,FILE* asFile,int startIndex){
    char* line;
    int endIndex;

    line = get_line(asFile);
    while(strcmp(line,"endmacro\n")){
        free(line);
        line = get_line(asFile);
    }
    endIndex = ftell(asFile);
    insertAtEnd(&head,createMacro(macroName,startIndex,endIndex));
}

void pre_assembler(char* fileNmae){
    FILE* asFile = NULL;
    FILE* amFile = NULL;
    macro_table* head = NULL;
    char* line;

    asFile = open_file(fileNmae,".as");
    if(asFile == NULL){
        printf("Couldn't open %s.as",fileNmae);
        return;
    }

    amFile = open_file(fileNmae,".am");

    while((line = get_line(asFile)) != NULL){
        if(!check_macro(line,asFile,head,amFile)){
            copy_line_to_file(line,amFile);
        }
    }
    free_macro_table(head);
    fclose(asFile);
    fclose(amFile);
}