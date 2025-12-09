/***************************************************************** 

    File: lab6main.c

    Author: [Your Name]
    Seneca email: [Your Seneca email address]

    To compile program in codespaces, in terminal pane type:
        gcc -Wall lab6.c lab6main.c
    To run program in codespaces, in terminal pane type:
        ./a.out
        
***************************************************************/
//Uncomment the next line if you are using Visual Studio
//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "lab6.h"

int main(void)
{
	int q, d, n;
	struct DateTime dt;

	/* Test makeChange */
	makeChange(86, &q, &d, &n);
	printf("makeChange(86): q=%d d=%d n=%d\n", q, d, n); /* Expect 3,1,0 */

	makeChange(89, &q, &d, &n);
	printf("makeChange(89): q=%d d=%d n=%d\n", q, d, n); /* Expect 3,1,1 */

	/* Test setDate and printDateTime */
	setDate("08/11/2024", &dt); /* 8 November 2024 */

	/* Additional date/time tests */
	setDate("01/04/2024", &dt); dt.hour = 0; dt.minute = 0; printDateTime(&dt);
	setDate("31/12/1999", &dt); dt.hour = 12; dt.minute = 0; printDateTime(&dt);
	setDate("15/01/2025", &dt); dt.hour = 12; dt.minute = 1; printDateTime(&dt);

	/* Various time cases */
	dt.hour = 8; dt.minute = 14; /* 8:14 am */
	printDateTime(&dt);

	dt.hour = 23; dt.minute = 33; /* 11:33 pm */
	printDateTime(&dt);

	dt.hour = 0; dt.minute = 55; /* 12:55 am */
	printDateTime(&dt);

	dt.hour = 6; dt.minute = 15; /* 6:15 am */
	printDateTime(&dt);

	dt.hour = 14; dt.minute = 0; /* 2:00 pm */
	printDateTime(&dt);

	return 0;
}