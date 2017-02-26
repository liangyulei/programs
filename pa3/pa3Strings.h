/*
 * File: pa3Strings.h
 * Description: Header file containing strings that are displayed to the user.
 * 
 * XXX DO NOT EDIT THIS FILE
 *
 */

#ifndef PA3_STRINGS_H /* Header guard */
#define PA3_STRINGS_H

/* Usage strings */
#define STR_USAGE_LONG "\n"\
  "Usage: %s [-f dictFile] [-s tableSize] [-i index] [-h]\n"\
  "Interactive anagram search.\n"\
  "  -f <dictFile>      Name of the dictionary file to use;\n"\
  "                     Defaults to /usr/dict/words if unspecified.\n"\
  "  -s <tableSize>     The size of the hashtable to be used;\n"\
  "                     Must be a decimal value within the range [%d - %d].\n"\
  "                     Defaults to 31 if unspecified.\n"\
  "  -i <index>         Display stats about the given table index.\n"\
  "  -h                 Print the long usage.\n"\
  "\n"

#define STR_USAGE_SHORT "\n"\
  "Usage: %s [-f dictFile] [-s tableSize] [-i index] [-h]\n"\
  "Try '%s -h' for more information.\n\n"

/* Strings for printing statistics */
#define STR_STATS_FOR_INDEX "\nDisplaying Stats for index [%d]:\n"
#define STR_NUM_WORDS       "\tNumber of words in the entry: %zd\n"
#define STR_COLLISIONS      "\tNumber of collisions: %zd\n"
#define STR_MAX_ANAGRAMS    "\tWord \"%s\" has the most anagrams (%zd).\n"
#define STR_MIN_ANAGRAMS    "\tWord \"%s\" has the least anagrams (%zd).\n"


/* Interactive prompt strings */
#define STR_USER_PROMPT "\nEnter a word to search for anagrams [^D to exit]: "
#define STR_NO_ANAGRAMS "No anagrams found.\n"
#define STR_FOUND_ANAGRAMS "Anagram(s) are:"
#define STR_SPACE_CHAR " "


/* Error strings */
#define STR_ERR_FILE_INVALID "\n"\
  "\tError opening dictionary file; invalid file.\n"
#define STR_ERR_FILE_PERMISSION "\n"\
  "\tError opening dictionary file; permission denied.\n"

#define STR_ERR_MEM_EXCEEDED  "\n\tMemory limit exceeded.\n"
#define STR_ERR_EXTRA_ARGS    "\n\tExtra operand '%s'.\n"
#define STR_ERR_RANGE         "\n\t%s must be within the range of [%d - %d].\n"
#define STR_ERR_CONVERTING    "\n\tConverting \"%s\" base \"%d\""
#define STR_ERR_NOTINT        "\n\t\"%s\" is not an integer.\n"
#define STR_ERR_INDEX         "index"
#define STR_ERR_SIZE          "size"

#endif /* PA3_STRINGS_H */