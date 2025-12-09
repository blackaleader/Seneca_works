/***************************************************************** 

    File: project.c

    Author: [Arman Ataeipour]
    Seneca email: [aataeipour1@myseneca.ca]

    To compile program in codespaces, in terminal pane type:
        gcc -Wall project.c projectmain.c
    To run program in codespaces, in terminal pane type:
        ./a.out

    Notes / Citations:
      - Engine ASCII art is adapted from examples at:
        https://www.asciiart.eu/vehicles/trains
        (Used as inspiration and mirrored/edited for left/right variants.)
      - Car design, couplers, and window randomization
        are authored by the student unless otherwise noted.

***************************************************************/
//Uncomment the next line if you are using Visual Studio
//#define _CRT_SECURE_NO_WARNINGS

#include "project.h"

/* -------------------- Utilities -------------------- */
/* Seed RNG once per run */
static void seed_rng_once(void) {
    static int seeded = 0;
    if (!seeded) {
        srand((unsigned)time(NULL));
        seeded = 1;
    }
}

/* Flush the rest of the current input line (safe after scanf) */
static void flush_line(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { /* discard */ }
}

/* -------------------- Input -------------------- */

/**
 * Reads an integer in [min, max].
 * No 'continue;' used; single return at end.
 */
int read_int_in_range(const char *prompt, int min, int max) {
    seed_rng_once();

    int value = min - 1;
    int ok = 0;

    while (!ok) {
        printf("%s", prompt);

        if (scanf("%d", &value) != 1) {
            printf("Invalid input. Please enter an integer.\n");
            flush_line();
        } else if (value < min || value > max) {
            printf("Value must be between %d and %d inclusive.\n", min, max);
            flush_line();
        } else {
            ok = 1;
            flush_line();
        }
    }

    return value;
}

/**
 * Reads a single char direction 'L' or 'R' (case-insensitive).
 * No 'continue;' used; single return at end.
 */
char read_direction_lr(const char *prompt) {
    char temp_dir = '\0';
    int ok = 0;

    while (!ok) {
        printf("%s", prompt);

        if (scanf(" %c", &temp_dir) != 1) {
            flush_line();
        } else {
            temp_dir = (char)toupper((unsigned char)temp_dir);
            if (temp_dir == 'L' || temp_dir == 'R') {
                ok = 1;
            } else {
                printf("Direction must be 'L' or 'R'.\n");
            }
            flush_line();
        }
    }

    return temp_dir;
}

/* -------------------- ASCII Engine -------------------- */
/* Your engine art, mirrored for R vs L (UNCHANGED) */

static void print_engine_part(int row, char direction) {
    if (direction == 'R') {
        /* Mirrored (left->right) version you provided */
        switch (row) {
            case 0: printf("    o O ____");     break;
            case 1: printf("  _T____|DD|");     break;
            case 2: printf(" >|_____| _|");     break;
            case 3: printf(" /oo-@-@-@  ");     break;
        }
    } else { /* direction == 'L' */
        /* Original right-facing set (used when moving left) */
        switch (row) {
            case 0: printf("____ O o");        break;
            case 1: printf("|DD|____T_");       break;
            case 2: printf("|_ |_____|<");      break;
            case 3: printf(" @-@-@-oo\\");      break; /* backslash escaped */
        }
    }
}

/* -------------------- ASCII Cars -------------------- */
/* Print one car segment for the given row, using window counts from array. */
static void print_car_part(int row, int car_index, const int windows[]) {
    int num_windows = (car_index >= 0 && car_index < MAX_CARS) ? windows[car_index] : 0;

    switch (row) {
        case 0:
            /* Roof (width 8) */
            printf("________");
            break;

        case 1: {
            /* Body with windows: '|' + 6 interior + '|' = width 8 */
            char buf[7];
            int i;
            for (i = 0; i < 6; ++i) buf[i] = ' ';
            buf[6] = '\0';

            /* Up to 4 windows, spaced at columns 0,1,4,5 */
            if (num_windows >= 1) buf[0] = 'o';
            if (num_windows >= 2) buf[1] = 'o';
            if (num_windows >= 3) buf[4] = 'o';
            if (num_windows >= 4) buf[5] = 'o';

            printf("|%s|", buf);
            break;
        }

        case 2:
            /* Base line (width 8) */
            printf("|______|");
            break;

        case 3:
            /* Wheels line (width 8) — added wheels */
            printf("  O  O  ");
            break;
    }
}

/* -------------------- Couplers -------------------- */
/* Print coupler only on the body row (row 1), spaces otherwise to keep alignment */
static void print_coupler(int row) {
    if (row == 1) {
        printf("-*-");
    } else {
        printf("   ");
    }
}

/* -------------------- Row Coordinators -------------------- */
/* Engine and cars appear in correct order; couplers only BETWEEN units */

static void print_row_r(int row, int num_cars, const int windows[]) {
    /* Engine first */
    print_engine_part(row, 'R');

    /* Then: (coupler + car0) (coupler + car1) ... */
    int i;
    for (i = 0; i < num_cars; ++i) {
        print_coupler(row);
        print_car_part(row, i, windows);
    }
    printf("\n");
}

static void print_row_l(int row, int num_cars, const int windows[]) {
    /* Cars first (reverse index so car0 is nearest the engine visually) */
    int i;
    for (i = num_cars - 1; i >= 0; --i) {
        print_car_part(row, i, windows);
        if (i > 0) {
            print_coupler(row);  /* between cars only */
        }
    }
    if (num_cars > 0) {
        print_coupler(row);      /* between last car and engine */
    }
    /* Engine last */
    print_engine_part(row, 'L');
    printf("\n");
}

/* -------------------- Public Draw -------------------- */
/* No globals: window counts are local and passed down. */
void draw_train(int num_cars, char direction) {
    int car_windows[MAX_CARS];
    int i;

    seed_rng_once();

    /* Generate random window counts 0..4 for the chosen number of cars */
    for (i = 0; i < num_cars && i < MAX_CARS; ++i) {
        car_windows[i] = rand() % 5;
    }

    /* Render the 4 rows */
    for (i = 0; i < NUM_TRAIN_ROWS; ++i) {
        if (direction == 'R') {
            print_row_r(i, num_cars, car_windows);
        } else {
            print_row_l(i, num_cars, car_windows);
        }
    }
}
