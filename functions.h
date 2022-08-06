#include "d.h"
void yieldError(Error err, int line);
char * convertfiletochar(const char *filename);
const char * beautycheck(const char *filename);
int extraSpaceCheck(const char *filename, int counted);
int keywordscheck(char *chars);
int extraCommaCheck(const char *filename,int counted);
