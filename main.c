#include <main.h>

int main(int argc, char** argv){
    int i;
    if(argc == 1){
        printf("No file was given");
        return 0;
    }else{
        for(i = 1;i<argc;i++){
            pre_assembler(argv[i]);
        }
    }
    return 0;
}