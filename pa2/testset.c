/*
Filename : testset.c
Author : Zhi Jia Teoh
User id : cs30xjk
Description : Unit test for set routine
Date : 14 Feb 2017
Sources of help : Piazza and TAs
*/

#include <stdio.h>
#include <stdlib.h>
#include "pa2.h"
#include "test.h"

/*
Function name : testset()
Function prototyope : void testset()
Description: This function tests various inputs on test routine
Parameters : none
Return value : void
*/

void testset()
{
  unsigned int lightBank[] = {0x00000000,0x0000FFFF};
  unsigned int pattern0 = 0x0000F0F0;
  unsigned int pattern1 = 0x00000000;
  
  //test 1 - lightBank[0] empty
  set(lightBank,pattern0,pattern1);
  TEST(lightBank[0] == 0x0000F0F0 && lightBank[1] == 0x0000FFFF);
  
  //test 2 - lightBank[1] empty
  lightBank[0] = 0xFFFFFFFF;
  lightBank[1] = 0;
  pattern0 = 0;
  pattern1 = 0xFFFF0000;
  set(lightBank,pattern0,pattern1);
  TEST(lightBank[0] == 0xFFFFFFFF && lightBank[1] == 0xFFFF0000);

  //test 3 - set zero on non-empty bank
  lightBank[0] = 0x0000000F;
  lightBank[1] = 0x0000000F;
  pattern0 = 0;
  pattern1 = 0;
  set(lightBank,pattern0,pattern1);
  TEST(lightBank[0] == 0x0000000F && lightBank[1] == 0x0000000F);

  //test 4 - set all
  lightBank[0] = 0xF123F123;
  lightBank[1] = 0xF000F000;
  pattern0 = 0xFFFFFFFF;
  pattern1 = 0xFFFFFFFF;
  set(lightBank,pattern0,pattern1);
  TEST(lightBank[0] == 0xFFFFFFFF && lightBank[1] == 0xFFFFFFFF);

  //test 5 - bit per nibble
  lightBank[0] = 0;
  lightBank[1] = 0;
  pattern0 = 0x11111111;
  pattern1 = 0x11111111;
  set(lightBank,pattern0,pattern1);
  TEST(lightBank[0] == 0x11111111 && lightBank[1] == 0x11111111);

  //test 6 - pattern == lightBank
  lightBank[0] = 0x10101010;
  lightBank[1] = 0x01010101;
  pattern0 = 0x10101010;
  pattern1 = 0x01010101;
  set(lightBank,pattern0,pattern1);
  TEST(lightBank[0] == 0x10101010 && lightBank[1] == 0x01010101);

  //test 7- set both banks empty
  lightBank[0] = 0;
  lightBank[1] = 0;
  pattern0 = 0x00000001;
  pattern1 = 0x00000010;
  set(lightBank,pattern0,pattern1);
  TEST(lightBank[0] == 0x00000001 && lightBank[1] == 0x00000010);
}
/*
Function name : main()
Function prototyope : int main()
Description: Driver program to run testset()
Paramemters: none
Return value:0
*/
int main()
{
  testset();
  return 0;
}
