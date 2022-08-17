



int isDirective(char* word){
    int i = 0;
    const char *directives[] = {".data", ".string", ".struct", ".entry", ".extern"};

    for(i = 0;i<NUM_OF_DIRECTIVES;i++){
        if(strcmp(word,instructions[i]) == 0){
            return TRUE;
        }
    }
    return FALSE;
}