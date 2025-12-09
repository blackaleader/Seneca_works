/***************************************************************** 

    File: lab6.h

    Author: [Your Name]
    Seneca email: [Your Seneca email address]

	The function prototypes for every function you write go
	into the header file.  You do not need to modify this file
        
***************************************************************/

/*this struct is used by all functions in lab 6.  We typically declare structs in 
.h files so that it can be included in all files that need to use the struct*/

struct DateTime
{
	int day;
	int month;
	int year;
	int hour;
	int minute;
};

/* Add the function prototypes for the lab6 problems to this file.  
 below this comment  You can copy these from the lab specifications. */

/* Function 1: Make change in Canadian coins (quarters, dimes, nickels) */
void makeChange(int cents, int* quarters, int* dimes, int* nickels);

/* Function 2: Parse a date string in the form dd/mm/yyyy into DateTime */
void setDate(const char dateString[], struct DateTime* dt);

/* Function 3: Print the DateTime as "Month day, year h:mm am/pm" */
void printDateTime(const struct DateTime* dt);