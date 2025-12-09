/***************************************************************** 

    File: projectmain.c

    Author: [Arman Ataeipour]
    Seneca email: [aataeipour1@myseneca.ca]

    To compile program in codespaces, in terminal pane type:
        gcc -Wall project.c projectmain.c
    To run program in codespaces, in terminal pane type:
        ./a.out

    Notes:
      Reads inputs in exact order (cars then direction) and draws the train.

***************************************************************/
//your main for the project goes into this file
//Uncomment the next line if you are using Visual Studio
//#define _CRT_SECURE_NO_WARNING

#include "project.h"

int main(void) {
    /* Read EXACT order: number of cars, then direction */
    int  num_cars  = read_int_in_range("Enter number of train cars (0-5): ", 0, 5);
    char direction = read_direction_lr("Enter direction (L/R): ");

    draw_train(num_cars, direction);
    return 0;
}
