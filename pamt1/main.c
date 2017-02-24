/*
 * Filename: main.c
 * Author: Zhi Jia Teoh
 * Userid: cs30xjk
 * Description: Driver program for testing functions to compare
 *              sequential vs multithreading
 * Date: 23/Feb/2017
 * Sources of Help: Piazza
 */

#include <errno.h>

#include "pamt1.h"

#define BASE 10

/*
 * Function name: main()
 * Function prototype: int main( int argc, char *argv[] );
 * Description: 
 * Parameters: int argc (total args) , char *argv[] (arg values)
 * Side Effects: none
 * Error Conditions: None.
 * Return Value: 0 indicating successful execution.
 */

int main( int argc, char *argv[] ) {
  unsigned char data[] = { 0x41, 0x59, 0x47, 0x3F, 0x3C, 0x24,
                           0x58, 0x69, 0x65, 0x6D, 0x7D, 0x25 };
  size_t dataSize = sizeof(data);

  if ( argc != 2 ) {
    usage(argv[0], dataSize);
    exit( -1 );
  }

  struct result result;
  struct result1 result1;
  double startTime, endTime;
  double seqTime, parTime;

  /* Convert command-line arg to an unsigned long and initialize array */
  char *endptr;

  errno = 0;
  size_t arraySize = strtoul( argv[1], &endptr, BASE );

  if ( errno != 0 || *endptr != '\0' || arraySize < dataSize ) {
    usage(argv[0], dataSize);
    exit( -1 );
  }

  unsigned char *array = (unsigned char *) malloc( arraySize );

  if ( array == NULL ) {
     perror( "array is NULL" );
     (void) fprintf( stderr, "This is most likely due to array_size too large.\n" );
     exit( 1 );
  }

  (void) printf( "Using array size = %zu\n", arraySize );

  /* First do sequential initData */

  (void) printf( "Initializing array with values using " );
  (void) printf( "sequential initData()\n  [be patient with large values]\n" );

  startTime = omp_get_wtime();
  initData( array, arraySize, data, dataSize );
  endTime = omp_get_wtime();

  (void) printf( "\nChecking that sequential initData produced " );
  (void) printf( "the values as expected\n" );
  (void) printf( "Checking the first %zu bytes only\n", dataSize );
  (void) printf( "Should print out the string: \"CSE30 Rocks!\"\n" );

  char *expectedStr = "CSE30 Rocks!";
  int error = 0;

  for ( int i = 0; i < dataSize; i++ ) {
    (void) printf( "%c", array[i] );

    if ( array[i] != expectedStr[i] ) {
      error = 1;
      break;
    }
  }

  if ( error ) {
    (void) printf( "\nYour initData.c doesn't seem to be correct!\n" );
    (void) printf( "Exiting ...\n" );
    exit( 1 );
  }

  (void) printf( "\n\n" );

  seqTime = endTime - startTime;
  (void) printf( "Sequential initData time = %f\n\n", seqTime );

  /*
   * After initData (serial).
   * TODO: Comment out the return 0; below to continue to the next
   *       phase involving parallelizing initData.c
   */

  //return 0;


  /* Next do parallel initData using OpenMP directives */

  (void) printf( "Initializing array with same values using " );
  (void) printf( "parallel initData()\n  [be less patient with large values]\n" );

  /* Print number of threads on this system. Just thread #0 prints vs. all. */
  #pragma omp parallel
  {
    if ( omp_get_thread_num() == 0 ) {
      (void) printf( "Num of threads = %d\n", omp_get_num_threads() );
    }
  }

  for ( int i = 0; i < dataSize; i++ ) {
    array[i] = 'X';
  }

  startTime = omp_get_wtime();
  parallel_initData( array, arraySize, data, dataSize );
  endTime = omp_get_wtime();

  (void) printf( "\nChecking that parallel initData produced " );
  (void) printf( "the values as expected\n" );
  (void) printf( "Checking the first %zu bytes only\n", dataSize );
  (void) printf( "Should print out the string: \"CSE30 Rocks!\"\n" );

  for ( int i = 0; i < dataSize; i++ ) {
    (void) printf( "%c", array[i] );

    if ( array[i] != expectedStr[i] ) {
      error = 1;
    }
  }

  if ( error ) {
    (void) printf( "\nYour parallel_initData.c doesn't seem to be correct!\n" );
    (void) printf( "Exiting ...\n" );
    exit( 1 );
  }

  (void) printf( "\n\n" );

  parTime = endTime - startTime;
  (void) printf( "Parallel initData time = %f\n\n", parTime );

  (void) printf( "*** initData Speed-up: %f ***\n\n", seqTime / parTime );


  /*
   * After initData (paralle).
   * TODO: Comment out the return 0; below to continue to the next
   *       phase involving sequential squaredSumMinMax.c
   */

  //return 0;


  /* First do sequential sum, min, max */

  (void) printf( "Sequential squared sum, min, max [be patient]\n" );  

  startTime = omp_get_wtime();
  result = squaredSumMinMax( array, arraySize );
  endTime = omp_get_wtime();

  seqTime = endTime - startTime;
  (void) printf( "Sequential squaredSumMinMax time = %f\n\n", seqTime );

  (void) printf( "Squared Sum is: %llu\n", result.sum );
  (void) printf( "Min value is: %d\n", result.min );
  (void) printf( "Max value is: %d\n", result.max );
  (void) printf( "Completed in %f sec\n\n", seqTime );

  /*
   * After squaredSumMinMax (serial).
   * TODO: Comment out the return 0; below to continue to the next
   *       phase involving parallel_squaredSumMinMax.c
   */

  //return 0;


  /* Now do parallel sum, min, max using OpenMP directives */

  (void) printf( "Parallel squared sum, min, max [don't need to be as patient]\n" );  

  startTime = omp_get_wtime();
  result = parallel_squaredSumMinMax( array, arraySize );
  endTime = omp_get_wtime();

  parTime = endTime - startTime;
  (void) printf( "Parallel squaredSumMinMax time = %f\n\n", parTime );

  (void) printf( "Squared Sum is: %llu\n", result.sum );
  (void) printf( "Min value is: %d\n", result.min );
  (void) printf( "Max value is: %d\n", result.max );
  (void) printf( "Completed in %f sec\n\n", parTime );

  (void) printf( "*** squaredSumMinMax Speed-up: %f ***\n\n", seqTime / parTime );

  /*
   * After squaredSumMinMax (parallel).
   * TODO: Comment out the return 0; below to continue to the next
   *       phase involving sequential sqrtSumMinMax.c
   */

  //return 0;


  /* First do sequential square root sum, min, max */

  (void) printf( "Sequential sqrt sum, min, max [be patient]\n" );  

  startTime = omp_get_wtime();
  result1 = sqrtSumMinMax( array, arraySize );
  endTime = omp_get_wtime();

  seqTime = endTime - startTime;
  (void) printf( "Sequential sqrtSumMinMax time = %f\n\n", seqTime );

  (void) printf( "Sqrt Sum is: %f\n", result1.sum );
  (void) printf( "Min value is: %d\n", result1.min );
  (void) printf( "Max value is: %d\n", result1.max );
  (void) printf( "Completed in %f sec\n\n", seqTime );

  /*
   * After sqrtSumMinMax (serial).
   * TODO: Comment out the return 0; below to continue to the next
   *       phase involving parallel_qrtSumMinMax.c
   */

  //return 0;


  /* Now do parallel square root sum, min, max using OpenMP directives */

  (void) printf( "Parallel sqrt sum, min, max [don't need to be as patient]\n" );  

  startTime = omp_get_wtime();
  result1 = parallel_sqrtSumMinMax( array, arraySize );
  endTime = omp_get_wtime();

  parTime = endTime - startTime;
  (void) printf( "Parallel sqrtSumMinMax time = %f\n\n", parTime );

  (void) printf( "Sqrt Sum is: %f\n", result1.sum );
  (void) printf( "Min value is: %d\n", result1.min );
  (void) printf( "Max value is: %d\n", result1.max );
  (void) printf( "Completed in %f sec\n\n", parTime );

  (void) printf( "*** sqrtSumMinMax Speed-up: %f ***\n\n", seqTime / parTime );


  free(array);

  return 0;
}

/*
 * Function name: usage()
 * Function prototype: void usage( char *filename, size_t dataSize )
 * Description: Prints a brief usage message to stderr
 * Parameters: filename   name of this program, to be printed out in message
 *             dataSize   size of the data[] array
 * Side Effects: Prints usage message to stderr
 * Error Conditions: None.
 */

void usage( char *filename, size_t dataSize ) {
  (void) fprintf( stderr, "\nUsage: %s array_size\n", filename );
  (void) fprintf( stderr, "   array_size  (must be >= %zu and <= %u)\n\n",
                          dataSize, UINT_MAX );
}

