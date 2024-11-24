/*
 * utf8_tamil.h (renamed) 
 *
 *  Created on: 2024-11-03
 *      Author: deepaks
 *
 * Copyright (C) 2024 Deepak Shanmugam 
 */

#ifndef UTF8_TAMIL_H
#define UTF8_TAMIL_H 

/*
 * Enumeration to indicate the Language of the code points 
 */
typedef enum {
    UTF8_LANG_ENGLISH,
    UTF8_LANG_TAMIL,
    UTF8_LANG_UNKNOWN,
    UTF8_LANG_TOTAL
} UTF8_Lang;

/*
 * Enumeration to indicate the UTF-8 Type 
 */
typedef enum {
    UTF8_TYPE_UNKNOWN,
    UTF8_TYPE_1,
    UTF8_TYPE_2,
    UTF8_TYPE_3,
    UTF8_TYPE_4,
    UTF8_TYPE_TOTAL
} UTF8_Type;

/*
 * Function to get the info of initial codepoint in an UTF-8 string pointer
 * 1 indicates 1 byte UTF-8 (UTF8_TYPE_1)
 * 2 indicates 2 byte UTF-8 (UTF8_TYPE_2)
 * 3 indicates 3 byte UTF-8 (UTF8_TYPE_3)
 * 4 indicates 4 byte UTF-8 (UTF8_TYPE_4)
 * 
 * 0 indicates unknown type (UTF8_TYPE_UNKNOWN)
 *
 * Note: This also sets the Language of the initial codepoint 
 * only if UTF8_Lang pointer is NOT NULL
 */
UTF8_Type get_utf8_info(const char *str, UTF8_Lang *lang);

/*
 * Function to count the no of code points in an entire string (UTF-8)
 * Note: It only count the code point, not the letter 
 */
int get_utf8_cp_count(const char *str);

/*
 * Function to compare the TAMIL string in UTF-8 
 * to determine the lexicographic order 
 *
 * return value:
 * = 0 : indicates same string
 * -ve : indicates first string comes first 
 * +ve : indicates second string comes first 
 */
int utf8_compare_tamil(const char *first, const char *second);

#endif 
