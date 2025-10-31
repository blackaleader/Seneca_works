/***************************************************************** 

    File: lab5.c

    Author: Arman Ataeiipour
    Seneca email: aataeipour1@myseneca.ca

    To compile program in codespaces, in terminal pane type:
        gcc -Wall lab5.c lab5main.c
    To run program in codespaces, in terminal pane type:
        ./a.out
        
***************************************************************/
//Uncomment the next line if you are using Visual Studio
//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>

/*
This function is passed an array and the size of the array. The
function returns the sum of the values from the array
*/
int sum(const int array[], int size);


/*
This function is passed an array of integers and its size. 
Function will reverse the array
*/
void reverse(int array[], int size);

/*
This function returns the number of times ch shows up in str
*/
int countChar(char ch,const char str[]);

/*
This function returns the number of times ch shows up. If ch
is an alphabetic character, count both the upper and lower case 
versions of this character
*/
int countAllCase(char ch,const char str[]);

void printIntArray(const int array[], int size) {
    printf("[");
    for (int i = 0; i < size; ++i) {
        if (i > 0) printf(", ");
        printf("%d", array[i]);
    }
    printf("]\n");
}

// LAB 5 function implementations

int sum(const int array[], int size) {
    int total = 0;
    for (int i = 0; i < size; ++i) {
        total += array[i];
    }
    return total;
}

void reverse(int array[], int size) {
    for (int i = 0; i < size / 2; ++i) {
        int temp = array[i];
        array[i] = array[size - 1 - i];
        array[size - 1 - i] = temp;
    }
}

int countChar(char ch, const char str[]) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == ch) {
            ++count;
        }
    }
    return count;
}

int countAllCase(char ch, const char str[]) {
    int count = 0;
    char ch_lower = tolower((unsigned char)ch);
    char ch_upper = toupper((unsigned char)ch);
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == ch_lower || str[i] == ch_upper) {
            ++count;
        }
    }
    return count;
}


