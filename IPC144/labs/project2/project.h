/***************************************************************** 

    File: project.h

    Author: [Arman Ataei-Pour]
    Seneca email: [aataeipour1@myseneca.ca]

    To compile program in codespaces, in terminal pane type:
        gcc -Wall project.c projectmain.c
    To run program in codespaces, in terminal pane type:
        ./a.out
        
***************************************************************/
#ifndef PROJECT_H
#define PROJECT_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* Constants */
#define MAX_RECORDS 200000
#define MAX_NAME_LEN 100
#define MIN_YEAR 1914
#define MAX_YEAR 2023
#define COHORT_SIZE 5
#define HISTOGRAM_MAX_WIDTH 80


typedef struct {
    int year;
    char name[MAX_NAME_LEN];
    int frequency;
    char gender; 
} BabyRecord;


typedef struct {
    BabyRecord records[MAX_RECORDS];
    int count;
} BabyDatabase;



int readDataFile(const char* filename, BabyDatabase* db, char gender);


void toLowerCase(char* dest, const char* src);


int compareNames(const char* name1, const char* name2);


int validateName(const char* name);


void displayMenu(void);


int getMenuChoice(void);


int getYear(void);


void getName(char* name);


void findBabiesByName(const BabyDatabase* db, const char* name);


void findTop5Names(const BabyDatabase* db, int year);


void drawHistogram(const BabyDatabase* db, const char* name);


int writeCombinedFile(const BabyDatabase* db);

#endif