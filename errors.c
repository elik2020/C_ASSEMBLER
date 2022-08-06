#include "d.h"

  
void yieldError(Error err, int line) {
  int num;
   FILE *fptr;

 
   fptr = fopen("C:\\ErrorsFile.txt","w");
 
   if(fptr == NULL)
    {
       
         printf("Unable to create file.\n");
        exit(1);
    }
  fprintf( fptr,"ERROR FILE");
  switch (err)
    {
    case missingComma:
       printf("\nMissing a comma in line number %d !",line);
        fprintf( fptr,"\nMissing a comma in line number %d !",line);
      
        break;
    case extraComma:
      printf("\nExtra comma in line number %d !",line);
         fprintf( fptr, "\nExtra comma in line number %d !",line);
        break;
    
case missingSpace:
  printf( "\nThere's a miss of a space when there should be in line number %d !",line);
         fprintf( fptr,"\nThere's a miss of a space when there should be in line number %d !",line);
        break;
     
case wrongCommaPlace:
  printf("\nThere's a comma in a place in which there should not be in line number %d !",line);
         fprintf( fptr,"\nThere's a comma in a place in which there should not be in line number %d !",line);
        break;
   case    extraChars:
      printf( "\nThere's extra characters when there should not be in line number %d !",line);
       fprintf( fptr,"\nThere's extra characters when there should not be in line number %d !",line);
        break;
case extraSpace:
  printf( "\nThere's an extra space in a place in which there should not be in line number %d !",line);
         fprintf( fptr, "\nThere's an extra space in a place in which there should not be in line number %d !",line);
        break;

    
    default:
        break;
    }
}

