/***************************************************************** 

    File: lab8.c

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

static void storeRecord(struct DateTime* target, int day, int month, int year, int hour, int minute)
{
	if (target != NULL)
	{
		target->day = day;
		target->month = month;
		target->year = year;
		target->hour = hour;
		target->minute = minute;
	}
}

int readNumericDataFile(const char* name, struct DateTime records[], int maxCapacity)
{
	FILE* fp = NULL;
	int count = 0;
	int day = 0;
	int month = 0;
	int year = 0;
	int hour = 0;
	int minute = 0;

	if (name == NULL || records == NULL || maxCapacity <= 0)
	{
		return 0;
	}

	fp = fopen(name, "r");

	if (fp == NULL)
	{
		return 0;
	}

	while (count < maxCapacity &&
		fscanf(fp, "%d,%d,%d,%d,%d", &day, &month, &year, &hour, &minute) == 5)
	{
		storeRecord(&records[count], day, month, year, hour, minute);
		count++;
	}

	fclose(fp);

	return count;
}

int readStringDataFile(const char* name, struct DateTime records[], int maxCapacity)
{
	FILE* fp = NULL;
	int count = 0;
	int day = 0;
	int month = 0;
	int year = 0;
	int hour = 0;
	int minute = 0;
	char period[3] = { 0 };

	if (name == NULL || records == NULL || maxCapacity <= 0)
	{
		return 0;
	}

	fp = fopen(name, "r");

	if (fp == NULL)
	{
		return 0;
	}

	while (count < maxCapacity &&
		fscanf(fp, "%d/%d/%d;%d:%d %2s", &day, &month, &year, &hour, &minute, period) == 6)
	{
		if (period[0] == 'p' || period[0] == 'P')
		{
			if (hour != 12)
			{
				hour += 12;
			}
		}
		else
		{
			if (hour == 12)
			{
				hour = 0;
			}
		}

		storeRecord(&records[count], day, month, year, hour, minute);
		count++;
	}

	fclose(fp);

	return count;
}

void printToFile(const char* filename, struct DateTime data[], int size)
{
	const char* monthNames[12] = {
		"January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December"
	};
	FILE* fp = NULL;
	int i = 0;

	if (filename == NULL || data == NULL || size <= 0)
	{
		return;
	}

	fp = fopen(filename, "w");

	if (fp == NULL)
	{
		return;
	}

	for (i = 0; i < size; i++)
	{
		const char* monthName = "Unknown";
		int displayHour = data[i].hour;
		const char* period = "am";

		if (data[i].month >= 1 && data[i].month <= 12)
		{
			monthName = monthNames[data[i].month - 1];
		}

		if (displayHour == 0)
		{
			displayHour = 12;
			period = "am";
		}
		else if (displayHour < 12)
		{
			period = "am";
		}
		else if (displayHour == 12)
		{
			period = "pm";
		}
		else
		{
			displayHour -= 12;
			period = "pm";
		}

		fprintf(fp, "%s %d, %d %d:%02d %s\n",
			monthName,
			data[i].day,
			data[i].year,
			displayHour,
			data[i].minute,
			period);
	}

	fclose(fp);
}
