/***************************************************************** 

    File: lab9.c

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
#include <string.h>
#include <ctype.h>
#include "lab9.h"

#define MONTHS_IN_YEAR 12

static const char* const MONTH_FULL[MONTHS_IN_YEAR] = {
	"January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"
};

static const char* const MONTH_ABBREV[MONTHS_IN_YEAR] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

static void copyMonth(char dest[], const char* src)
{
	if (dest == NULL) {
		return;
	}

	if (src == NULL) {
		dest[0] = '\0';
		return;
	}

	strncpy(dest, src, STRINGMAX);
	dest[STRINGMAX] = '\0';
}

static int findMonthIndexByNumber(int number)
{
	if (number < 1 || number > MONTHS_IN_YEAR) {
		return -1;
	}
	return number - 1;
}

static int equalsIgnoreCaseN(const char* a, const char* b, size_t n)
{
	size_t i;

	if (a == NULL || b == NULL) {
		return 0;
	}

	for (i = 0; i < n; ++i) {
		unsigned char ca = (unsigned char)a[i];
		unsigned char cb = (unsigned char)b[i];

		if (ca == '\0' || cb == '\0') {
			return ca == cb;
		}

		if (tolower(ca) != tolower(cb)) {
			return 0;
		}
	}

	return 1;
}

static int findMonthIndexByAbbrev(const char* abbr)
{
	size_t i;

	if (abbr == NULL) {
		return -1;
	}

	for (i = 0; i < MONTHS_IN_YEAR; ++i) {
		if (equalsIgnoreCaseN(abbr, MONTH_ABBREV[i], 3)) {
			return (int)i;
		}
	}

	return -1;
}

static char* trim(char* str)
{
	char* end;

	if (str == NULL) {
		return NULL;
	}

	while (*str && isspace((unsigned char)*str)) {
		++str;
	}

	if (*str == '\0') {
		return str;
	}

	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end)) {
		*end-- = '\0';
	}

	return str;
}

static int stringsEqualIgnoreCase(const char* a, const char* b)
{
	if (a == NULL || b == NULL) {
		return 0;
	}

	while (*a && *b) {
		if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
			return 0;
		}
		++a;
		++b;
	}

	return *a == '\0' && *b == '\0';
}

int readDataFile1(const char* name, struct DateTime records[], int maxCapacity)
{
	FILE* file;
	int count = 0;

	if (name == NULL || records == NULL || maxCapacity <= 0) {
		return 0;
	}

	file = fopen(name, "r");
	if (file == NULL) {
		return 0;
	}

	while (count < maxCapacity) {
		int day, monthNum, year, hour, minute;
		int readValues = fscanf(file, "%d,%d,%d,%d,%d",
			&day, &monthNum, &year, &hour, &minute);
		int monthIndex;
		struct DateTime* current;

		if (readValues != 5) {
			break;
		}

		monthIndex = findMonthIndexByNumber(monthNum);
		if (monthIndex < 0) {
			continue;
		}

		current = &records[count];
		current->day = day;
		copyMonth(current->month, MONTH_FULL[monthIndex]);
		current->year = year;
		current->hour = hour;
		current->minute = minute;

		++count;
	}

	fclose(file);
	return count;
}

int readDataFile2(const char* name, struct DateTime records[], int maxCapacity)
{
	FILE* file;
	int count = 0;
	char line[128];

	if (name == NULL || records == NULL || maxCapacity <= 0) {
		return 0;
	}

	file = fopen(name, "r");
	if (file == NULL) {
		return 0;
	}

	while (count < maxCapacity && fgets(line, sizeof line, file) != NULL) {
		char* separator = strchr(line, ';');
		char* timePart;
		char* datePart;
		int hour12, minute, day, year;
		char period[3];
		char monthAbbrev[4];
		int monthIndex;
		struct DateTime* current;
		int hour24;

		if (separator == NULL) {
			continue;
		}

		*separator = '\0';
		timePart = trim(line);
		datePart = trim(separator + 1);

		if (sscanf(timePart, "%d:%d %2s", &hour12, &minute, period) != 3) {
			continue;
		}

		if (sscanf(datePart, "%d-%3s-%d", &day, monthAbbrev, &year) != 3) {
			continue;
		}

		monthIndex = findMonthIndexByAbbrev(monthAbbrev);
		if (monthIndex < 0) {
			continue;
		}

		period[0] = (char)tolower((unsigned char)period[0]);
		period[1] = (char)tolower((unsigned char)period[1]);
		hour12 %= 12;
		hour24 = hour12;
		if (period[0] == 'p') {
			hour24 += 12;
		}

		current = &records[count];
		current->day = day;
		copyMonth(current->month, MONTH_FULL[monthIndex]);
		current->year = year;
		current->hour = hour24;
		current->minute = minute;

		++count;
	}

	fclose(file);
	return count;
}

int numMonths(const char monthName[], const struct DateTime dates[], int size)
{
	int count = 0;
	int i;

	if (monthName == NULL || dates == NULL || size <= 0) {
		return 0;
	}

	for (i = 0; i < size; ++i) {
		if (stringsEqualIgnoreCase(monthName, dates[i].month)) {
			++count;
		}
	}

	return count;
}

