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

#define TOTAL_TA_CODEPOINTS 128

/*
 * A Key-Value map:
 * To indicate the priority of the Tamil code points for string comparison 
 * based on the values of 2nd and 3rd byte of a code point 
 * (Note: refer utf-8-analysis.txt document for more details) 
 * 
 * Rank:
 * 1        : pulli 
 * 2 to 13  : uyir 
 * 14       : aaitham
 * 15 to 28 : First 14 agara uyirmei
 * 29 to 32 : last 4 agara uyirmei
 * 33       : "ja" non-tamil letter
 * 34 to 37 : other 4 non-tamil letters
 * 38 to 48 : inaippu letters which makes other uyir mei 
 * 49 to 58 : tamil numbers 
 * 59 to 72 : remaining 
 */
static const int utf_ta_map[TOTAL_TA_CODEPOINTS] = {
    0, 0, 72, 14, 0, 2, 3, 4, 5, 6, 7, 0, 0, 0, 8, 9, 
    10, 0, 11, 12, 13, 15, 0, 0, 0, 16, 17, 0, 33, 0, 18, 19, 
    0, 0, 0, 20, 21, 0, 0, 0, 22, 32, 23, 0, 0, 0, 24, 25, 
    26, 31, 27, 30, 29, 28, 34, 35, 36, 37, 0, 0, 0, 0, 38, 39, 
    40, 41, 42, 0, 0, 0, 43, 44, 45, 0, 46, 47, 48, 1, 0, 0, 
    70, 0, 0, 0, 0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 
    59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 0, 0, 0, 0, 0
};

static int utf_8_cp_rank(const char *str, int utf_8_type, LangCode code);


/*
 * Function to get the type of the First UTF-8 code point in a string pointer 
 */
int utf_8_type(const char *str, LangCode *code) 
{
    if (str == NULL) 
        return -1;

    if (code != NULL) *code = LANG_UNKNOWN;
    
    if ((str[0] & 0x80) == 0x00) {
        if (code != NULL && (str[0] >= 'a' && str[0] <= 'z')
        && (str[0] >= 'A' && str[0] <= 'Z')) {
            *code = LANG_ENGLISH;
        } 
        return 1;
    }
    
    if (((str[0] & 0xE0) == 0xC0) && ((str[1] & 0xC0) == 0x80)) {
        return 2;
    }
    
    if (((str[0] & 0xF0) == 0xE0) && ((str[1] & 0xC0) == 0x80) 
    && ((str[2] & 0xC0) == 0x80)) {
        //puts("debug: 3 byte utf-8");
        if (code != NULL) {
            //puts("debug: code is NOT NULL");
            if (str[0] == -32 && (str[1] == -82 || str[1] == -81)) {
                //puts("debug: tamil");
                *code = LANG_TAMIL;
            } 
        } 
        return 3;
    }
    
    if (((str[0] & 0xF8) == 0xF0) && ((str[1] & 0xC0) == 0x80) 
    && ((str[2] & 0xC0) == 0x80) && ((str[3] & 0xC0) == 0x80)) {
        return 4;
    }
    
    return 0;
}

/*
 * Function to count the UTF-8 code points in a string 
 */
int utf_8_cp_count(const char *str) 
{
    int index = 0;
    int count = 0;
    int jump;

    if (str == NULL) 
        return -1;

    while(str[index] != '\0') {
        jump = utf_8_type(&str[index], NULL);

        if (jump == 0) jump = 1;

        index += jump;
        count++;
    }

    return count;
}

/*
 * Function to compare TAMIL string in UTF-8 format 
 * Note: Works best if the string is entirely tamil 
 */
int utf_8_ta_compare(const char *first, const char *second) 
{
    int f_index = 0, s_index = 0;
    int f_jump, s_jump;
    int f_key, s_key;
    LangCode f_lang, s_lang;

    if (first == NULL && second == NULL) 
        return 0;

    if (first == NULL) 
        return 1;

    if (second == NULL) 
        return -1;

    while (first[f_index] != '\0' && second[s_index] != '\0') {
        f_jump = utf_8_type(&first[f_index], &f_lang);
        s_jump = utf_8_type(&second[s_index], &s_lang);

        if (f_jump == 0) f_jump = 1;
        if (s_jump == 0) s_jump = 1;

        if (f_lang != LANG_TAMIL && s_lang != LANG_TAMIL) {
            f_key = utf_8_cp_rank(&first[f_index], f_jump, f_lang);
            s_key = utf_8_cp_rank(&second[s_index], s_jump, s_lang);

            if (f_key != s_key) {
                return f_key - s_key;
            }

            f_index += f_jump;
            s_index += s_jump;
            continue;
        }

        if (f_lang != LANG_TAMIL) return 1;
        if (s_lang != LANG_TAMIL) return -1;

        /*
         * Logic to get the key of each Tamil code points 
         * used to get its map-value for comparison using utf_ta_map array 
         */
        f_key = ((first[f_index + 1] & 1) * 64) + (128 + first[f_index + 2]);
        s_key = ((second[s_index + 1] & 1) * 64) + (128 + second[s_index + 2]);

        if (utf_ta_map[f_key] != utf_ta_map[s_key]) 
            return (utf_ta_map[f_key] - utf_ta_map[s_key]);

        f_index += f_jump;
        s_index += s_jump;
    }

    if (first[f_index] != '\0') { 
        utf_8_type(&first[f_index], &f_lang);
        if (f_lang == LANG_TAMIL) {
            if (first[f_index + 2] == -115) {
                return -1;
            }
        }
        return 1;
    }

    if (second[s_index] != '\0') {
        utf_8_type(&second[s_index], &s_lang);
        if (s_lang == LANG_TAMIL) {
            if (second[s_index + 2] == -115) {
                return 1;
            }
        }
        return -1;
    }

    return 0;
} 

/*
 * Function to get the rank of the NON-TAMIL code points in UTF-8
 * if rank is lower, then the letter has lexicographically lower order
 * else, otherwise 
 * 
 * we form the rank by just multiplying the 'unsigned char' value of 
 * each byte in a code point 
 * Note: This is applicable only for 'NON-TAMIL' code points 
 */
static int utf_8_cp_rank(const char *str, int utf_8_type, LangCode code) 
{
    int rank = 1;
    int index;

    if (str == NULL) {
        return -1;
    }

    if (utf_8_type == 1) {
        if (code == LANG_ENGLISH && str[0] >= 'a' && str[0] <= 'z') {
            return (str[0] - 32);
        }
        return ((str[0] & 0x80) ? -1 : str[0]);
    }

    for (index = 0; index < utf_8_type; index++) {
        rank *= (unsigned char) str[index];
    }

    return rank;
} 