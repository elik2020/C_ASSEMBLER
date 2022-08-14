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

void removeWhiteSpaces(char line[LINE_LEN]){
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