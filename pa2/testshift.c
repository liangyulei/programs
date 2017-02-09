/*
 * Filename: testshift.c
 * Author: TODO
 * Userid: TODO
 * Description: Unit test program to test the function shift().
 * Date: TODO
 * Sources of Help: TODO
 */ 

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa2.h"     /* For shift() function prototype */


/*
 * Unit Test for shift.s
 *
 * void shift( unsigned int lightBank[], const int shiftCnt );
 * 
 * Shifts the current light pattern in the lightBank by shiftCnt places.
 * If shiftCnt is positive, shift left.  If shiftCnt is negative, shift right.
 */
void testshift()
{
  unsigned int lightBank[2];
  int shiftCnt;

  (void) printf( "Testing shift()\n" );


  /* Shift left by 1 bit */
  lightBank[0] = 0xCAFEBABE;
  lightBank[1] = 0xDECAFBAD;
  shiftCnt = 1;
 
  shift( lightBank, shiftCnt );
  TEST( lightBank[0] == 0x95FD757D && lightBank[1] == 0xBD95F75A );


  /* Shift right by 1 bit */
  lightBank[0] = 0xCAFEBABE;
  lightBank[1] = 0xDECAFBAD;
  shiftCnt = -1;

  shift( lightBank, shiftCnt );
  TEST( lightBank[0] == 0x657F5D5F && lightBank[1] == 0x6F657DD6 );


  /*
   * TODO: YOU MUST WRITE MORE TEST CASES FOR FULL POINTS!
   * Some ideas are:
   *  - Test shifting left, right, and not at all
   *  - Test different shift amounts less than, equal to, and greater than 32
   */

  lightBank[0] = 0xFFFF0000;
  lightBank[1] = 0x0000FFFF;
  shiftCnt = 0;

  shift(lightBank, shiftCnt);
  TEST( lightBank[0] == 0xFFFF0000 && lightBank[1] == 0x0000FFFF );

  
  lightBank[0] = 0x00000000F;
  lightBank[1] = 0x00000000F;
  shiftCnt = 32;

  shift(lightBank,shiftCnt);
  TEST(lightBank[0] == 0x0000000F && lightBank[1] == 0x00000000);

  lightBank[0] = 0x00000000F;
  lightBank[1] = 0x00000000F;
  shiftCnt = 33;

  shift(lightBank,shiftCnt);
  TEST(lightBank[0] == 0x0000001E && lightBank[1] == 0x00000000);

  printf( "Finished running tests on shift()\n" );
}


int main() {
  testshift();

  return 0;
}
