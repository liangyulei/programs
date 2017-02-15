/*
Filename : main.c
Author : Zhi Jia Teoh
UserID : cs30xjk
Description : This is program's main driver that will check the
              command and arguments usage correctly before running
              the program.
Date : 14 Feb 2017
Sources of Help : Piazza and TAs
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "pa2.h"
#include "pa2Strings.h"

/*
Function name : main()
Function prototyope : int main (int argc, char *argv[])
Description : Check that the number of args entered to run the program
              is correct, and check user prompt commands is correct
              with the right number of arguments before executing
              the correct functions as required. Program will
              return EXIT_SUCCESS if no errors, EXIT_FAILURE if
              there is error.
Parameters : int argc = argument count
             char *argv = array of argument string
Side effects : Output the lightBanks correctly
Error conditions : Output too many arguments error or file open failure
Return value : EXIT_SUCCESS if no errors, EXIT_FAILURE if errors
*/

int main(int argc,char *argv[])
{ 
  //variable declarations
  unsigned int lightBank[] = {0,0};
  const char * const commands [] = {COMMANDS,NULL};
  FILE * inFile = stdin;
  char buf[BUFSIZ] = {0};
  short prompt = TRUE;
  
  //turn off buffering in stdout
  (void)setvbuf(stdout,NULL,_IONBF,0);
  
  //check if too many arguments
  if(argc > MAX_ARGS+1)
  {
    char cwd[BUFSIZ];
    (void)getcwd(cwd,sizeof(cwd));
    (void)printf(STR_USAGE_MSG,cwd);
    return EXIT_FAILURE;
  }

  //argument number correct
  if(argv[1] != NULL)
  {
    FILE * file = fopen(argv[1],"r");
    if(file==NULL)
    {
      //file not found error
      perror(argv[1]);
      return EXIT_FAILURE;
    }

    inFile = file;
    prompt = FALSE;
  }
  else
  {
    prompt = checkPrompt(); 
  }
  
  //display initial lights
  displayLights(lightBank);

  //for loop to continually reprompt user
  for(DISPLAY_PROMPT; fgets(buf,BUFSIZ,inFile) != NULL; DISPLAY_PROMPT)
  {
    //points to first string token (cmd)
    char *token = strtok(buf,TOKEN_SEPARATORS);
    unsigned long int _arg1;
    unsigned long int _arg2;
    
    //if no command entered
    if(token == NULL)
    {
      continue;
    }
    
    //check if commands valid
    int index = checkCmd(token,commands);

    if(index==-1)
    {
      (void)printf(STR_BAD_CMD);
      continue;
    }
    
    //help command
    if(strcmp(token,"help")==0)
    {
      (void)fprintf(stderr,"%s",STR_HELP_MSG);
      continue;
    }
    
    //quit command
    if(strcmp(token,"quit")==0)
    {
      break;
    }
    
    //get command's first argument
    char *arg1 = strtok(NULL,TOKEN_SEPARATORS);
    
    //command argument missing
    if (arg1 == NULL)
    {
      (void)printf(STR_ARGS_REQ);
      continue;
    }
    
    //convert argument to int
    char *endptr = NULL;
    errno=0;
    _arg1 = strtoul(arg1,&endptr,0);
    
    //check if argument has any non-digits
    if(isalpha(*endptr))
    {
      (void)printf(STR_STRTOLONG_NOTINT,arg1);
      continue;
    }
    
    //if argument out of range
    if(errno == ERANGE)
    {
      char buffer[BUFSIZ];
      (void)snprintf(buffer,BUFSIZ,STR_STRTOLONG_CONVERTING,arg1,0);
      perror(buffer);
      continue;
    }
    
    //get command's second argument
    char *arg2 = strtok(NULL,TOKEN_SEPARATORS);
    
    //second argument required only for selected commands
    if(index == 0 || index == 1 || index == 2)
    {
      if(arg2 == NULL)
      {
        (void)printf(STR_ARGS_REQ);
        continue;
      }
      
      //convert argument to int
      char *endptr2 = NULL;
      errno = 0;
      _arg2 = strtoul(arg2,&endptr2,0);
      
      //check if argument has any non-digits
      if(endptr!=NULL)
      if(isalpha(*endptr))
      {
        (void)printf(STR_STRTOLONG_NOTINT,arg2);
        continue;
      }
      
      //if argument out of range
      if(errno == ERANGE)
      {
        char buffer2[BUFSIZ];
        (void)snprintf(buffer2,BUFSIZ,STR_STRTOLONG_CONVERTING,arg2,0);
        perror(buffer2);
        continue;
      }
      
      //too many arguments error
      char *arg3 = strtok(NULL,TOKEN_SEPARATORS);
      if (arg3 != NULL)
      {
        (void)printf(STR_EXTRA_ARG,arg3);
        continue;
      }
    }
    //commands that require only one argument
    else
    {
      //too many arguments error
      if (arg2 != NULL)
      { 
        (void)printf(STR_EXTRA_ARG,arg2);
        continue;
      } 
    }  
  
   //run user's prompt command
   if (index == 0)
   {
     set(lightBank,_arg1,_arg2);
     displayLights(lightBank);
   }
   else if (index == 1)
   {
     clear(lightBank,_arg1,_arg2);
     displayLights(lightBank);
   }
   else if (index == 2)
   {
     toggle(lightBank,_arg1,_arg2);
     displayLights(lightBank);
   }
   else if (index == 3)
   {
     shift(lightBank,_arg1);
     displayLights(lightBank);
   }
   else if (index == 4)
   {
     rotate(lightBank,_arg1);
     displayLights(lightBank);
   }
   else if (index == 5)
   {
     ripple(lightBank,_arg1);
   }
  }
  
  //return EXIT_SUCCESS if no errors
  return EXIT_SUCCESS;
}
