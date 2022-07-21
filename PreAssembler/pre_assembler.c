#include "pre_assembler.h"

/**
 * @brief The function checks if the line contains a macro definition or a macro name
 * 
 * @param line The line we check
 * @param asFile the as assembly file we read from
 * @param head The pointer to the start of the macro table
 * @param amFile the am file we write to
 * @return int 1 if we found a macro 0 if we didn't
 */
int check_macro(char* line,FILE* asFile,macro_table** head,FILE* amFile){
    char* lineSeparated;
    int startIndex;   

    lineSeparated = strtok(line,SPACES_AND_NEWLINE);/*we get the first word in the line*/
    printf("\nthe start: %s\n",lineSeparated);
    
    if((*head) != NULL && lineSeparated != NULL && strcmp(lineSeparated,"macro") != 0){/*If the line is not a macro definition*/
        if(in_macro_table(*head,lineSeparated)){/*We check if it's a macro name*/
        
            replace_macro(*head,lineSeparated,amFile,asFile);/*If it is we copy the content of the macro to the am file*/
            return 1;
        }
        return 0;
    }else if(lineSeparated != NULL&&strcmp(lineSeparated,"macro") == 0){/*If the line is a macro definition*/
        
        lineSeparated = strtok(NULL,"\n");/*The name of the macro*/
        
        startIndex = ftell(asFile);/*The index where the content of the macro start*/

        add_to_macro_table(head,lineSeparated,asFile,startIndex);/*We add the macro to the macro table*/
        return 1;
    }
    
    return 0;

}
/**
 * @brief The function write the macro content to the am file(output file) instead of the macro name
 * 
 * @param head The pointer to the start of the macro table
 * @param macroName The name of the macro we replace
 * @param amFile the am file we write to
 * @param asFile the as assembly file we read from
 */
void replace_macro(macro_table* head,char* macroName,FILE* amFile,FILE* asFile){
    char c;
    int originalPlace = 0;
    int currPlace = 0;
    
    while(strcmp(head->name,macroName) != 0){/*we get to the node which contains the macro we want to replace*/
        head = head->next;
    }

    originalPlace = ftell(asFile);/*The index we are now in the as file*/
    fseek(asFile,head->startIndex, SEEK_SET);/*We change the index to the where the macro content begin*/
    currPlace = head->startIndex;
    c = fgetc(asFile);
    while(currPlace <= head->endIndex){/*We read the content of the macro and copy it to the am file*/
        fputc(c, amFile);
        c = fgetc(asFile);
        currPlace++;
    }
    fseek(asFile,originalPlace, SEEK_SET);/*we get back to the index we switched from*/
}
/**
 * @brief The function add a new macro to the macro table
 * 
 * @param head double pointer to the start of the macro table
 * @param macroName the name of the new macro
 * @param asFile the as assembly file we read from
 * @param startIndex The index where the content of the macro start
 */
void add_to_macro_table(macro_table** head,char* macroName,FILE* asFile,int startIndex){
    char* line;
    char* lineStart;
    macro_table* newMacro = NULL;
    int endIndex;

    line = get_line(asFile);
    lineStart = strtok(line,SPACES);/*we get the first word in the line*/

    while(strcmp(lineStart,"endmacro\n") != 0){/*we check if we got to the end of the macro definition*/
        free(line);
        endIndex = ftell(asFile)-1;/*We save every time the end index so we have the index where the macro content ends*/
        line = get_line(asFile);
        lineStart = strtok(line,SPACES);
    }
    free(line);
    newMacro = createMacro(macroName,startIndex,endIndex);/*we create a new macro node*/
    insertAtEnd(head,newMacro);/*And adding it to the end of the macro table*/
}

/**
 * @brief The function pre-assemble the as file to the am file
 * 
 * @param fileNmae the name of the file to pre-assemble
 */
void pre_assembler(char* fileNmae){
    FILE* asFile = NULL;
    FILE* amFile = NULL;
    macro_table* head = NULL;
    char* line;
    char* originalLine;

    asFile = open_file(fileNmae,".as","r");
    if(asFile == NULL){/*Check the file was opened*/
        printf("Couldn't open %s.as",fileNmae);
        return;
    }

    amFile = open_file(fileNmae,".am","w");

    while((line = get_line(asFile)) != NULL){
        originalLine = (char*)malloc(strlen(line)+1);/*We copy the line because the strtok will change the line later*/
        strcpy(originalLine,line);
        if(!check_macro(line,asFile,&head,amFile)){/*We check if we found a macro*/
            copy_line_to_file(originalLine,amFile);/*if not we copy the line to the am file*/
        }
        free(line);
        free(originalLine);
    }

    free(line);
    free_macro_table(head);
    fclose(asFile);
    fclose(amFile);
}