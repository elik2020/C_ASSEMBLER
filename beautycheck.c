#include "d.h"

const char * beautycheck(const char *filename) {
FILE *fp;
int lines=1;
char line[MAXL];
char *check;
int spaceCounted=0;
int commaCounted=0;

/*if the file doesn't open, exit*/
if ((fp = fopen (filename,"r")) == NULL )
{

fprintf( stderr, "An issue with opening the file! \n" );
 exit(1);
}
  


/*reading from the file line by line*/
  
while ( fgets(line, sizeof line, fp))
 {

/*if the line starts at ';' or is just an empty line ignore it, like a comment*/
if (strstr(line, ";")!=NULL || isspace(*line) !=0) {
lines++;
continue;
}

         
/*if the line includes :, that means that its a label, we need to check if there's a space after it*/
    
if (strstr(line, ":")!=NULL ) {
spaceCounted++;
check = strstr(line, ":");
check = check+1;
if (*check != ' ') {
  yieldError(missingSpace, lines);
  exit(1);
}  
} 

/*if the line includes mov/add/cmp/sub/lea/not/inc/clr/dec/jmp/bne/get/prn/jsr we check if there's a space afterwards*/
      if (strstr(line, "not")!=NULL ||strstr(line, "inc")!=NULL||strstr(line, "clr")!=NULL||strstr(line, "dec")!=NULL||strstr(line, "jmp")!=NULL||strstr(line, "bne")!=NULL||strstr(line, "get")!=NULL||strstr(line, "prn")!=NULL||strstr(line, "jsr")!=NULL) {
     if (strstr(line, "not")!=NULL){


    check = strstr(line, "not");
       }
          if (strstr(line, "inc")!=NULL){


    check = strstr(line, "inc");
       }
           if (strstr(line, "clr")!=NULL){


    check = strstr(line, "clr");
       }
        if (strstr(line, "dec")!=NULL){


    check = strstr(line, "dec");
       }
        if (strstr(line, "jmp")!=NULL){


    check = strstr(line, "jmp");
       }
        if (strstr(line, "bne")!=NULL){


    check = strstr(line, "bne");
       }
         if (strstr(line, "get")!=NULL){


    check = strstr(line, "get");
       }
        if (strstr(line, "prn")!=NULL){


    check = strstr(line, "prn");
       }
         if (strstr(line, "jsr")!=NULL){


    check = strstr(line, "jsr");
       }
    check=check+3;
  spaceCounted++;
if (*check!=' ') {
  
  yieldError(missingSpace,lines);
  exit(1);
}
        }
/*if the line includes mov/add/cmp/sub/lea check also for extra/ lack of commas*/
   if(strstr(line, "mov")!=NULL||strstr(line, "cmp")!=NULL||strstr(line, "add")!=NULL||strstr(line, "sub")!=NULL||strstr(line, "lea")!=NULL) {
  if (strstr(line, "mov")!=NULL){
    check = strstr(line, "mov");
    }
      if (strstr(line, "add")!=NULL){
    check = strstr(line, "add");
    }
      if (strstr(line, "cmp")!=NULL){
    check = strstr(line, "cmp");
    }
      if (strstr(line, "sub")!=NULL){
    check = strstr(line, "sub");
    }
      if (strstr(line, "lea")!=NULL){
    check = strstr(line, "lea");
    }
commaCounted++;
spaceCounted++;
    
    check=check+3;
  if (strstr(line, ",")==NULL) {
    yieldError(missingComma, lines);
    exit(1);
  }
if (*check!=' ') {
  
  yieldError(missingSpace,lines);
  exit(1);
}

}

 lines++; 

}
 lines--; 
  printf("%d",lines);
   /*checking for extra commas*/
 
  if(extraCommaCheck(filename, commaCounted)==0) {
  /*if successful, checking for extra spaces*/
  extraSpaceCheck(filename, spaceCounted);
    }
  
  /*closing the file reading process*/
fclose(fp);
return 0;
}

int extraCommaCheck(const char *filename,int counted) {
Boolio flag=False;
FILE* fp;
int lines=1;
char c;
int count = 0;    
fp = fopen(filename, "r");
    
    if (fp == NULL) 
    {
        printf("UNABLE TO OPEN THE FILE");
        exit(1);
    }

/*reading from the file*/
/*we will count the amount of commas and see if it matched commaCounted - which counter the amount of commas required by counting words which require a comma after them*/

    while (counted>=count && (c = fgetc(fp)) != EOF) 
    {
     
        if (c == '\n') {
         flag =False;
      lines++;
         }
      if (c == ';') {
          flag=True;
        }
      if (flag == True) {
       
        continue;
      }

        if (c == ',')
            ++count;
     
    }
    if(count>counted) {
     yieldError(extraComma, lines);
      
        exit(1);
     
    }

 
   
 fclose(fp);
  return 0;
}
int extraSpaceCheck(const char *filename,int counted) {
Boolio flag=False;
FILE* fp;
int lines=1;
char c;
int count = 0;    
fp = fopen(filename, "r");
 
    if (fp == NULL) 
    {
        printf("UNABLE TO OPEN THE FILE");
        exit(1);
    }

/*reading from the file*/
/*we will count the amount of spaces and see if it matched spaceCounted - which counter the amount of spaces required by counting words which require a space after them*/

    while (counted>=count && (c = fgetc(fp)) != EOF) 
    {
     
        if (c == '\n') {
         flag =False;
           lines++;
     
         }
      if (c == ';' ) {
      
          flag=True;
        }
      if (flag == True) {
       
        continue;
      }

        if (c == ' ')
            ++count;
     
    }

    
    if(count>counted) {
     yieldError(extraSpace, lines);
       exit(1);
      return 1;
    }
else if(count==counted) {
   printf("\n\nBeauty check passed successfully! :)");
 }
 
   
 fclose(fp);
  return 0;
}
