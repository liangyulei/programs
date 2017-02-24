/*
 * Filename: sqrtSumMinMax.c
 * Author: Zhi Jia Teoh
 * Userid: cs30xjk
 * Description: Sums the square root of each element in array a[] and finds the
 *              minimum and maximum value in the array.
 *              (Sequential version)
 * Date: 23/Feb/2017
 * Sources of Help: Piazza
 */

#include <math.h> // Needed for sqrt() function prototype

/*
 * See pamt1.h for definition of struct result1
 */

#include "pamt1.h"

/*
 * Function name: sqrtSumMinMax()
 *
 * Function prototype: struct result1 sqrtSumMinMax( unsigned char a[],
 *                                                   size_t arraySize );
 *
 * Description: Gets the square root of each element (sqrt(a[i])) and adds
 *              this to an accumulating sum.
 *              Find the min and max values in the array.
 *
 * Parameters: a[]        array to perform square root, min, and max 
 *             arraySize  size of the array
 *
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: A struct result1 populated with the sum of the square roots
 *               of each element, overall min and max values.
 */

struct result1 sqrtSumMinMax( unsigned char a[], size_t size ) {
  //local struct var
  struct result1 result1;
  
  //local variables
  double sum=sqrt(a[0]);
  unsigned int min=a[0];
  unsigned int max=a[0];
  
  //loop to calculate sqrtSum, min and max
  for(size_t i = 1; i<size; i++)
  {
    sum = sum + sqrt(a[i]);
    
    if(a[i]<min) min=a[i];
    if(a[i]>max) max=a[i];
  }
  
  //assign local vars to struct vars
  result1.sum = sum;
  result1.min = min;
  result1.max = max;    

  return result1; // return the struct by value
}

