#include <stdlib.h>
#include <stdio.h>

void clear(unsigned int lightBank[],const unsigned int pattern0,
            const unsigned int pattern1)
{

  lightBank[0] = lightBank[0] & (~pattern0);
  lightBank[1] = lightBank[1] & (~pattern1);
}
