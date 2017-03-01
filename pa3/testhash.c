/*
Author : Zhi Jia Teoh
User ID : cs30xjk
Description : unit test for hash() function
Date : 22 Feb 2017
Sources of Help : Piazza and TAs
*/

#include "test.h"
#include "pa3.h"

void testhash()
{
  char const * defaultStr = "\0";
  TEST(hash(defaultStr) == HASH_START_VAL);
  
  char const * str = "UCSD";
  int ret = HASH_START_VAL;
  ret = ret * HASH_PRIME + 'U';
  ret = ret * HASH_PRIME + 'C';
  ret = ret * HASH_PRIME + 'S';
  ret = ret * HASH_PRIME + 'D';
  TEST(hash(str) == ret);

  char const * str2 = "123";
  int ret2 = HASH_START_VAL;
  ret2 = ret2 * HASH_PRIME + '1';
  ret2 = ret2 * HASH_PRIME + '2';
  ret2 = ret2 * HASH_PRIME + '3';
  TEST(hash(str2) == ret2);



}
int main()
{
  testhash();
  return 0;
}

