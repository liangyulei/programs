/*
Filename : clear.c
Author : Zhi Jia Teoh
User id : cs30xjk
Date : 14 Feb 2017
Description : This function clears the bit on lightBanks based 
              on the pattern
Sources of help : TA's and piazza
*/

#include <stdlib.h>
#include <stdio.h>

/*
Function name : clear()
Function prototyope : void clear(unsigned int lightBank[],
                      const unsigned int pattern0, const
                      unsigned int pattern1);
Description: Clear each lightBank bits following the patterns
Parameters: lightBank => Two lightBank elements to be cleared
            pattern0 => Pattern for lightBank[0]
            pattern1 => Pattern for lightBank[1]
Side effect: lightBanks bit cleared according to pattern
Error conditions: none
Return value: void
*/

void clear(unsigned int lightBank[],const unsigned int pattern0,
            const unsigned int pattern1)
{

  lightBank[0] = lightBank[0] & (~pattern0);
  lightBank[1] = lightBank[1] & (~pattern1);
}
