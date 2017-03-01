/* Filname : main.c
 * Author : Zhi Jia Teoh
 * Userid : cs30xjk
 * Description : main to parse user argument and perform the required task
 * Date : 27 Feb 2017
 * Source of Help : Piazza and TAs
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "pa3.h"
#include "pa3Strings.h"
#define MIN_INDEX 0

/*
 * Function name : main()
 * Prototype: int main( int agrc, char * argv[] );
 * Descirption : Parse user args and run respective commands
 * Parameters : argc = argument number, argv = argument values
 * Side Effects : none
 * Error Conditions : Hashtable error, flag error, memory error or
                      function call error
 * Return Value : EXIT_SUCCESS is success, EXIT_FAILURE if fails
 */

int main( int argc, char * argv[] )
{
  //flag variables
  int flag_f=0;
  int flag_s=0;
  int flag_i=0;
  int flag_h=0;
  //user input flag
  int inputFlag = 0;
  //argCount (offset for default arg name)
  int argCount = 0;
  
  //arg pointers and table size/index
  char * dictNameArg = NULL;
  char * tableSizeArg = NULL;
  char * tableIndexArg = NULL;
  int tableSize = 0; 
  int tableIndex = 0;

//parse user args
  while((inputFlag = getopt( argc, argv, ARG_STR )) != -1)
  {
    switch(inputFlag)
    {
      case CHAR_FILE_FLAG :
        dictNameArg = optarg;
        flag_f = 1;
        argCount = argCount + 2;
        break;
      
      case CHAR_SIZE_FLAG :
        tableSizeArg = optarg;
        flag_s = 1;
        argCount = argCount + 2;
        break;

      case CHAR_INFO_FLAG : 
        tableIndexArg = optarg;
        flag_i = 1;
        argCount = argCount + 2;
        break;

      case CHAR_HELP_FLAG :
        flag_h = 1;
        argCount++;
        break;

      default : 
        usage(stderr,USAGE_SHORT,argv[0]);
        return EXIT_FAILURE;
    }
  }

  //too many arguments
  if (argCount+1 < argc)
  {
    (void)fprintf( stderr, STR_ERR_EXTRA_ARGS, argv[argCount+1]);
    usage(stderr, USAGE_SHORT, argv[MIN_INDEX]);
    return EXIT_FAILURE;
  }

 //if -h entered 
   if (flag_h == 1 )
   { 
     usage( stdout, USAGE_LONG, argv[MIN_INDEX] );
     return EXIT_SUCCESS;
   }

//-f flag not entered
  if (flag_f == 0 )
    dictNameArg = DEFAULT_DICT_FILENAME;

//-s flag entered
  if (flag_s != 0 )
  {
    char * end = NULL;
    tableSize = strtoul( tableSizeArg, &end, 0 );

    //check for valid input size
    int checkInBound = isInBounds(MIN_SIZE,MAX_SIZE-1,tableSize);
    if (checkInBound == 0)
    {
      (void)fprintf(stderr,STR_ERR_RANGE,STR_ERR_SIZE,
      MIN_SIZE, MAX_SIZE );
      usage(stderr,USAGE_SHORT,argv[MIN_INDEX]);
      return EXIT_FAILURE;
    }


    if (*end != '\0')
    { 
       (void)fprintf(stderr,STR_ERR_NOTINT,tableSizeArg);
       usage(stderr, USAGE_SHORT, argv[MIN_INDEX] );
       return EXIT_FAILURE;
    }

    if (errno != 0)
    {
      char  buffer[BUFSIZ];
      (void)snprintf(buffer, BUFSIZ, STR_ERR_CONVERTING
      ,tableSizeArg, 10);
      perror(buffer);
      usage(stderr,USAGE_SHORT,argv[MIN_INDEX]);
      return EXIT_FAILURE;
    }
  }
  else 
  {
    tableSize = DEFAULT_SIZE;
  }

 //if -i entered
   if (flag_i != 0 )
   {
     char * end;
     tableIndex = strtol(tableIndexArg,&end,0);
     if (errno != 0)
     {
       char buffer[BUFSIZ];
       (void)snprintf(buffer,BUFSIZ,STR_ERR_CONVERTING,tableIndex,10);
       perror(buffer);
       usage(stderr,USAGE_SHORT,argv[MIN_INDEX]);
       return EXIT_FAILURE;
     }
     if (*end != '\0' )
     {
       (void)fprintf(stderr,STR_ERR_NOTINT,tableIndexArg);
       usage(stderr,USAGE_SHORT,argv[MIN_INDEX]);
       return EXIT_FAILURE;
     }
     //check if index valid
         int checkInBounds = isInBounds(0,tableSize-1,tableIndex);
         if (checkInBounds == 0 )
         {
           (void)fprintf( stderr, STR_ERR_RANGE, STR_ERR_INDEX,
           0,tableSize -1 );
           usage( stderr, USAGE_SHORT, argv[MIN_INDEX] );
           return EXIT_FAILURE;
         }
   }
   
//build HashTable
  struct HashTable table;
  table.size = tableSize;
  table.entryPtr = ( struct TableEntry * )
  calloc(tableSize, sizeof(struct TableEntry) ); 

  if ( loadDict(dictNameArg, &table) != 0)
  {
    usage( stderr, USAGE_SHORT, argv[MIN_INDEX] );
    return EXIT_FAILURE;
  }
//call printStats
  if (flag_i == 1)
  {
    printStats( &table, tableIndex );
    return EXIT_SUCCESS;
  }
//interactive mode
  if ( findAnagrams( &table ) != 0)
  {
    usage( stderr, USAGE_SHORT, argv[MIN_INDEX] );
    return EXIT_FAILURE;
  }

//free memory
for (int i = 0; i < table.size; i++ )
  {
    struct TableEntry * tableEntry = &(table.entryPtr[i]);
    if (tableEntry != NULL)
    {
      int length = tableEntry->numAnagrams/sizeof(struct Anagram);
      for (int j=0;j<length;j++)
      {
        struct Anagram * tempAnagram = &(tableEntry -> anagramPtr[j] );
        if (tempAnagram != 0 )
        {
          int numWordsSize = tempAnagram->numWords;
          for (int k = 0; k < numWordsSize; k++ )
              free(tempAnagram-> words[k]);
          //free memory
          free(tempAnagram-> words);
        }
      }
      //free memory
      free(tableEntry-> anagramPtr);
    }
  }
  //free memory
  free(table.entryPtr);

  //return succeed value
  return EXIT_SUCCESS;
}
