/*
Author : Zhi Jia Teoh
User ID : cs30xjk
Description : unit test for getTableIndex functon
Return : void
Date : 22 Feb 2017
Sources of Help : Piazza and TAs
*/

#include "pa3.h"
#include "test.h"

void testgti()
{
  char const * str = "\0";
  TEST(getTableIndex(str,5)==1);

  char const * str1 = "test";
  char const * str2 = "test";
  TEST(getTableIndex (str1,10) == getTableIndex (str2,10));
  
  char const * str3 = "abc";
  TEST(getTableIndex(str3,-51) == 50);
}


int main()
{
  testgti();
  return 0;
}
