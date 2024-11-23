/*
 * utf_tamil.c 
 *
 *  Created on: 2024-11-03
 *      Author: deepaks
 *
 * Copyright (C) 2024 Deepak Shanmugam 
 */

#include <stdio.h>
#include "utf_tamil.h"

#define TOTAL_TAMIL_CODEPOINTS 128

/*
 * A Key-Value map:
 * To indicate the priority of the Tamil lang points for string comparison 
 * based on the values of 2nd and 3rd byte of a lang point 
 * (Note: refer utf-8-analysis.txt document for more details) 
 * 
 * Rank:
 * 1        : pulli 
 * 2 to 13  : uyir 
 * 14       : aaitham
 * 15 to 28 : First 14 agara uyirmei
 * 29 to 32 : last 4 agara uyirmei
 * 33       : "ja" vadamozhi letter
 * 34 to 37 : other 4 vadamozhi letters
 * 38 to 48 : inaippu letters which makes other uyir mei 
 * 49 to 58 : tamil numbers 
 * 59 to 72 : remaining 
 */
static const int utf8_tamil_key_map[TOTAL_TAMIL_CODEPOINTS] = {
    0   ,0  ,72 ,14 ,0  ,2  ,3  ,4  ,5  ,6  ,7  ,0  ,0  ,0  ,8  ,9  
    ,10 ,0  ,11 ,12 ,13 ,15 ,0  ,0  ,0  ,16 ,17 ,0  ,33 ,0  ,18 ,19 
    ,0  ,0  ,0  ,20 ,21 ,0  ,0  ,0  ,22 ,32 ,23 ,0  ,0  ,0  ,24 ,25
    ,26 ,31 ,27 ,30 ,29 ,28 ,34 ,35 ,36 ,37 ,0  ,0  ,0  ,0  ,38 ,39
    ,40 ,41 ,42 ,0  ,0  ,0  ,43 ,44 ,45 ,0  ,46 ,47 ,48 ,1  ,0  ,0
    ,70 ,0  ,0  ,0  ,0  ,0  ,0  ,71 ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0
    ,0  ,0  ,0  ,0  ,0  ,0  ,49 ,50 ,51 ,52 ,53 ,54 ,55 ,56 ,57 ,58
    ,59 ,60 ,61 ,62 ,63 ,64 ,65 ,66 ,67 ,68 ,69 ,0  ,0  ,0  ,0  ,0
};

typedef int (*CompareFunction)(const char *first, const char *second);

static int compare_default_cp(const char *first, const char *second);
static int compare_tamil_cp(const char *first, const char *second);

typedef struct {
    UTF8_Lang       language;
    UTF8_Type       type;
    CompareFunction fn_compare;
} UTF8_LanguageSet; 

/*
 * **WARNING**: The below order should follow the UTF8_Lang Type 
 * If any modification in future: remember the above 
 * Note: This is implemented because of future modification/additions in mind 
 */
UTF8_LanguageSet lang_object_map[UTF8_LANG_TOTAL] = {
    {UTF8_LANG_TAMIL    ,UTF8_TYPE_3        ,compare_tamil_cp},
    {UTF8_LANG_ENGLISH  ,UTF8_TYPE_1        ,compare_default_cp},
    {UTF8_LANG_UNKNOWN  ,UTF8_TYPE_UNKNOWN  ,compare_default_cp}
};

/*
 * Function to get the type of the First UTF-8 code point in a string pointer 
 */
int get_utf8_info(const char *str, UTF8_Lang *lang) 
{
    if (str == NULL) 
        return UTF8_TYPE_UNKNOWN;

    if (lang != NULL) *lang = UTF8_LANG_UNKNOWN;
    
    if ((str[0] & 0x80) == 0x00) {
        /* Set corresponding Language of this type */
        if (lang != NULL) {
            *lang = UTF8_LANG_ENGLISH;
        } 
        return UTF8_TYPE_1;
    }
    
    if (((str[0] & 0xE0) == 0xC0) && ((str[1] & 0xC0) == 0x80)) {
        return UTF8_TYPE_2;
    }
    
    if (((str[0] & 0xF0) == 0xE0) && ((str[1] & 0xC0) == 0x80) 
    && ((str[2] & 0xC0) == 0x80)) {
        if (lang != NULL) {
            /* Set corresponding Language of this type: only tamil can be found now */
            if (str[0] == -32 && (str[1] == -82 || str[1] == -81)) {
                *lang = UTF8_LANG_TAMIL;
            } 
        } 
        return UTF8_TYPE_3;
    }
    
    if (((str[0] & 0xF8) == 0xF0) && ((str[1] & 0xC0) == 0x80) 
    && ((str[2] & 0xC0) == 0x80) && ((str[3] & 0xC0) == 0x80)) {
        return UTF8_TYPE_4;
    }
    
    return UTF8_TYPE_UNKNOWN;
}

/*
 * Function to count the UTF-8 code points in a string 
 */
int get_utf8_cp_count(const char *str) 
{
    int index = 0;
    int count = 0;
    int jump;

    if (str == NULL) return -1;

    while(str[index] != '\0') {
        jump = get_utf8_info(&str[index], NULL);

        if (jump == 0) jump = 1;

        index += jump;
        count++;
    }

    return count;
}

/*
 * Function to compare string in UTF-8 format (most suitable for Tamil) 
 * Note: Currently this works best for TAMIL language, hence this name 
 */ 
int utf8_compare_tamil(const char *first, const char *second) 
{
    int f_index, s_index;
    int f_jump, s_jump;
    int comparison;

    UTF8_Lang f_lang, s_lang;

    if (first == NULL && second == NULL) return 0;
    if (first == NULL) return -1;
    if (second == NULL) return 1;

    f_index = 0;
    s_index = 0;

    while (first[f_index] != '\0' && second[s_index] != '\0') {
        f_jump = get_utf8_info(&first[f_index], &f_lang);
        s_jump = get_utf8_info(&second[s_index], &s_lang);

        if (f_jump == UTF8_TYPE_UNKNOWN) f_jump = 1;
        if (s_jump == UTF8_TYPE_UNKNOWN) s_jump = 1;

        if (f_lang != s_lang) {
            return f_lang - s_lang;
        }

        comparison = lang_object_map[f_lang].fn_compare(&first[f_index], &second[s_index]);
        if (comparison != 0) {
            return comparison;
        }

        f_index += f_jump;
        s_index += s_jump;
    }

    if (first[f_index] != '\0') return 1;
    if (second[s_index] != '\0') return -1;

    return 0;
} 

/*
 * Function to compare the initial codepoints in default way!
 * **BEWARE**: When this function is being called, that means 
 * 1. UTF8_Type of initial codepoints of first and second string should be equal 
 */ 
static int compare_default_cp(const char *first, const char *second) 
{
    UTF8_Type utf8_type;
    int index;

    utf8_type = get_utf8_info(first, NULL);

    if (utf8_type == UTF8_TYPE_UNKNOWN) {
        return (first[0] - second[0]);
    }

    if (utf8_type == UTF8_TYPE_1) {
        return (first[0] - second[0]);
    }

    for (index = 0; index < utf8_type; index++) {
        if (first[index] != second[index]) {
            return (first[index] - second[index]);
        }
    }

    return 0;
}

/*
 * Function to compare the initial codepoints of the TAMIL strings 
 * **BEWARE**: If this function is being called, that means
 * 1. The Language of initial codepoints of first and second strings should be TAMIL 
 */
static int compare_tamil_cp(const char *first, const char *second) 
{
    int f_key, s_key;
    int f_rank, s_rank;
    UTF8_Lang f_lang_next, s_lang_next;

    f_key = ((first[1] & 1) * 64) + (128 + first[2]);
    s_key = ((second[1] & 1) * 64) + (128 + second[2]);

    f_rank = utf8_tamil_key_map[f_key];
    s_rank = utf8_tamil_key_map[s_key];
    
    if (f_rank == s_rank) {
        /*
         * The below scenario to handle 
         * comparison between 'agara uyir mei' and its own 'mei',
         * when the next codepoint of the word with 'agara uyir mei' is "Not-Tamil"
         * in this case, the word which is having 'mei' should comes first in order 
         * Example: first = "பட" (ப+ட+'\0') vs second = "பட்" (ப+ட+்+'\0')
         * in the above example, '\0' is a non-tamil code point (it can be any non-tamil cp)
         * Expectation: compare(first, second), returns 1
         * If we don't handle it here, it will cause the different output (opposite one) 
         */
        if (f_rank >= 15 && f_rank <= 37) {
            get_utf8_info(&first[3], &f_lang_next);
            get_utf8_info(&second[3], &s_lang_next);
            if (s_lang_next != UTF8_LANG_TAMIL && f_lang_next == UTF8_LANG_TAMIL) {
                if (first[5] == -115) {
                    return -1;
                }
            }
            if (f_lang_next != UTF8_LANG_TAMIL && s_lang_next == UTF8_LANG_TAMIL) {
                if (second[5] == -115) {
                    return 1;
                }
            }
        } 
    }

    return (f_rank - s_rank);
} 
