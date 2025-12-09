/***************************************************************** 

    File: lab8.h

    Author: [Arman Ataei-Pour]
    Seneca email: [aataeipour1@myseneca.ca]

	The function prototypes for every function you write go
	into the header file.  You do not need to modify this file
        
***************************************************************/


struct DateTime
{
	int day;
	int month;
	int year;
	int hour;
	int minute;
};


int readNumericDataFile(const char* name, struct DateTime records[], int maxCapacity);
int readStringDataFile(const char* name, struct DateTime records[], int maxCapacity);
void printToFile(const char* filename, struct DateTime data[], int size);