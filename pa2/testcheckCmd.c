#include <stdio.h>
#include <stdlib.h>
#include "pa2.h"
#include "test.h"


void testcmd()
{
  const char * const cmdString = "command";
  const char * const commands [] = {"not1","not2","command","not3",0};

  int ret = checkCmd(cmdString,commands);
  
  TEST(ret == 1);
  
  const char * const cmdString1 = "command";
  const char * const commands1 [] = {"not1","not2","not3","not4",0};

  int ret2 = checkCmd(cmdString1,commands1);
  TEST(ret2==-1);
}

int main()
{
  testcmd();
  return 0;
}

