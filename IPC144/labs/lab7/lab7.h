/***************************************************************** 

    File: lab7.h

    Author: Arman Ataeipour

    Seneca email: aataeipour1@myseneca.ca

	The function prototypes for every function you write go
	into the header file.  You do not need to modify this file
        
***************************************************************/

/*this struct is used by all functions in lab 7.  We typically declare structs in 
.h files so that it can be included in all files that need to use the struct*/

struct Date
{
    int day;
    int month;
    int year;
};

int findDate(int day, int month, int year, struct Date dates[], int size);
int numInYear(int year, struct Date dates[], int size);
int cmpDates(int dayIndex1, int dayIndex2, struct Date dates[]);
int printDates(struct Date dates[], int size);

