/*
Filename : testupperCaseSortString.c
Description : Unit test for upperCaseSortString.c
Date : 22 Feb 2017
Sources of help : Piazza and TAs
*/

#include "pa3.h"
#include "test.h"
#include <string.h>

/*
Function name : testfunction()
Description : function to test upperCaseSortString
Return value : void
Error conditions : none
*/

void testfunction()
{
  char ret[BUFSIZ];
  char * src="defabcghiJKLPONM";
  upperCaseSortString(src,BUFSIZ,ret);
  TEST(strncmp(ret,"ABCDEFGHIJKLMNOP",11) == 0);

  char ret1[BUFSIZ];
  char * src1 = "321acbfde";
  upperCaseSortString(src1,BUFSIZ,ret1);
  TEST(strncmp(ret1,"123ABCDEF",3) == 0);

  char ret2[BUFSIZ];
  char * src2 = "9827304561";
  upperCaseSortString(src2,BUFSIZ,ret2);
  TEST(strncmp(ret2,"0123456789",10) == 0);

}

int main()
{
  testfunction();
  return 0;
} 
