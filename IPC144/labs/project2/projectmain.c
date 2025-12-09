/***************************************************************** 

    File: projectmain.c

    Author: [Arman Ataei-Pour]
    Seneca email: [aataeipour1@myseneca.ca]

    To compile program in codespaces, in terminal pane type:
        gcc -Wall project.c projectmain.c
    To run program in codespaces, in terminal pane type:
        ./a.out
        
***************************************************************/
//your main for the project goes into this file
//Uncomment the next line if you are using Visual Studio
//#define _CRT_SECURE_NO_WARNINGS

#include "project.h"

int main(void) {
    static BabyDatabase database;
    int choice = 0;
    int running = 1;
    
    database.count = 0;
    
    printf("Loading data...\n");
    
    if (readDataFile("femalebabynames.csv", &database, 'F') == 0) {
        printf("Error reading femalebabynames.csv\n");
        return 1;
    }
    
    if (readDataFile("malebabynames.csv", &database, 'M') == 0) {
        printf("Error reading malebabynames.csv\n");
        return 1;
    }
    
    printf("Data loaded successfully. Total records: %d\n", database.count);
    
    while (running == 1) {
        displayMenu();
        choice = getMenuChoice();
        
        if (choice == 1) {
            char name[MAX_NAME_LEN];
            getName(name);
            findBabiesByName(&database, name);
            
        } else if (choice == 2) {
            int year = getYear();
            findTop5Names(&database, year);
            
        } else if (choice == 3) {

            char name[MAX_NAME_LEN];
            getName(name);
            drawHistogram(&database, name);
            
        } else if (choice == 4) {

            running = 0;
        }
    }
    

    printf("\nFinished, writing data to combined.txt\n");
    
    if (writeCombinedFile(&database) == 0) {
        printf("Error writing combined.txt\n");
        return 1;
    }
    
    return 0;
}