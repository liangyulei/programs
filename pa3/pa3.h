/*
 * File: pa3.h
 * Description: Header file that contains function prototypes and
 *              constants.
 *
 * XXX Only add constants to this file at the bottom.
 * DO NOT EDIT FUNCTION PROTOTYPES OR PREDEFINED CONSTANTS
 *
 */
#ifndef PA3_H      /* Macro Guard */
#define PA3_H

#include <stdio.h> /* For FILE type */

/* Arg parsing */
#define ARG_STR "f:hi:s:"

#define CHAR_FILE_FLAG 'f'
#define CHAR_SIZE_FLAG 's'
#define CHAR_INFO_FLAG 'i'
#define CHAR_HELP_FLAG 'h'

/* Hashing */
#define HASH_START_VAL 11
#define HASH_PRIME     37

/* Sizes for Hash table */
#define MAX_SIZE 1000
#define MIN_SIZE 1
#define DEFAULT_SIZE 31

/* Default dictionary filename */
#define DEFAULT_DICT_FILENAME "/usr/dict/words"


/*
 * Enum Definitions
 */
enum usageMode { USAGE_SHORT, USAGE_LONG };


/* Struct Definitions */
struct HashTable {
  struct TableEntry * entryPtr; /* Pointer to the first element in the table */
  size_t size;                  /* Size of the table */
};

struct TableEntry {
  struct Anagram * anagramPtr;  /* Pointer to the first anagram */
  size_t numAnagrams;           /* Length of array pointed to by anagramPtr */
};

/* Create one anagram struct per unique sorted word */
struct Anagram {
  char sortedWord[BUFSIZ];     /* Sorted word from dictionary */
  size_t numWords;             /* Number of words that match in this node */
  char ** words;               /* Pointer to the array of matching words */
};


/* C Function Prototypes */
int initAnagram( char const * src, struct Anagram * anagram );
int findAnagrams( struct HashTable const * table );
int loadDict( char * filename, struct HashTable * table );
void printStats( struct HashTable const * table, int index );
void upperCaseSortString(char const * src, int n, char * dest );
void usage( FILE * stream, enum usageMode u, char const * progName );

/* Assembly Function Prototypes */
int charCompare( void const * p1, void const * p2 );
int getTableIndex(char const * ucSorted, size_t tableSize );
long isInBounds( long min, long dist, long val );
int hash(char const *str);
/*
 * Commented out to keep lint happy since this function isn't called from
 * C functions.
 *
 * int hash( char const * str );
 */

#endif /* PA3_H */
