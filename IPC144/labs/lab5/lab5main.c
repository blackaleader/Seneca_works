/***************************************************************** 

    File: lab5main.c

    Author: [Your Name]
    Seneca email: [Your Seneca email address]    

    To compile program in codespaces, in terminal pane type:
        gcc -Wall lab5.c lab5main.c
    To run program in codespaces, in terminal pane type:
        ./a.out
        
***************************************************************/
//Uncomment the next line if you are using Visual Studio
//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
int sum(const int array[], int size);
void reverse(int array[], int size);
int countChar(char ch,const char str[]);
int countAllCase(char ch,const char str[]);
void printIntArray(const int array[], int size);
#define CAP 20

int main(void)
{
    int array[CAP] = {1, 5, 4, 3, 2};
    int array2[6] = {2, 1, 3, 4, 7, 6};
    char mystring[100] = "the quick brown Fox jumped\tOver r2d2 but c 3po was\n Too tall";

    printf("Original array: ");
    printIntArray(array, 5);
    int result = sum(array, 5);
    printf("Sum of original array: %d\n", result);

    printf("Original array2: ");
    printIntArray(array2, 6);
    reverse(array2, 6);
    printf("Reversed array2: ");
    printIntArray(array2, 6);

    int numTs = countChar('t', mystring);
    printf("Number of 't' chars in mystring: %d\n", numTs);
    int numOs = countAllCase('o', mystring);
    printf("Number of 'o' or 'O' chars in mystring: %d\n", numOs);

    // Additional Tests (Lab Sheet)
    // ==========================
    printf("\n============================\n");
    printf("Additional Tests (Lab Sheet)\n");
    printf("============================\n\n");

    // sum tests
    printf("-- sum tests --\n");
    int s1_arr[] = {1, 5, 4, 3, 2};
    printf("Input: "); printIntArray(s1_arr, 5);
    printf("Expected: 15, Got: %d\n\n", sum(s1_arr, 5));

    int s2_arr[] = {0, 0, 0};
    printf("Input: "); printIntArray(s2_arr, 3);
    printf("Expected: 0, Got: %d\n\n", sum(s2_arr, 3));

    int s3_arr[] = {-4, -6, 10, 2};
    printf("Input: "); printIntArray(s3_arr, 4);
    printf("Expected: 2, Got: %d\n\n", sum(s3_arr, 4));

    // reverse tests
    printf("-- reverse tests --\n");
    int r1_arr[] = {2, 1, 3, 4, 7, 6};
    printf("Before: "); printIntArray(r1_arr, 6);
    reverse(r1_arr, 6);
    printf("After:  "); printIntArray(r1_arr, 6);
    printf("Expected: [6, 7, 4, 3, 1, 2]\n\n");

    int r2_arr[] = {9, 8, 7};
    printf("Before: "); printIntArray(r2_arr, 3);
    reverse(r2_arr, 3);
    printf("After:  "); printIntArray(r2_arr, 3);
    printf("Expected: [7, 8, 9]\n\n");

    int r3_arr[] = {5};
    printf("Before: "); printIntArray(r3_arr, 1);
    reverse(r3_arr, 1);
    printf("After:  "); printIntArray(r3_arr, 1);
    printf("Expected: [5]\n\n");

    // countChar tests
    printf("-- countChar tests --\n");
    char str1[] = "the tall tree";
    printf("Input: '%s' | ch='t'\n", str1);
    printf("Expected: 3, Got: %d\n\n", countChar('t', str1));

    char str2[] = "example xXx";
    printf("Input: '%s' | ch='x'\n", str2);
    printf("Expected: 3, Got: %d\n\n", countChar('x', str2));

    char str3[] = " a b c ";
    printf("Input: '%s' | ch=' ' (space)\n", str3);
    printf("Expected: 4, Got: %d\n\n", countChar(' ', str3));

    // countAllCase tests
    printf("-- countAllCase tests --\n");
    char str4[] = "Ooo, look! Oops.";
    printf("Input: '%s' | ch='o' (case-insensitive)\n", str4);
    printf("Expected: 7, Got: %d\n\n", countAllCase('o', str4));

    char str5[] = "tTtT tttT";
    printf("Input: '%s' | ch='T' (case-insensitive)\n", str5);
    printf("Expected: 8, Got: %d\n\n", countAllCase('T', str5));

    char str6[] = "Chocolate Cake can't cook correctly";
    printf("Input: '%s' | ch='c' (case-insensitive)\n", str6);
    printf("Expected: 7, Got: %d\n\n", countAllCase('c', str6));


    return 0;
}