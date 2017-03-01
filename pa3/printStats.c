/* Filename: printStats.c
 * Author : Zhi Jia Teoh
 * User id : cs30xjk
 * Description : Print statistics on tableEntry
 * Date :  27 Feb 2017
 * Source of Help : Piazza and TAs
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "pa3.h"
#include "pa3Strings.h"

/* 
 * Function name : printStats()
 * Prototype : void printStats( struct HashTable const *, int );
 * Description : Prints information at specific entry in table
 * Parameters : arg1 = table, arg2= index
 * Side Effects : none
 * Error Conditions : none 
 * Return Value : void
 */

void printStats( struct HashTable const * table, int index )
{
    (void)printf(STR_STATS_FOR_INDEX,index);

  struct TableEntry * tableEntry = &(table -> entryPtr[index]);
  int totalCollision = tableEntry -> numAnagrams / sizeof( struct Anagram);

  (void)printf(STR_COLLISIONS,totalCollision);
  
  int wordCount = 0;
  int maximum = 0;
  int minimum = 0;

  for (int i = 0; i < totalCollision; i++ )
  {
    struct Anagram * tempAnagram = &(tableEntry -> anagramPtr[i]);
    wordCount = wordCount + tempAnagram -> numWords;

    if (tableEntry -> anagramPtr[maximum].numWords < tempAnagram->numWords )
      maximum = i;
    if (tableEntry -> anagramPtr[minimum].numWords > tempAnagram->numWords )
      minimum = i;
  }
  (void)printf(STR_NUM_WORDS,wordCount);

  char * minWord = NULL;
  char * maxWord = NULL;
  int minTotal,maxTotal;

  minTotal = tableEntry->anagramPtr[minimum].numWords - 1;
  maxTotal = tableEntry->anagramPtr[maximum].numWords - 1;

  minWord = tableEntry->anagramPtr[minimum].words[0];
  maxWord = tableEntry->anagramPtr[maximum].words[0];

  (void)printf(STR_MIN_ANAGRAMS, minWord, minTotal);
  (void)printf(STR_MAX_ANAGRAMS, maxWord, maxTotal);
}
