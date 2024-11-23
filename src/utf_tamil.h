/*
 * utf_tamil.h 
 *
 *  Created on: 2024-11-03
 *      Author: deepaks
 *
 * Copyright (C) 2024 Deepak Shanmugam 
 */

#ifndef UTF_TAMIL_H
#define UTF_TAMIL_H 

/*
 * Enumeration to indicate the Language of the code points 
 */
typedef enum {
    LANG_UNKNOWN,
    LANG_ENGLISH,
    LANG_TAMIL
} UTF8_Lang;

/*
 * Enumeration to indicate the UTF-8 Type 
 */
typedef enum {
    UTF8_TYPE_UNKNOWN   = 0,
    UTF8_TYPE_1         = 1,
    UTF8_TYPE_2         = 2,
    UTF8_TYPE_3         = 3,
    UTF8_TYPE_4         = 4
} UTF8_Type;

/*
 * Function to get the type of the first UTF-8 code point in a string pointer
 * 1 indicates 1 byte UTF-8
 * 2 indicates 2 byte UTF-8
 * 3 indicates 3 byte UTF-8
 * 4 indicates 4 byte UTF-8
 * 
 * 0 indicates unknown type
 * -1 indicates error
 *
 * Note: This also sets the Language of the code point 
 * only if code pointer is NOT NULL
 */
int utf_8_type(const char *str, UTF8_Lang *code);

/*
 * Function to count the no of code points in an entire string 
 * Note: It only count the code point, not the letter 
 */
int utf_8_cp_count(const char *str);

/*
 * Function to compare the TAMIL string in UTF-8 
 * to determine the lexicographic order 
 *
 * return value:
 * = 0 : indicates same string
 * -ve : indicates first string comes first 
 * +ve : indicates second string comes first 
 */
int utf_8_ta_compare(const char *first, const char *second);

#endif 
