/*
Filename : loadDict.c
Author : Zhi Jia Teoh
User ID : cs30xjk
Description : Loads the dictionary into hash table
Date : Feb 27 2017
Sources of Help : Piazza and TAs
*/

#define FILE_DOES_NOT_EXIST 2
#define FILE_PERMISSION_DENIED 14
#define MIN_INDEX 0
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "pa3.h"
#include "pa3Strings.h"

/*
Function name : loadDict()
Prototyope : int loadDict(char*, struct HashTable*);
Description : Read line by line of dict file and store
              all words as anagrams
Parameters : arg1 = file, arg2= hashtable
Side Effects : none
Error Conditions : fopen() fails by permission denied
                   or file does not exist
                 : initAnagram() failure (returns -1)
Return Value : 0 if success, -1 if failure                 
*/

int loadDict(char *filename, struct HashTable * table)
{
  //char array that reads from dict
  char buffer[BUFSIZ];

  //Open file
  FILE * inFile = fopen(filename,"r");

  //Error check for file
  if(inFile == 0)
  {
    perror(NULL);
    if(errno == FILE_DOES_NOT_EXIST)
      (void)fprintf(stderr,STR_ERR_FILE_INVALID);
    
    if(errno == FILE_PERMISSION_DENIED)
      (void)fprintf(stderr,STR_ERR_FILE_PERMISSION);
  
    //failure
    return -1;
  }
  //read dict line by line
  while(fgets(buffer,BUFSIZ,inFile))
  {
    //get word length (exclude null terminator)
    int length = strlen(buffer);
    
    //include null terminator as length
    length++;

    //null terminate each word
    char * nullTerminate = strchr(buffer,'\n');
    if(nullTerminate != NULL)
      *nullTerminate = '\0';

    //declare a temp Anagram for each word read
    struct Anagram wordAnagram;

    //initialize wordAnagram
    int checkFailure = initAnagram(buffer,&wordAnagram);

    //fail to initialize anagram
    if(checkFailure == -1)
      return -1;
    
    //get table index using sortedWord of wordAnagram
    int tableIndex = getTableIndex(wordAnagram.sortedWord, table->size);

    //get TableEntry using tableIndex
    struct TableEntry *tableEntry = &(table->entryPtr[tableIndex]);

    //if array anagrams in tableEntry is uninitialized
    if(tableEntry -> anagramPtr == NULL)
    {
      //allocate new memory
      tableEntry->anagramPtr =
      (struct Anagram *)malloc(sizeof(struct Anagram));

      //if allocation fail
      if(tableEntry->anagramPtr == NULL)
      { 
        //print error
        (void)fprintf(stderr,STR_ERR_MEM_EXCEEDED);
        
        //deallocate wordAnagram memory
        free(wordAnagram.words[MIN_INDEX]);
        free(wordAnagram.words);
        return -1;
      }

      //if allocation succeed, update numAnagrams
      tableEntry->numAnagrams = sizeof(struct Anagram);

      //set anagramPtr to wordAnagram
      *(tableEntry->anagramPtr) = wordAnagram;
    }
    //if array anagrams in tableEntry is initialized
    else
    {
      int matchExist = 0;
      //search array for matching word
      for(int i =0;i*sizeof(struct Anagram) < tableEntry->numAnagrams;i++)
      {
        //get anagram in anagramPtr by index
        struct Anagram *tempAnagram = &(tableEntry->anagramPtr[i]);

        //compare tempAnagram sortedWord with wordAnagram sortedWord
        if(strncmp(tempAnagram->sortedWord,
        wordAnagram.sortedWord,length-1)==0)
        { 
          //reallocate memory for new word
          tempAnagram->words = (char **)realloc(tempAnagram->words,
          sizeof(char *)*(tempAnagram->numWords+1));

          //if reallocation fail
          if(tempAnagram->words == NULL)
          {
            (void)fprintf(stderr,STR_ERR_MEM_EXCEEDED);
            free(wordAnagram.words[MIN_INDEX]);
            free(wordAnagram.words);
            return -1;
          }

          //if reallocation succeds
          tempAnagram->words[tempAnagram->numWords]=
          wordAnagram.words[MIN_INDEX];
          tempAnagram->numWords = tempAnagram->numWords +1;

          //matchExist
          matchExist=1;
        }
     }
        
        //if no matching sortedWord in anagram
        if(matchExist==0)
        {
          //append new anagram at end of anagramPtr
          struct Anagram *tempAnagram = (struct Anagram *)realloc
          (tableEntry->anagramPtr,tableEntry->numAnagrams+sizeof
          (struct Anagram));
  
          //if memory realloc failure
          if(tempAnagram == NULL)
          {
            (void)fprintf(stderr,STR_ERR_MEM_EXCEEDED);
            free(wordAnagram.words[MIN_INDEX]);
            free(wordAnagram.words);
            return -1;
          }
          
          //set anagramPtr to newly reallocated tempAnagram
          tableEntry->anagramPtr = tempAnagram;
          
          //set last index of anagramPtr to wordAnagram
          struct Anagram * last = &(tableEntry -> 
          anagramPtr[tableEntry->numAnagrams/sizeof(struct Anagram)]);
          tableEntry -> numAnagrams = tableEntry->numAnagrams + 
                                      sizeof(struct Anagram);
          *(last) = wordAnagram;      
        }
      }
  }
  return 0;

}
