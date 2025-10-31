/***************************************************************** 

    File: lab5practice.h

    Author: [Your Name]
    Seneca email: [Your Seneca email address]

	The function prototypes for every function you write go
	into the header file. You do not need to modify this file
        
***************************************************************/

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
