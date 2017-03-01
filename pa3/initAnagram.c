/*
Filename : initAnagram.c
Name : Zhi Jia Teoh
User ID : cs30xjk
Return value : (int) 0 success or -1 failure
Description : Initialzies anagram struct
              for the src string passed in.
Date : 27 Feb 2017
*/

#define MIN_INDEX 0
#include <strings.h>
#include <stdlib.h>
#include "pa3.h"
#include "pa3Strings.h"

/*
Function Name : initAnagram()
Prototyope : int initAnagram(const char*, struct Anagram *);
Description : Sort and capitalize src string, then initialize
              the sortedWord, array, and numWords
Parameter : arg1: src srring, arg2: ptr to anagram struct
Side Effects : none
Error conditions : Memory allocation failure
Return : 0 if success, -1 if failure
*/
         

int initAnagram(char const * src, struct Anagram * anagram)
{ 
  //length of src string excluding null terminator
  int length = strlen(src);

  //initialize sortedWord (will null terminate src string
  //                       if needed)
  upperCaseSortString(src,length+1,anagram->sortedWord);
  
  //initialize numWords
  anagram-> numWords = 1;

  //allocate memory words array
  anagram->words = (char **)calloc(sizeof(char *), anagram->numWords);

  //check if memory alloc failure
  if(anagram->words == NULL)
  {
    (void)fprintf(stderr,STR_ERR_MEM_EXCEEDED);
    return -1;
  }

  //allocate memory for initial index of words array
 anagram->words[MIN_INDEX] = 
 (char *)calloc(sizeof(char),length+1);

 //check if memory alloc failure
 if(anagram->words[MIN_INDEX] == NULL)
 {
  (void)fprintf(stderr,STR_ERR_MEM_EXCEEDED);
  free(anagram -> words);
  return -1;
 }

 //copy src string to allocated string memory in word array
 //strlen returns length of string excluding null terminator
 (void)strncpy(anagram -> words[MIN_INDEX],src, length);
 //null terminate string
 anagram-> words[MIN_INDEX][length] = '\0';

 return 0;
}
