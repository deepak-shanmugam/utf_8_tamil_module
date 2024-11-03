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

int main(int argc, char *argv[]) {
    char *str1 = "படம்";
    char *str2 = "பட்டம்";

    printf("return value of comparison: %d\n", utf_8_ta_compare(str1, str2));
    printf("No of code points in str1: %d\n", utf_8_cp_count(str1));
    printf("No of code points in str2: %d\n", utf_8_cp_count(str2));

    return 0;
} 