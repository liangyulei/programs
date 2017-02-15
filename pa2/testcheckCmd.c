/*
Filename : testcheckCmd.c
Author : Zhi Jia Teoh
USER ID : cs30xjk
Date : Feb 8 2017
Description : This program tests checkCmd.c
Sources of help : Handout and Piazza
*/

#include <stdio.h>
#include <stdlib.h>
#include "pa2.h"
#include "test.h"

/*
Function name: testcmd()
Function prototyope : void testcmd()
Parameters : none
Return : voided
Description : Multiple test cases for checkCmd.c
*/

void testcmd()
{
  //command first index
  const char * const cmdString = "command";
  const char * const commands [] = {"command","not1","not2","not3",0};
  int ret = checkCmd(cmdString,commands); 
  TEST(ret == 0);
  
  //command last index
  const char * const cmdString1 = "command";
  const char * const commands1 [] = {"not1","not2","not3","command",0};
  int ret2 = checkCmd(cmdString1,commands1);
  TEST(ret2 == 3);

  //null input
  const char * const cmdString2 = "";
  const char * const commands2 [] = {"not1","not2","not3","command",0};
  int ret3 = checkCmd(cmdString2,commands2);
  TEST(ret3 == -1);

  //null commands 
  const char * const cmdString3 = "command";
  const char * const commands3 [] = {0};
  int ret4 = checkCmd(cmdString3,commands3);
  TEST(ret4 == -1);

  //multiple commands
  const char * const cmdString4 = "command1 command2";
  const char * const commands4 [] = {"command1","command2",0};
  int ret5 = checkCmd(cmdString4,commands4);
  TEST(ret5 == -1);

}
/*
Function name : main()
Function prototyope : int main()
Parameters: non
Return : 0
Description : Driver to run testcmd()
*/
int main()
{
  testcmd();
  return 0;
}

