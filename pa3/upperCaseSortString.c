/*
Filename : upperCaseSortString.c
Author : Zhi Jia Teoh
UserID : cs30xjk
Description : This routine sorts the string by alphabetical order
              and converts them to upper case
*/
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <strings.h>
#include "pa3.h"

/*
Function prototype: voidupperCaseSortString(char const *,int,char*);
Return value : void
Parameters : src = source string
             n   = string length
             dest= dest string
Description : Sorts alpbabetically and convert string to uppercase
*/
void upperCaseSortString(char const *src, int n, char *dest)
{
  //copy the string
  (void)strncpy(dest,src,n-1);
  dest[n-1]='\0';

  //convert to upperCase
  int i = 0;
  while(i<n)
  {
    if(dest[i]!='\0')
    {
      dest[i]=toupper(dest[i]);
      i++;
    }
    else break;
  }
  
  //sort
  qsort(dest,strlen(src),sizeof(char),charCompare);
}
