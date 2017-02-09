/*
 * Filename: testdisplayLights.c
 * Author: TODO
 * Userid: TODO
 * Description: Unit test program to test the function displayLights().
 * Date: TODO
 * Sources of Help: TODO
 */ 

#include <stdlib.h>
#include <signal.h>

#include <string.h>

#include "pa2.h"       /* For displayLights() function prototype */
#include "test.h"      /* For TEST() macro and stdio.h */

#define SYSRUN(CMD) (system(CMD))

void runTest( unsigned int bank[], char * expectedOutput, char * testDesc );

char * testFileName = ".test_displayLights_student_file";
FILE * testFilePtr;


/*
 * Unit Test for displayLights.s
 * 
 * void displayLights( const unsigned int lightBank[] );
 *
 * Displays the lights based on what bits are set in the lightBank array.
 * Prints '*' if a light is on, prints '-' if a light is off.  A space ' ' is
 * printed between each set of four lights.
 */
void testdisplayLights() {

  unsigned int lightBank[2];
  char * expected;


  /* Test 1 */
  fprintf( stderr, "\nRUNNING TEST 1!\n" );
   
  lightBank[0] = 0x0;
  lightBank[1] = 0x0;
  expected = "---- ---- ---- ---- ---- ---- ---- ---- "      /* lightBank[0] */
             "---- ---- ---- ---- ---- ---- ---- ---- \n";   /* lightBank[1] */
  runTest( lightBank, expected, "Test: 0x0, 0x0" );
  

  /* Test 2 */
  fprintf( stderr, "\nRUNNING TEST 2!\n" );
  
  lightBank[0] = 0x11111111;
  lightBank[1] = 0x88888888;
  expected = "---* ---* ---* ---* ---* ---* ---* ---* "
             "*--- *--- *--- *--- *--- *--- *--- *--- \n";
  runTest( lightBank, expected, "Test: 0x11111111, 0x88888888" );


    fprintf( stderr, "\nRUNNING TEST 3!\n" );
  
    lightBank[0] = 0xf0f0f0f0;
    lightBank[1] = 0x01010101;
    expected = "**** ---- **** ---- **** ---- **** ---- "
               "---- ---* ---- ---* ---- ---* ---- ---* \n";
    runTest( lightBank, expected, "Test: 0xf0f0f0f0, 0x01010101" );


  
  /* TODO: YOU MUST WRITE MORE TEST CASES FOR FULL POINTS! */
}


/*
 * Function Name: runTest()
 * Function Prototype: void runTest( unsigned int bank[], char * expectedOutput,
                                     char * testDesc );
 * Description:  Helper function to actually run a test of displayLights.
 *               Prints test description (as specified by testDesc), and
 *               calls displayLights, handling segfaults.
 * Parameters:
 *     arg1: unsigned int bank[] -- bank of lights
 *     arg2: char * expectedOutput -- the expected output to be printed by
 *                                    displayLights()
 *     arg3: char * testDesc -- Description of the test being run
 * Side Effects: Outputs the result of the test to stdout
 * Error Conditions: None
 * Return Value: None
 */
void runTest( unsigned int bank[], char * expectedOutput, char * testDesc ) {
  char buf[BUFSIZ] = {0};

  /* Print test description */
  fprintf( stderr, "\n%s\n", testDesc );

  /* Display the lights and flush stdout */
  displayLights( bank );
  fflush( stdout );

  /* Reset file pointer */
  fseek( testFilePtr, -strlen(expectedOutput), SEEK_END );

  /* Read from test file and compare */
  fgets( buf, BUFSIZ, testFilePtr );

  TEST( strncmp( buf, expectedOutput, BUFSIZ ) == 0 );
  
}


int main() {

  /* 
   * Begin setup to capture stdout to a file.  You aren't expected to know how
   * to do this, but it never hurts to learn!
   */
  testFilePtr = fopen( testFileName, "w+" );
  if ( testFilePtr == NULL ) {
    perror( "Could not open test file" );
    exit( 1 );
  }

  if ( dup2( fileno( testFilePtr ), fileno( stdout ) ) == -1 ) {
    perror( "Could not duplicate stdout file descriptor" );
    exit( 1 );
  }
  /* End setup to capture stdout */

  fprintf( stderr, "Running tests for displayLights...\n" );
  testdisplayLights();
  fprintf( stderr, "\nDone running tests!\n" );

  /* Close file when done */
  fclose( testFilePtr );

  return 0;
}
