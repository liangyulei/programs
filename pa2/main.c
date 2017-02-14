#include <stdlib.h>
#include <stdio.h>
#include "pa2.h"
#include <string.h>
#include <errno.h>
#include <ctype.h>

#define STR_USAGE_MSG "Please use the following format ./pa2 <filename>\n"
#define STR_BAD_CMD   "Wrong command. Type help for list of commands\n"
#define STR_HELP_MSG  "helps commands\n"
#define STR_ARGS_REQ  "Command requires argument. Type help to see\n"
#define STR_STRTOLONG_NOTINT "Argument contains non-digit error\n"
#define STR_STRTOLONG_CONVERTING "Converting %s base 0:"
#define STR_EXTRA_ARG "Extra argument entered %s\n Type help for more info\n"


int main(int argc,char *argv[])
{
  unsigned int lightBank[] = {0,0};
  const char * const commands [] = {COMMANDS,NULL};
  FILE * inFile = stdin;
  char buf[BUFSIZ] = {0};
  short prompt = TRUE;

  (void)setvbuf(stdout,NULL,_IONBF,0);
  
  if(argc > MAX_ARGS+1)
  {
    (void)printf(STR_USAGE_MSG);
    return EXIT_FAILURE;
  }

  if(argv[1] != NULL)
  {
    FILE * file = fopen(argv[0],"r");
    if(file==NULL)
    {
      perror(argv[0]);
      return EXIT_FAILURE;
    }

    inFile = file;
    prompt = FALSE;
  }
  else
  {
    prompt = checkPrompt(); 
  }

  displayLights(lightBank);

  for(DISPLAY_PROMPT; fgets(buf,BUFSIZ,inFile) != NULL; DISPLAY_PROMPT)
  {
    //points to first string token (cmd)
    char *token = strtok(buf,TOKEN_SEPARATORS);
    unsigned long int _arg1;
    unsigned long int _arg2;

    if(token == NULL)
    {
      continue;
    }

    int index = checkCmd(token,commands);

    if(index==-1)
    {
      printf(STR_BAD_CMD);
      continue;
    }
    
    if(strcmp(token,"help")==0)
    {
      fprintf(stderr,"%s",STR_HELP_MSG);
      continue;
    }

    if(strcmp(token,"quit")==0)
    {
      break;
    }

    char *arg1 = strtok(NULL,TOKEN_SEPARATORS);

    if (arg1 == NULL)
    {
      printf(STR_ARGS_REQ);
    }
  
    char *endptr = NULL;
    errno=0;
    _arg1 = strtoul(arg1,&endptr,0);
    
    if(isdigit(*endptr) != 0)
    {
      printf(STR_STRTOLONG_NOTINT);
      continue;
    }
    
    if(errno == ERANGE)
    {
      char buffer[BUFSIZ];
      (void)snprintf(buffer,BUFSIZ,STR_STRTOLONG_CONVERTING,arg1);
      perror(buffer);
      continue;
    }
    
    char *arg2 = strtok(NULL,TOKEN_SEPARATORS);

    if(index == 0 || index == 1 || index == 2)
    {
      if(arg2 == NULL)
      {
        printf(STR_ARGS_REQ);
      }

      char *endptr2 = NULL;
      errno = 0;
      _arg2 = strtoul(arg2,&endptr2,0);

      if(isdigit(*endptr2) != 0)
      {
        printf(STR_STRTOLONG_NOTINT);
        continue;
      }
      
      if(errno == ERANGE)
      {
        char buffer2[BUFSIZ];
        (void)snprintf(buffer2,BUFSIZ,STR_STRTOLONG_CONVERTING,arg2);
        perror(buffer2);
        continue;
      }

      char *arg3 = strtok(NULL,TOKEN_SEPARATORS);
      if (arg3 != NULL)
      {
        printf(STR_EXTRA_ARG,arg3);
        continue;
      }
    }
    else
    {
      if (arg2 != NULL)
      {
        printf(STR_EXTRA_ARG,arg2);
        continue;
      } 
    }  

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

  return 0;
}
