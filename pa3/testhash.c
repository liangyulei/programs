#include "test.h"
#include "pa3.h"

void testhash()
{
  char const *str = "abc";
  TEST(hash(str) == 693701);

}
int main()
{
  testhash();
  return 0;
}

