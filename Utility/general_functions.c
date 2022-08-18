#include "../Utility/general_functions.h"

int isRegister(char *name)
{
    return strlen(name) == REGISTER_NAME_LENGTH && name[0] == 'r' && name[1] >= '0' && name[1] <= '7';
}

int is_number(char number[])
{
    int i;
    if (number[0] == '-' || number[0] == '+' || isdigit(number[0])) /*whether the first character is a digit or a sign*/
    {
        for (i = 1; i < strlen(number) - 1; i++)
            if (!isdigit(number[i]))
                return FALSE;
    }
    else
        return FALSE;
    return TRUE;
}

void removeLeftWhiteSpaces(char line[LINE_LEN]){
    int i = 0, j = 0;
    for(i = 0;  (line[i] == ' ' || line[i] == '\t') && i < strlen(line) ; i++){
        j = i;
    }
    /* shift to the left */
    for(i = 0; j <= strlen(line); i++){
        line[i] = line[j];
        j++;
    }
    line[j] = '\0';
}

void removeRightWhiteSpaces(char line[LINE_LEN]){
    int i;
    for(i = strlen(line)-1 && (line[i] == ' ' || line[i] == '\t');i>0;i--){
        line[i] = '\0'
    }
}


int ignoreLine(char* line){
    removeLeftWhiteSpaces(line);
    return line[0] == ';' || line[0] == '\0' || line[0] == '\n';
}

void copyCurrentWord(char *word, char *line)
{
    int i = 0;
    if (word == NULL || line == NULL)
        return;

    while (i < LINE_LEN && !isspace(line[i]) && line[i] != '\0') /* Copy the courant first word in the line until a space */
    {
        word[i] = line[i];
        i++;
    }
    word[i] = '\0';
}

void toNextWord(char *line)
{
    int i = 0;
    if (line == NULL)
        return NULL;
    /* Skip rest of characters in the line (until a space) */
    while (!isspace(line[i]) && !end_of_line(line)){
        line++;
        i++;
    }
                      
    removeLeftWhiteSpaces(line); /* Skip the spaces or tubs from the left*/

    
}

int is_system_word(char* word){
    return isRegister(word) || isDirective(word) || isOperation(word);
}

void printError(char* error,int line,char* fileName){
    printf("%s in line: %d in file: %s",error,line,fileName);
}