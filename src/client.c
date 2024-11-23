/*
 * client.c: 
 * a sample client program to test the utf_tamil.h modules 
 *
 *  Created on: 2024-11-03
 *      Author: deepaks
 *
 * Copyright (C) 2024 Deepak Shanmugam 
 */

#include <stdio.h>
#include "utf_tamil.h"

void test1();
void test2();
void test3();

int main(int argc, char *argv[]) {
    test3();

    return 0;
} 

void test1() {
    char *str1 = "வணக்கம்";
    char *str2 = "फायदे";
    char *str3 = "భారతదేశం";
    char *str4 = "സ്വതന്ത്ര";
    char *str5 = "test";
    char *str6 = "";

    printf("return value of comparison: %d\n", utf_8_ta_compare(str1, str6));
    printf("No of code points in str1: %d\n", utf_8_cp_count(str1));
    printf("No of code points in str2: %d\n", utf_8_cp_count(str2));
}

void test2() {
    char *str[9];
    str[0] = "2eஅ";
    str[1] = "படம்";
    str[2] = "படு";
    str[3] = "பட்டம்";
    str[4] = "2eம";
    str[5] = "பட";
    str[6] = "பட்";
    str[7] = "க";
    str[8] = "க்";

    char *temp;

    for (int i=0; i<8; i++) {
        //printf("%d: ",i);
        for (int j=i+1; j<9; j++) {
            //printf("%d, ", j);
            if (utf_8_ta_compare(str[i],str[j]) > 0) {
                temp = str[j];
                str[j] = str[i];
                str[i] = temp;
            }
        }
        //puts("");
    }

    for (int i=0; i<9; i++) {
        puts(str[i]);
    }
}

void test3() {
    char first[128];
    char second[128];

    puts("Enter first: ");
    fgets(first, 128, stdin);
    puts("Enter second: ");
    fgets(second, 128, stdin);

    printf("utf_8_ta_compare: %d\n", utf_8_ta_compare(first, second));
} 
