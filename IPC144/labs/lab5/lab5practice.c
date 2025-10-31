/***************************************************************** 

    File: lab5practice.c

    Author: [Your Name]
    Seneca email: [Your Seneca email address]

    To compile program in codespaces, in terminal pane type:
        gcc -Wall lab5practice.c lab5main.c
    To run program in codespaces, in terminal pane type:
        ./a.out
        
***************************************************************/
//Uncomment the next line if you are using Visual Studio
//#define _CRT_SECURE_NO_WARNINGS

/*
This function returns the smallest value in an array
*/
int findSmallest(int array[], int size);

/*
This function returns the average of the values in the array
*/
double average(int array[],int size);
/*
This function is passed a key value as well as an array and the size of the array. 
The function returns the index where key was found within the array. If the key
does not exist within the array, function returns -1. If there are multiple 
values in the array that match the key, return the index of the first value 
that matches
*/
int linearSearch(int key, const int array[], int size);

/*
This function will capitalize the first character of every "word" in the sentence
if the word begins with an alphabetic character. Words are separated by 1 or more
whitespace character (spaces, tabs, newlines).
*/
void capitalize(char str[]);

/*
This function removes all trailing whitespaces (spaces, tabs and newlines) from str
*/
void removeTrailingWhitespace(char str[]);



