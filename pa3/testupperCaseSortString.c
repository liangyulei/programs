#include "pa3.h"
#include "test.h"
#include <strings.h>
void testfunction()
{
  char ret[BUFSIZ];
  char *src="abcfedgihljkmonp";
  upperCaseSortString(src,BUFSIZ,ret);
  (void)printf("%s",ret);
}

int main()
{
  testfunction();
  return 0;
}  
