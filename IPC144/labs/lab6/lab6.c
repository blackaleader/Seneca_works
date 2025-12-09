/***************************************************************** 

    File: lab6.c

    Author: [Arman Ataeipour]
    Seneca email: [aataeipour1@myseneca.ca]

    To compile program in codespaces, in terminal pane type:
        gcc -Wall lab6.c lab6main.c
    To run program in codespaces, in terminal pane type:
        ./a.out
        
***************************************************************/
//Uncomment the next line if you are using Visual Studio
//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "lab6.h"

/* Function 1: Make change in Canadian coins (quarters, dimes, nickels) */
void makeChange(int cents, int* quarters, int* dimes, int* nickels)
{
	int remainder;

	if (quarters)
		*quarters = 0;
	if (dimes)
		*dimes = 0;
	if (nickels)
		*nickels = 0;

	/* Round to nearest nickel based on last digit */
	remainder = cents % 5;
	if (remainder == 1 || remainder == 2)
		cents -= remainder;
	else if (remainder == 3 || remainder == 4)
		cents += (5 - remainder);

	if (quarters)
	{
		*quarters = cents / 25;
		cents %= 25;
	}
	if (dimes)
	{
		*dimes = cents / 10;
		cents %= 10;
	}
	if (nickels)
	{
		*nickels = cents / 5;
	}
}

/* Function 2: Parse a date string in the form dd/mm/yyyy into DateTime */
void setDate(const char dateString[], struct DateTime* dt)
{
	int day = 0, month = 0, year = 0;
	if (dateString && dt)
	{
		/* Assumes format dd/mm/yyyy */
		if (sscanf(dateString, "%d/%d/%d", &day, &month, &year) == 3)
		{
			dt->day = day;
			dt->month = month;
			dt->year = year;
		}
	}
}

/* Function 3: Print the DateTime as "Month day, year h:mm am/pm" */
void printDateTime(const struct DateTime* dt)
{
	static const char* MONTHS[12] = {
		"January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December"
	};
	int hour12;
	const char* meridiem = "am";

	if (!dt)
		return;

	/* Print date: Month day, year */
	if (dt->month >= 1 && dt->month <= 12)

		printf("%s %d, %d ", MONTHS[dt->month - 1], dt->day, dt->year);
	else
		printf("%d/%d/%d ", dt->month, dt->day, dt->year);

	/* Convert to 12-hour time and determine am/pm */
	if (dt->hour == 0)
	{
		hour12 = 12;
		meridiem = "am";
	}
	else if (dt->hour < 12)
	{
		hour12 = dt->hour;
		meridiem = "am";
	}
	else if (dt->hour == 12)
	{
		hour12 = 12;
		meridiem = "pm";
	}
	else
	{
		hour12 = dt->hour - 12;
		meridiem = "pm";
	}

	/* Print time: h:mm am/pm */
	printf("%d:%02d %s\n", hour12, dt->minute, meridiem);
}