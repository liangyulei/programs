/*
 * Filename: testcharCompare.c
 * Author: TODO
 * Userid: TODO
 * Description: Unit test program to test the function charCompare().
 * Date: TODO
 * Sources of Help: TODO
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


  /*
   * TODO: YOU MUST WRITE MORE TEST CASES FOR FULL POINTS!
   * Some ideas are:
   *  - first character is smaller
   *  - first character is the same as second character
   *  - etc.
   */

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
