#include "d.h"

const char * beautycheck(const char *filename) {
FILE *fp;
int lines=1;
char line[MAXL];
char *check;
  char *check2;
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

if ( strstr(line, ":")!=NULL) {
      check = strstr(line, ":");
           check=check+1;
  if (*check!=' ') {
 
  sendError(missingSpace,lines);
  exit(1);
}
      
       check = strstr(line, " ");
  /*that means that there's a space before the end of the label, which should not happen*/
  if (*(check-1)!=':') {
     sendError(extraSpace,lines);
  exit(1);
  }
  check=check+1;
 
  
      
  }

/*if the line includes mov/add/cmp/sub/lea/not/inc/clr/dec/jmp/bne/get/prn/jsr we check if there's a space afterwards*/
      if (strstr(line, "not")!=NULL ||strstr(line, "inc")!=NULL||strstr(line, "clr")!=NULL||strstr(line, "dec")!=NULL||strstr(line, "jmp")!=NULL||strstr(line, "bne")!=NULL||strstr(line, "get")!=NULL||strstr(line, "prn")!=NULL||strstr(line, "jsr")!=NULL) {
      

    if (strstr(line, "not")!=NULL) {
      check=strstr(line, "not");
    }
         if (strstr(line, "inc")!=NULL) {
      check=strstr(line, "inc");
    }
      if (strstr(line, "clr")!=NULL) {
      check=strstr(line, "clr");
    }
         if (strstr(line, "dec")!=NULL) {
      check=strstr(line, "dec");
    }
         if (strstr(line, "jmp")!=NULL) {
      check=strstr(line, "jmp");
    }
         if (strstr(line, "bne")!=NULL) {
      check=strstr(line, "bne");
    }
         if (strstr(line, "get")!=NULL) {
      check=strstr(line, "get");
    }
         if (strstr(line, "prn")!=NULL) {
      check=strstr(line, "prn");
    }
    check=check+3;
   
if (*check!=' ') {
 
  sendError(missingSpace,lines);
  exit(1);
  
}
    if (strstr(line, ":")!=NULL) {
check = strstr(line, ":");
          
          check=check+2;
      }
        
        /*we skip the first - expected space and check if there are any more, if there are more spaces, we send an error*/
       check = strstr(check, " ");
       check=check+1;
        
       if ( strstr(check, " ")!=NULL){
        
           sendError(extraSpace,lines);
  exit(1);
       }
   
   
       
       
          
        }
/*if the line includes mov/add/cmp/sub/lea check also for extra/ lack of commas*/
   if(strstr(line, "mov")!=NULL||strstr(line, "cmp")!=NULL||strstr(line, "add")!=NULL||strstr(line, "sub")!=NULL||strstr(line, "lea")!=NULL) {
    
 if(strstr(line, "mov")!=NULL) {
   check =  strstr(line, "mov");
 }
      if(strstr(line, "cmp")!=NULL) {
   check =  strstr(line, "cmp");
 }
      if(strstr(line, "add")!=NULL) {
   check =  strstr(line, "add");
 }
      if(strstr(line, "sub")!=NULL) {
   check =  strstr(line, "sub");
 }
      if(strstr(line, "lea")!=NULL) {
   check =  strstr(line, "lea");
 }
    
    
    check=check+3;
  if (strstr(line, ",")==NULL) {
    sendError(missingComma, lines);
    exit(1);
  }
  
   
if (*check!=' ') {
 
  sendError(missingSpace,lines);
  exit(1);
  }
    
 
        /*if there's a label, we skip it and the expected space afterwards*/
    if (strstr(line, ":")!=NULL) {
check = strstr(line, ":");
          
          check=check+2;
      }
        /*we skip the first - expected space and check if there are any more, if there are more spaces, we send an error*/
       check = strstr(check, " ");
       check=check+1;
        
       if ( strstr(check, " ")!=NULL){
        
           sendError(extraSpace,lines);
  exit(1);
       }
       /*we skip the first - expected comma and check if there are any more, if there are more spaces, we send an error*/
       check = strstr(line, ",");
       check=check+1;
        
       if ( strstr(check, ",")!=NULL){
        
           sendError(extraComma,lines);
  exit(1);
       }

}

 lines++; 

}
 lines--; 
 
printf("Beauty check passed successfully! :)");
  
  /*closing the file reading process*/
fclose(fp);
return 0;
}
