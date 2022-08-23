#include "../Utility/general_functions.h"
#include "../Utility/operation_handler.h"
#include "../Utility/directives_handler.h"
#include "../Utility/symbol_table.h"

int isRegister(char *name)
{
    return strlen(name) == REGISTER_NAME_LENGTH && name[0] == 'r' && name[1] >= '0' && name[1] <= '7';
}

int isNumber(char* number)
{
    int i;
    char numCopy[LINE_LEN] = {0};

    strcpy(numCopy,number);
    removeLeftWhiteSpaces(numCopy);
    removeRightWhiteSpaces(numCopy);

    if (numCopy[0] == '-' || numCopy[0] == '+' || isdigit(numCopy[0])) /*whether the first character is a digit or a sign*/
    {
        for (i = 1; i < strlen(numCopy) - 1; i++)
            if (!isdigit(numCopy[i]))
                return FALSE;
    }
    else{
        return FALSE;
    }
        
    return TRUE;
}

void removeLeftWhiteSpaces(char line[LINE_LEN]){
    int i = 0, j = 0;
    for(i = 0;  (line[i] == ' ' || line[i] == '\t') && i < strlen(line) ; i++){
        j = i;
    }
    if(line[0] == ' ' || line[0] == '\t'){
        j++;
    }
    /* shift to the left */
    for(i = 0; j <= strlen(line); i++){
        line[i] = line[j];
        j++;
    }
    line[j] = '\0';
}

void removeRightWhiteSpaces(char line[LINE_LEN]){
    int i = 0;
    for(i = (strlen(line)-1);(line[i] == ' ' || line[i] == '\t' || line[i] == '\n') && i>0;i--){
        line[i] = '\0';
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
        return;
    /* Skip rest of characters in the line (until a space) */
    while (!isspace(line[i]) && !endOfLine(line)){
        line++;
        i++;
    }
                      
    removeLeftWhiteSpaces(line); /* Skip the spaces or tubs from the left*/

    
}

int is_system_word(char* word){
    return isRegister(word) || isDirective(word) || isOperation(word);
}

void printError(char* error,int line,char* fileName){
    printf("%s in line: %d in file: %s\n",error,line,fileName);
}

int endOfLine(char *line)
{
    return line == NULL || line[0] == '\0' || line[0] == '\n';
}

int addressingMethodType(char* operand,int lineNum){
    int i;
    char number[LINE_LEN] = {0};
    char* afterDot;
    char* beforeDot;

    
    if (operand[0] == '#')
    {
        for(i = 1;i<strlen(operand) && operand[i] != '\n';i++){
            number[i-1] = operand[i];
        }
        if (isNumber(number)){
            return IMMEDIATE_ADDRESS;
        }
            
    }

    if (checkLabelName(operand))
    {
        return DIRECT_ADDRESS;
    }

    if (isRegister(operand))
    {
        return REGISTER_ADDRESS;
    }

    beforeDot = strtok(operand, ".");
    afterDot = strtok(NULL, ".");
    if (checkLabelName(beforeDot))
    {                                                       
        if (strlen(afterDot) == 1 && (afterDot[0] == '1' || afterDot[0] == '2')){
            return STRUCT_ADDRESS;
        }
            
    }
    printf("invalid addressing method in line: %d\n",lineNum);
    return addressingError;
}

int isEmpty(char* word){
    int i;
    if(word == NULL){
        return 1;
    }
    for(i = 0;i<strlen(word);i++){
        if(word[i] != ' ' && word[i] != '\n' && word[i] != '\t'){
            return 0;
        }
    }
    return 1;
}