/***************************************************************** 

    File: lab9main.c

    Author: [Arman  Ataeipour]
    Seneca email: [ataeipour1@myseneca.ca]

    To compile program in codespaces, in terminal pane type:
        gcc -Wall lab9.c lab9main.c
    To run program in codespaces, in terminal pane type:
        ./a.out
        
***************************************************************/
//Uncomment the next line if you are using Visual Studio
//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "lab9.h"

int main(void)
{
	struct DateTime format1Records[32];
	struct DateTime format2Records[32];
	int count1 = readDataFile1("lab9format1.txt", format1Records, 32);
	int count2 = readDataFile2("lab9format2.txt", format2Records, 32);
	char monthQuery[STRINGMAX + 1];
	int monthMatches;
	int i;

	printf("Format one records: %d\n", count1);
	for (i = 0; i < count1; ++i) {
		printf("%02d %s %04d @ %02d:%02d\n",
			format1Records[i].day,
			format1Records[i].month,
			format1Records[i].year,
			format1Records[i].hour,
			format1Records[i].minute);
	}

	printf("\nFormat two records: %d\n", count2);
	for (i = 0; i < count2; ++i) {
		printf("%02d %s %04d @ %02d:%02d\n",
			format2Records[i].day,
			format2Records[i].month,
			format2Records[i].year,
			format2Records[i].hour,
			format2Records[i].minute);
	}

	printf("\nEnter full month name to count (e.g., November): ");
	if (scanf("%10s", monthQuery) != 1) {
		printf("No month entered. Exiting.\n");
		return 1;
	}

	monthMatches = numMonths(monthQuery, format2Records, count2);
	printf("Number of dates in %s: %d\n", monthQuery, monthMatches);

	return 0;
}