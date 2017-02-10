/*
Filename : checkCmd.c
Author : Zhi Jia Teoh
USER ID : cs30xjk
Date : Feb 8 2017
Description : This routine checks if the cmdString is present
              in the commands array.
Sources of help : Handout and Piazza

*/
#include <stdio.h>
#include <string.h>

/*
Function name : checkCmd()
Prototype:
int checkCmd(const char * const cmdString,
           const char * const commands[]);
Description : Checks of similar string from
              cmdString in commands[]
Return value : Index if present, -1 if absent
*/


int checkCmd(const char * const cmdString, const char * const commands[])
{
  if (cmdString != NULL && commands != NULL)
  { 
     int i;
     for (i =0; commands[i] != NULL ; i++)
     {
        if(strncmp(cmdString,commands[i],BUFSIZ)==0)
         {
         printf("%d\n",i);
         return i;}
     }
  }
  return -1;
}

