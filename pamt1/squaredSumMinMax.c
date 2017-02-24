/*
 * Filename: squaredSumMinMax.c
 * Author: Zhi Jia Teoh
 * Userid: cs30xjk
 * Description: Sums the square of each element in array a[] and finds the
 *              minimum and maximum value in the array.
 *              (Sequential version)
 * Date: 23/Feb/2017
 * Sources of Help: Piazza
 */

/*
 * See pamt1.h for definition of struct result
 */

#include "pamt1.h"

/*
 * Function name: squaredSumMinMax()
 *
 * Function prototype: struct result squaredSumMinMax( unsigned char a[],
 *                                                     size_t arraySize );
 *
 * Description: squares each element (a[i] * a[i]) and adds this to an
 *              accumulating sum. Find the min and max values in the array.
 *
 * Parameters: a[]        array to perform sum of squares, min, and max 
 *             arraySize  size of the array
 *
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: A struct result populated with the sum of the squares
 *               of each element, overall min and max values.
 */

struct result squaredSumMinMax( unsigned char a[], size_t size ) {
  //local struct var
  struct result result;
 
  //local vars
  unsigned long long sum=a[0]*a[0];
  unsigned int min=a[0];
  unsigned int max=a[0];
  
  //loop to calculate squaredSum,min and max
  for(size_t i = 1; i<size; i++)
  {
    sum=sum+(a[i]*a[i]);

    if(a[i]<min) min=a[i];
    if(a[i]>max) max=a[i];
  }
  
  //assign local vars to struct vars
  result.sum = sum;
  result.min = min;
  result.max = max; 

  return result; // return the struct by value
}

