#include <stdio.h>
#include "utf_tamil.h"

#define TOTAL_TA_CODEPOINTS 128

/*
 * A Key-Value map:
 * To indicate the priority of the Tamil code points for string comparison 
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

/*
 * Function to get the type of the First UTF-8 code point in a string pointer 
 */
int utf_8_type(const char *str, LangCode *code) 
{
    if (str == NULL) 
        return -1;

    if (code != NULL) *code = LANG_UNKNOWN;
    
    if (str[0] > 0) {
        if (code != NULL) *code = LANG_ENGLISH;
        return 1;
    }
    
    if ((str[0] >= -64 && str[0] <= -33)
    && (str[1] >= -128 && str[1] <= -65)) {
        return 2;
    }
    
    if ((str[0] >= -32 && str[0] <= -17) 
    && (str[1] >= -128 && str[1] <= -65) 
    && (str[2] >= -128 && str[2] <= -65)) {
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
    
    if ((str[0] >= -16 && str[0] <= -12) 
    && (str[1] >= -128 && str[1] <= -65) 
    && (str[2] >= -128 && str[2] <= -65) 
    && (str[3] >= -128 && str[3] <= -65)) {
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

        if (f_lang != LANG_TAMIL && s_lang != LANG_TAMIL) return 0;
        if (f_lang != LANG_TAMIL) return 1;
        if (s_lang != LANG_TAMIL) return -1;

        printf("f_lang: %d, s_lang: %d\n", f_lang, s_lang);

        /*
         * Logic to get the key of each Tamil code points 
         * to get its value for comparison using utf_ta_map array
         */
        f_key = ((82 + first[f_index + 1]) * 64) + (128 + first[f_index + 2]);
        s_key = ((82 + second[s_index + 1]) * 64) + (128 + second[s_index + 2]);

        if (utf_ta_map[f_key] != utf_ta_map[s_key]) 
            return (utf_ta_map[f_key] - utf_ta_map[s_key]);

        f_index += f_jump;
        s_index += s_jump;
    }

    if (first[f_index] != '\0') return 1;
    if (second[s_index] != '\0') return -1;

    return 0;
} 