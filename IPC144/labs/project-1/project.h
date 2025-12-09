/***************************************************************** 

    File: project.h

    Author: [Arman Ataeipour]
    Seneca email: [aataeipour1@myseneca.ca]

    To compile program in codespaces, in terminal pane type:
        gcc -Wall project.c projectmain.c
    To run program in codespaces, in terminal pane type:
        ./a.out

    Notes / Citations:
      Engine ASCII art adapted from examples at:
      https://www.asciiart.eu/vehicles/trains
      All other code and design are original unless otherwise noted.
***************************************************************/
#ifndef PROJECT_H
#define PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

/* You can adjust these as you like */
#define MAX_CARS        1000
#define NUM_TRAIN_ROWS  4

/* Input (instructor expects number, then direction) */
int  read_int_in_range(const char *prompt, int min, int max);
char read_direction_lr(const char *prompt);

/* Drawing */
void draw_train(int num_cars, char direction);

#endif /* PROJECT_H */
