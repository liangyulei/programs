/*
 * Filename: testcharCompare.c
 * Author: Zhi Jia Teoh
 * Userid: cs20xjk
 * Description: Unit test program to test the function charCompare().
 * Date: 22 Feb 2017
 * Sources of Help: piazza and TAs
 */ 

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"     /* For charCompare() function prototype */


/*
 * Unit Test for charCompare.s
 *
 * int charCompare( void const * p1, void const * p2 );
 *
 * Compares the two characters passed in.  Returns -1 if the first character
 * is smaller, 0 if the characters are the same, or +1 if the first character
 * is larger.
 */
void testcharCompare()
{
  char lhs;
  char rhs;

  (void) printf( "Testing charCompare()\n" );

  lhs = 'm';
  rhs = 'j';
  TEST( charCompare( &lhs, &rhs ) == 1 );

  lhs = 'l';
  rhs = 'l';
  TEST( charCompare( &lhs, &rhs ) == 0 );

  lhs = 'a';
  rhs = 'b';
  TEST(charCompare(&lhs,&rhs)==-1);

  (void) printf( "Finished running tests on charCompare()\n" );
}


int main() {
  testcharCompare();

  return 0;
}
