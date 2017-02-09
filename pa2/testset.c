#include <stdio.h>
#include <stdlib.h>
#include "pa2.h"
#include "test.h"


void testset()
{
  unsigned int lightBank[] = {0x00000001,0x00000002};
  const unsigned int pattern0 = 0x00000002;
  const unsigned int pattern1 = 0x00000001;

  printf("%d / %d \n",lightBank[0],lightBank[1]);

  set(lightBank,pattern0,pattern1);

  
  printf("%d / %d \n",lightBank[0],lightBank[1]);


  TEST(lightBank[0] == 0x00000003 && lightBank[1] == 0x00000003);
  
}

int main()
{
  testset();
  return 0;
}
