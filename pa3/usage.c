/* Filename : usage.c
 * Author : Zhi Jia Teoh
 * User ID : cs30xjk
 * Description : Prints out the usage message by the modes
 * Date : 28 Feb 2017
 * Source of Help : Piazza and TAs
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pa3.h"
#include "pa3Strings.h"

/*
 * Function name : usage()
 * Prototype : void usage (FILE *, enum usageMode, const char * );
 * Description : prints usage message
 * Parameters : arg1 = stream to print to , arg2 = type of print
 *              ,arg3 = program name
 * Side Effects : none
 * Error Conditions : none
 * Return Value : void
 */

void usage(FILE * stream, enum usageMode u, const char * progName)
{
  if (u == USAGE_SHORT)
    (void)fprintf(stream,STR_USAGE_SHORT,progName,progName);
  else
    (void)fprintf(stream,STR_USAGE_LONG,progName,MIN_SIZE,MAX_SIZE);
}
