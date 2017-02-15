/*
 * Filename: testshift.c
 * Author: Zhi Jia Teoh
 * Userid: cs30xjk
 * Description: Unit test program to test the function shift().
 * Date: 14 Feb 2017
 * Sources of Help: Piazza and TAs
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

  //shift by zero bits
  lightBank[0] = 0xFFFF0000;
  lightBank[1] = 0x0000FFFF;
  shiftCnt = 0;
  shift(lightBank, shiftCnt);
  TEST( lightBank[0] == 0xFFFF0000 && lightBank[1] == 0x0000FFFF );

  //shift 32 bits
  lightBank[0] = 0x00000000F;
  lightBank[1] = 0x00000000F;
  shiftCnt = 32;
  shift(lightBank,shiftCnt);
  TEST(lightBank[0] == 0x0000000F && lightBank[1] == 0x00000000);

  //shift 63 bits
  lightBank[0] = 0xFFFFFFFF;
  lightBank[1] = 0x00000001;
  shiftCnt=63;
  shift(lightBank,shiftCnt);
  TEST(lightBank[0] == 0x80000000 && lightBank[1] == 0x00000000);

  //shift 64 bits
  lightBank[0] = 0x00000000F;
  lightBank[1] = 0x00000000F;
  shiftCnt = 64;
  shift(lightBank,shiftCnt);
  TEST(lightBank[0] == 0x0000000F && lightBank[1] == 0x0000000F);

  //shift -63 bits
  lightBank[0] = 0xFFFFFFFF;
  lightBank[1] = 0xFFFFFFFF;
  shiftCnt = -63;
  shift(lightBank,shiftCnt);
  TEST(lightBank[0] == 0x00000000 && lightBank[1] == 0x00000001);

  //shift -64 bits
  lightBank[0] = 0xFFFFFFFF;
  lightBank[1] = 0xFFFFFFFF;
  shiftCnt = -64;
  shift(lightBank,shiftCnt);
  TEST(lightBank[0] == 0xFFFFFFFF && lightBank[1] == 0xFFFFFFFF);

  //shift one hex char
  lightBank[0] = 0x00000001;
  lightBank[1] = 0x00000001;
  shiftCnt = 4;
  shift(lightBank,shiftCnt);
  TEST(lightBank[0] == 0x00000010 && lightBank[1] == 0x00000010);
  printf( "Finished running tests on shift()\n" );
}

/*
main function to run testshift()
*/
int main() {
  testshift();

  return 0;
}
