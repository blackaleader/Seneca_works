/***************************************************************** 

    File: lab9.h

    Author: [Arman  Ataeipour]
    Seneca email: [ataeipour1@myseneca.ca]

	The function prototypes for every function you write go
	into the header file.  You do not need to modify this file
        
***************************************************************/



#define STRINGMAX 10
struct DateTime
{
	int day;
	char month[STRINGMAX+1];
	int year;
	int hour;
	int minute;
};


int readDataFile1(const char* name, struct DateTime records[], int maxCapacity);
int readDataFile2(const char* name, struct DateTime records[], int maxCapacity);
int numMonths(const char monthName[], const struct DateTime dates[], int size);