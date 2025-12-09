/***************************************************************** 

    File: lab8main.c

    Author: [Arman Ataei-Pour]
    Seneca email: [aataeipour1@myseneca.ca]

    To compile program in codespaces, in terminal pane type:
        gcc -Wall lab8.c lab8main.c
    To run program in codespaces, in terminal pane type:
        ./a.out
        
***************************************************************/
//Uncomment the next line if you are using Visual Studio
//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "lab8.h"

int main(void)
{
	const char numericFile[] = "lab8format1.txt";
	const char stringFile[] = "lab8format2.txt";
	const char numericOutputFile[] = "numeric_output.txt";
	const char stringOutputFile[] = "string_output.txt";

	struct DateTime numericRecords[64];
	struct DateTime stringRecords[64];
	int numericCount = 0;
	int stringCount = 0;
	int i = 0;

	numericCount = readNumericDataFile(numericFile, numericRecords, 64);
	printf("Numeric file: %d records loaded from %s\n", numericCount, numericFile);

	stringCount = readStringDataFile(stringFile, stringRecords, 64);
	printf("String file: %d records loaded from %s\n", stringCount, stringFile);

	if (numericCount > 0)
	{
		printToFile(numericOutputFile, numericRecords, numericCount);
		printf("Numeric data written to %s\n", numericOutputFile);
	}

	if (stringCount > 0)
	{
		printToFile(stringOutputFile, stringRecords, stringCount);
		printf("String data written to %s\n", stringOutputFile);
	}

	printf("\nPreview of first five numeric records:\n");
	for (i = 0; i < numericCount && i < 5; i++)
	{
		printf("%d/%d/%d %02d:%02d\n",
			numericRecords[i].day,
			numericRecords[i].month,
			numericRecords[i].year,
			numericRecords[i].hour,
			numericRecords[i].minute);
	}

	printf("\nPreview of first five string records:\n");
	for (i = 0; i < stringCount && i < 5; i++)
	{
		printf("%d/%d/%d %02d:%02d\n",
			stringRecords[i].day,
			stringRecords[i].month,
			stringRecords[i].year,
			stringRecords[i].hour,
			stringRecords[i].minute);
	}

	return 0;
}