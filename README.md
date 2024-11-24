# utf_8_tamil_module
C library to primarily handle the tamil unicode letters in utf-8 format. 

# Supported Platform 
> Linux, Windows, MAC 

# Build 
To compile using gcc: 
```
gcc -o test client.c utf8_tamil.c 
```
To run: 
```
./test
```

# Supported Functionality 
- To get the no of codepoints present in a string: int get_utf8_cp_count(const char *string); 
- To get the UTF8 information (UTF8_Type and UTF8_Lang) of the first codepoint in a string: UTF8_Type get_utf8_info(const char *string, UTF8_Lang *lang); 
- To compare the UTF-8 string for searching, sorting based on the lexicographic order: int utf8_compare_tamil(const char *first, const char *second); 
- Note: The above compare function works best for TAMIL and ENGLISH based on Lexicographic order. Also, can detect only these 2 languages.

# Points to be noted for UTF-8 string comparison  
- **utf8_compare_tamil()** - this function works best for TAMIL and ENGLISH as currently the lexicographic order is maintained only for these 2 languages. 
- The function gives proper result for these languages even if a single string contains codepoints of any languages and types. 
- The proper Lexicographic order for remaining languages are currently not maintained. So, it follows the default order of codepoints of those languages. 
- Yet this function is scalable that we can integrate the proper functionality for other languages also. So that a proper lexicographic order can be achievable for any multi-languages here. 
- If you want to add those support for other language, kindly let me know. so that I can share you the standard template or format for those language module for integration in this module. **FURTHER INFO REGARDING THIS WILL BE PROVIDED SEPERATELY** 
- Note: If multi-language support occurred, the function name might need to be renamed from 'utf8_compare_tamil' to 'utf8_compare' or else a seperate function for 'utf8_compare' can be declared and defined. 

# Future works 
- A functionality to check if the string contains only a single language codepoints or contains multi-language codepoints. 
- If it contains only single languae indicate which Language is that. 

# About this project 
This project is created to process TAMIL strings in UTF-8 format. There was a need to properly search and sort TAMIL strings based on the lexicographic order. The compare function named 'utf8_compare_tamil()' is much suitable for these operations. If any more functionalities are needed, it will be added. 

Feedbacks and suggestions are welcome. You can also report bugs in your convenient way. 

> Email: deepdeepdeepak@outlook.com 

# License 
[GNU GENERAL PUBLIC LICENSE](LICENSE), Version 3, 29 June 2007 
