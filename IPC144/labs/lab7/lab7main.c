/***************************************************************** 

    File: lab7main.c

    Author: Arman Ataeipour

    Seneca email: aataeipour1@myseneca.ca

    To compile program in codespaces, in terminal pane type:
        gcc -Wall lab7.c lab7main.c
    To run program in codespaces, in terminal pane type:
        ./a.out
        
***************************************************************/
//Uncomment the next line if you are using Visual Studio
//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "lab7.h"

int main(void)
{
    struct Date dates[3] = {{1, 1, 2024}, {2, 9, 2023}, {24, 11, 2024}};
    int size = 3;
    int result;
    
    printf("=== Testing printDates function ===\n");
    printDates(dates, size);
    printf("\n");
    
    printf("=== Testing findDate function ===\n");
    result = findDate(1, 1, 2024, dates, size);
    printf("findDate(1, 1, 2024): index = %d (expected: 0)\n", result);
    
    result = findDate(2, 9, 2023, dates, size);
    printf("findDate(2, 9, 2023): index = %d (expected: 1)\n", result);
    
    result = findDate(25, 12, 2024, dates, size);
    printf("findDate(25, 12, 2024): index = %d (expected: -1)\n", result);
    printf("\n");
    
    printf("=== Testing numInYear function ===\n");
    result = numInYear(2024, dates, size);
    printf("numInYear(2024): %d (expected: 2)\n", result);
    
    result = numInYear(2023, dates, size);
    printf("numInYear(2023): %d (expected: 1)\n", result);
    
    result = numInYear(2025, dates, size);
    printf("numInYear(2025): %d (expected: 0)\n", result);
    printf("\n");
    
    printf("=== Testing cmpDates function ===\n");
    result = cmpDates(0, 0, dates);
    printf("cmpDates(0, 0): %d (expected: 0)\n", result);
    
    result = cmpDates(1, 0, dates);
    printf("cmpDates(1, 0): %d (expected: 1, since 2023 < 2024)\n", result);
    
    result = cmpDates(0, 1, dates);
    printf("cmpDates(0, 1): %d (expected: -1, since 2024 > 2023)\n", result);
    
    result = cmpDates(0, 2, dates);
    printf("cmpDates(0, 2): %d (expected: 1, since Jan < Nov)\n", result);
    
    result = cmpDates(2, 0, dates);
    printf("cmpDates(2, 0): %d (expected: -1, since Nov > Jan)\n", result);
    
    return 0;
}