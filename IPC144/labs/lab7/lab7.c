/***************************************************************** 

    File: lab7.c

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

int findDate(int day, int month, int year, struct Date dates[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (dates[i].day == day && dates[i].month == month && dates[i].year == year)
        {
            return i;
        }
    }
    return -1;
}

int numInYear(int year, struct Date dates[], int size)
{
    int count = 0;
    int i;
    for (i = 0; i < size; i++)
    {
        if (dates[i].year == year)
        {
            count++;
        }
    }
    return count;
}

int cmpDates(int dayIndex1, int dayIndex2, struct Date dates[])
{
    if (dates[dayIndex1].year < dates[dayIndex2].year)
    {
        return 1;
    }
    else if (dates[dayIndex1].year > dates[dayIndex2].year)
    {
        return -1;
    }
    
    if (dates[dayIndex1].month < dates[dayIndex2].month)
    {
        return 1;
    }
    else if (dates[dayIndex1].month > dates[dayIndex2].month)
    {
        return -1;
    }
    
    if (dates[dayIndex1].day < dates[dayIndex2].day)
    {
        return 1;
    }
    else if (dates[dayIndex1].day > dates[dayIndex2].day)
    {
        return -1;
    }
    
    return 0;
}

int printDates(struct Date dates[], int size)
{
    const char* monthNames[] = {
        "", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    
    int i;
    for (i = 0; i < size; i++)
    {
        if (dates[i].month >= 1 && dates[i].month <= 12)
        {
            printf("%s %d, %d\n", monthNames[dates[i].month], dates[i].day, dates[i].year);
        }
    }
    
    return 0;
}

