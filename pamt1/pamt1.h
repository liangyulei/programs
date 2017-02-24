#ifndef PAMT1_H   /* Macro Guard */
#define PAMT1_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

#include <omp.h>  // For OpenMP directives

/*
 * Used in initData.c and parallel_initData.c
 */
#define BIT_7 0x80
#define BIT_0 0x01
#define BITS_IN_A_BYTE 8
#define BITS_IN_A_NIBBLE 4
#define UPPER_NIBBLE 0xF0

/*
 * Local function prototypes for PAMT1
 */

void initData( unsigned char a[],
               size_t arraySize,
               unsigned char data[],
               size_t dataSize );

void parallel_initData( unsigned char a[],
                        size_t arraySize,
                        unsigned char data[],
                        size_t dataSize );


struct result squaredSumMinMax( unsigned char a[],
                                size_t arraySize );

struct result parallel_squaredSumMinMax( unsigned char a[],
                                         size_t arraySize );

struct result1 sqrtSumMinMax( unsigned char a[],
                              size_t arraySize );

struct result1 parallel_sqrtSumMinMax( unsigned char a[],
                                       size_t arraySize );

void usage( char *filename,
            size_t dataSize );

/*
 * If you want to see what size_t is typdef'ed to be:
 *
 *   echo '#include <stdlib.h>' | cpp | egrep 'typedef .* size_t'
 */

/*
 * The data structure to encapsulate the results of the calculations.
 */

struct result {
  unsigned long long int sum;
  unsigned int min;
  unsigned int max;
};

struct result1 {
  double sum;
  unsigned int min;
  unsigned int max;
};

#endif  /* PAMT1_H */

