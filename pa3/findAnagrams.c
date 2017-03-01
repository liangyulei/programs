/*
Filename : findAnagrams.c
Author : Zhi Jia Teoh
Userid : cs30xjk
Description : Searches for anagrams on a given string
Date : 27 Feb 2017
Sources of Help : Piazza and TAs
*/

#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include "pa3.h"
#include "pa3Strings.h"
#define MIN_INDEX 0

/*
Function name : findAnagrams()
Prototyope : int findAnagrams(struct HashTable const *);
Parameters: arg1 = dictionary table
Side Effects : none
Error Conditions : initAnagram failure
Return value : 0 if success,-1 if failure
*/

int findAnagrams(struct HashTable const * table)
{ 
  //var for input file and user prompt string
  FILE *inFile = stdin;
  char buffer [BUFSIZ];

  //while user prompts
  for(fprintf(stdout,STR_USER_PROMPT);
    fgets(buffer,BUFSIZ,inFile) != NULL;
    fprintf(stdout,STR_USER_PROMPT) )
    {
        //null terminate the prompt string
        //remove newline char
        char * endPtr = strchr(buffer,'\n');
        if(endPtr != NULL)
          *endPtr = '\0';


        struct Anagram anagram;

        //if initAnagram failure
        if( initAnagram (buffer, &anagram) == -1)
          return -1;
        
        //get hashtableindex 
        int tableIndex = getTableIndex(anagram.sortedWord,
                         table -> size);
      
        //get table entry
        struct TableEntry *entry = &(table -> entryPtr[tableIndex]);

        //get table size
        int totalSize = entry->numAnagrams/sizeof(struct Anagram);

        //initially not found
        int foundWord = 0;

        //loop table
        for(int i =0 ; i < totalSize ; i++)
        {
          if(foundWord == 0)
          {
            struct Anagram * temp = &(entry->anagramPtr[i]);
            if(strncmp(anagram.sortedWord,temp->sortedWord,BUFSIZ)==0)
             { 
              int firstWord = 0;
              for(int j=0;j < temp -> numWords; j++)
              {
               //temp str to not print same string
                char * tempStr = temp -> words[j];
                int sameStr = strncasecmp(buffer,tempStr,BUFSIZ);
             
               //print STR_FOUND_ANAGRAMS 
               if(sameStr !=0 && firstWord==0)
               {
                  (void)fprintf(stdout,STR_FOUND_ANAGRAMS);
                  firstWord++;
               }
                //print anagrams
               if(sameStr != 0)
                {
                  (void)fprintf(stdout,"%s%s",STR_SPACE_CHAR,tempStr);
                  foundWord = 1;
                }  
              } 
             }
           }else break;
        }
  (void)printf("\n");
  if(foundWord!=1)
    (void)fprintf(stdout,STR_NO_ANAGRAMS);
  
    //free initially created anagram 
    free(anagram.words[MIN_INDEX]);
    free(anagram.words);
 
    }
    (void)printf("\n");
  return 0;
}
