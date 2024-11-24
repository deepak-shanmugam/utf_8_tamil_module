# utf_8_tamil_module
C library to primarily handle the tamil unicode letters in utf-8 format. 

# Supported Platform 
> Linux, Windows, MAC 

# Run or Test 
```
gcc -o test client.c utf_tamil.c 
```

# Supported Functionality 
- To get the no of codepoints present in a string: int get_utf8_cp_count(const char *string); 
- To get the UTF8 information (UTF8_Type and UTF8_Lang) of the first codepoint in a string: int get_utf8_info(const char *string); 
- To compare the UTF-8 string for searching, sorting based on the lexicographic order: int utf8_compare_tamil(const char *first, const char *second); 
- Note: The above compare function works best for TAMIL and ENGLISH based on Lexicographic order. 

# Points to be noted for UTF-8 string comparison  
- **utf8_compare_tamil()** - this function works best for TAMIL and ENGLISH as lexicographic order is maintained for those 2 languages in this current module. 
- The function gives proper result for those languages even if a single string contains codepoints of any type and language. 
- The proper Lexicographic order for remaining languages are not maintained. So, it follows the default order of codepoints of those languages. 
- Yet this function is scalable that we can integrate the proper compare function for other languages also. So that a proper lexicographic order can be achievable for multi-languages here. 
- If you want to add those support for other language, kindly let me know. so that I will tell you the template for those language module to be integrated here. It will be very simple only. **FURTHER UPDATES WILL BE PROVIDED REGARDING THIS** 
- Note: If multi-language support occurred, the function name needs to be renamed from 'utf8_compare_tamil' to 'utf8_compare' or a seperate function for 'utf8_compare' can be declared. 

# Future works 
- A functionality to check if the string contains only a single language codepoints or contains multi-language codepoints. 
- If it contains only single languae indicate which Language is that. 

# About this project 
This project is created to process TAMIL strings in UTF-8 format. There was a need to properly search and sort TAMIL strings based on the lexicographic order. The created compare function named 'utf8_compare_tamil()' works fantastic for these operations. If any more functionality needed, it will be added. 

Feedbacks and suggestions are welcome. You can also report bugs in your convenient way. 

> Email: deepdeepdeepak@outlook.com 

# License 
[GNU GENERAL PUBLIC LICENSE](LICENSE), Version 3, 29 June 2007 
