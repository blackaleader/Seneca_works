/***************************************************************** 

    File: project.c

    Author: [Arman ataei pour]
    Seneca email: [aataeipour1@myseneca.ca]

    To compile program in codespaces, in terminal pane type:
        gcc -Wall project.c projectmain.c
    To run program in codespaces, in terminal pane type:
        ./a.out
        
***************************************************************/
//Uncomment the next line if you are using Visual Studio
//#define _CRT_SECURE_NO_WARNINGS

#include "project.h"


int readDataFile(const char* filename, BabyDatabase* db, char gender) {
    FILE* file = fopen(filename, "r");
    char line[256];
    int result = 1;
    
    if (file == NULL) {
        result = 0;
    } else {
        /* Skip header line */
        if (fgets(line, sizeof(line), file) != NULL) {
            /* Read data lines */
            while (fgets(line, sizeof(line), file) != NULL && db->count < MAX_RECORDS) {
                int year = 0;
                char name[MAX_NAME_LEN];
                int frequency = 0;
                char* token = NULL;
                
                /* Parse year */
                token = strtok(line, ",");
                if (token != NULL) {
                    sscanf(token, "%d", &year);
                }
                
                /* Parse name */
                token = strtok(NULL, ",");
                if (token != NULL) {
                    strncpy(name, token, MAX_NAME_LEN - 1);
                    name[MAX_NAME_LEN - 1] = '\0';
                }
                
                /* Parse frequency */
                token = strtok(NULL, ",\n");
                if (token != NULL) {
                    sscanf(token, "%d", &frequency);
                }
                
                /* Store record */
                if (year > 0 && frequency > 0) {
                    db->records[db->count].year = year;
                    strncpy(db->records[db->count].name, name, MAX_NAME_LEN - 1);
                    db->records[db->count].name[MAX_NAME_LEN - 1] = '\0';
                    db->records[db->count].frequency = frequency;
                    db->records[db->count].gender = gender;
                    db->count++;
                }
            }
        }
        fclose(file);
    }
    
    return result;
}

/**
 * Converts a string to lowercase for case-insensitive comparison
 * Parameters: dest - destination buffer (must be large enough)
 *            src - source string
 */
void toLowerCase(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = tolower(src[i]);
        i++;
    }
    dest[i] = '\0';
}

/**
 * Compares two names in a case-insensitive manner
 * Parameters: name1 - first name
 *            name2 - second name
 * Returns: 1 if names match, 0 otherwise
 */
int compareNames(const char* name1, const char* name2) {
    char lower1[MAX_NAME_LEN];
    char lower2[MAX_NAME_LEN];
    int result = 0;
    
    toLowerCase(lower1, name1);
    toLowerCase(lower2, name2);
    
    if (strcmp(lower1, lower2) == 0) {
        result = 1;
    }
    
    return result;
}

/**
 * Validates if a name contains only valid characters (alphabetic, space, hyphen)
 * Parameters: name - the name to validate
 * Returns: 1 if valid, 0 otherwise
 */
int validateName(const char* name) {
    int i = 0;
    int result = 1;
    int hasAlpha = 0;
    
    if (name[0] == '\0') {
        result = 0;
    } else {
        while (name[i] != '\0' && result == 1) {
            if (isalpha(name[i])) {
                hasAlpha = 1;
            } else {
                if (name[i] != ' ' && name[i] != '-') {
                    result = 0;
                }
            }
            i++;
        }
        
        if (hasAlpha == 0) {
            result = 0;
        }
    }
    
    return result;
}

/**
 * Displays the main menu to the user
 */
void displayMenu(void) {
    printf("\n-----------------------------------------------------\n");
    printf("Baby Name Data Viewer\n");
    printf("1. number of babies\n");
    printf("2. top 5 names\n");
    printf("3. histogram\n");
    printf("4. exit\n");
}

/**
 * Gets and validates menu choice from user
 * Returns: validated menu choice (1-4)
 */
int getMenuChoice(void) {
    int choice = 0;
    int valid = 0;
    
    while (valid == 0) {
        printf("Enter your choice: ");
        if (scanf("%d", &choice) == 1) {
            /* Clear input buffer */
            while (getchar() != '\n');
            
            if (choice >= 1 && choice <= 4) {
                valid = 1;
            } else {
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
            }
        } else {
            /* Clear input buffer */
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number between 1 and 4.\n");
        }
    }
    
    return choice;
}

/**
 * Gets and validates a year from user
 * Returns: validated year (1914-2023)
 */
int getYear(void) {
    int year = 0;
    int valid = 0;
    
    printf("Enter the Year: ");
    
    while (valid == 0) {
        if (scanf("%d", &year) == 1) {
            /* Clear input buffer */
            while (getchar() != '\n');
            
            if (year >= MIN_YEAR && year <= MAX_YEAR) {
                valid = 1;
            } else {
                printf("Number entered was invalid. Number must be between %d to %d inclusive\n", 
                       MIN_YEAR, MAX_YEAR);
                printf("Please re-enter: ");
            }
        } else {
            /* Clear input buffer */
            while (getchar() != '\n');
            printf("Invalid input. Please enter a year between %d and %d.\n", 
                   MIN_YEAR, MAX_YEAR);
            printf("Please re-enter: ");
        }
    }
    
    return year;
}

/**
 * Gets a name from user and validates it
 * Parameters: name - buffer to store the name (must be MAX_NAME_LEN size)
 */
void getName(char* name) {
    int valid = 0;
    
    while (valid == 0) {
        printf("Enter the Name: ");
        if (fgets(name, MAX_NAME_LEN, stdin) != NULL) {
            /* Remove newline */
            int len = strlen(name);
            if (len > 0 && name[len-1] == '\n') {
                name[len-1] = '\0';
            }
            
            if (validateName(name)) {
                valid = 1;
            } else {
                printf("Invalid name. Name must contain only letters, spaces, or hyphens.\n");
            }
        }
    }
}

/**
 * Finds and displays number of babies born with a given name
 * Parameters: db - pointer to database
 *            name - the name to search for
 * Displays: yearly counts, female total, male total, overall total
 */
void findBabiesByName(const BabyDatabase* db, const char* name) {
    int yearCounts[MAX_YEAR - MIN_YEAR + 1];
    int femaleTotal = 0;
    int maleTotal = 0;
    int i = 0;
    int year = 0;
    
    /* Initialize year counts */
    for (i = 0; i < MAX_YEAR - MIN_YEAR + 1; i++) {
        yearCounts[i] = 0;
    }
    
    printf("\nResults for %s\n", name);
    
    /* Search through database */
    for (i = 0; i < db->count; i++) {
        if (compareNames(db->records[i].name, name)) {
            int yearIndex = db->records[i].year - MIN_YEAR;
            yearCounts[yearIndex] += db->records[i].frequency;
        }
    }
    
    /* Display yearly counts */
    for (year = MIN_YEAR; year <= MAX_YEAR; year++) {
        int yearIndex = year - MIN_YEAR;
        if (yearCounts[yearIndex] > 0) {
            printf("%d: %d\n", year, yearCounts[yearIndex]);
        }
    }
    
    /* Calculate totals by gender */
    for (i = 0; i < db->count; i++) {
        if (compareNames(db->records[i].name, name)) {
            if (db->records[i].gender == 'F') {
                femaleTotal += db->records[i].frequency;
            } else if (db->records[i].gender == 'M') {
                maleTotal += db->records[i].frequency;
            }
        }
    }
    
    printf("\nTotal females named %s: %d\n", name, femaleTotal);
    printf("Total males named %s: %d\n", name, maleTotal);
    printf("Total babies named %s: %d\n", name, femaleTotal + maleTotal);
}

/**
 * Finds and displays top 5 names in a given year
 * Parameters: db - pointer to database
 *            year - the year to search
 * Displays: top 5 female, male, and overall names
 */
void findTop5Names(const BabyDatabase* db, int year) {
    typedef struct {
        char name[MAX_NAME_LEN];
        int frequency;
    } NameCount;
    
    NameCount femaleNames[1000];
    NameCount maleNames[1000];
    NameCount overallNames[1000];
    int femaleCount = 0;
    int maleCount = 0;
    int overallCount = 0;
    int i = 0;
    int j = 0;
    
    printf("\nResults for %d\n", year);
    
    /* Collect names for this year by gender */
    for (i = 0; i < db->count; i++) {
        if (db->records[i].year == year) {
            if (db->records[i].gender == 'F') {
                /* Add to female list */
                int found = 0;
                for (j = 0; j < femaleCount; j++) {
                    if (compareNames(femaleNames[j].name, db->records[i].name)) {
                        femaleNames[j].frequency += db->records[i].frequency;
                        found = 1;
                        j = femaleCount;
                    }
                }
                if (found == 0 && femaleCount < 1000) {
                    strncpy(femaleNames[femaleCount].name, db->records[i].name, MAX_NAME_LEN - 1);
                    femaleNames[femaleCount].name[MAX_NAME_LEN - 1] = '\0';
                    femaleNames[femaleCount].frequency = db->records[i].frequency;
                    femaleCount++;
                }
            } else if (db->records[i].gender == 'M') {
                /* Add to male list */
                int found = 0;
                for (j = 0; j < maleCount; j++) {
                    if (compareNames(maleNames[j].name, db->records[i].name)) {
                        maleNames[j].frequency += db->records[i].frequency;
                        found = 1;
                        j = maleCount;
                    }
                }
                if (found == 0 && maleCount < 1000) {
                    strncpy(maleNames[maleCount].name, db->records[i].name, MAX_NAME_LEN - 1);
                    maleNames[maleCount].name[MAX_NAME_LEN - 1] = '\0';
                    maleNames[maleCount].frequency = db->records[i].frequency;
                    maleCount++;
                }
            }
            
            /* Add to overall list */
            int found = 0;
            for (j = 0; j < overallCount; j++) {
                if (compareNames(overallNames[j].name, db->records[i].name)) {
                    overallNames[j].frequency += db->records[i].frequency;
                    found = 1;
                    j = overallCount;
                }
            }
            if (found == 0 && overallCount < 1000) {
                strncpy(overallNames[overallCount].name, db->records[i].name, MAX_NAME_LEN - 1);
                overallNames[overallCount].name[MAX_NAME_LEN - 1] = '\0';
                overallNames[overallCount].frequency = db->records[i].frequency;
                overallCount++;
            }
        }
    }
    
    /* Sort female names by frequency */
    for (i = 0; i < femaleCount - 1; i++) {
        for (j = 0; j < femaleCount - i - 1; j++) {
            if (femaleNames[j].frequency < femaleNames[j + 1].frequency) {
                NameCount temp = femaleNames[j];
                femaleNames[j] = femaleNames[j + 1];
                femaleNames[j + 1] = temp;
            }
        }
    }
    
    /* Sort male names by frequency */
    for (i = 0; i < maleCount - 1; i++) {
        for (j = 0; j < maleCount - i - 1; j++) {
            if (maleNames[j].frequency < maleNames[j + 1].frequency) {
                NameCount temp = maleNames[j];
                maleNames[j] = maleNames[j + 1];
                maleNames[j + 1] = temp;
            }
        }
    }
    
    /* Sort overall names by frequency */
    for (i = 0; i < overallCount - 1; i++) {
        for (j = 0; j < overallCount - i - 1; j++) {
            if (overallNames[j].frequency < overallNames[j + 1].frequency) {
                NameCount temp = overallNames[j];
                overallNames[j] = overallNames[j + 1];
                overallNames[j + 1] = temp;
            }
        }
    }
    
    /* Display top 5 female */
    printf("\nTop 5 female names:\n");
    for (i = 0; i < 5 && i < femaleCount; i++) {
        printf("%d. %s (%d)\n", i + 1, femaleNames[i].name, femaleNames[i].frequency);
    }
    
    /* Display top 5 male */
    printf("\nTop 5 male names:\n");
    for (i = 0; i < 5 && i < maleCount; i++) {
        printf("%d. %s (%d)\n", i + 1, maleNames[i].name, maleNames[i].frequency);
    }
    
    /* Display top 5 overall */
    printf("\nTop 5 names overall:\n");
    for (i = 0; i < 5 && i < overallCount; i++) {
        printf("%d. %s (%d)\n", i + 1, overallNames[i].name, overallNames[i].frequency);
    }
}

/**
 * Draws a histogram of name popularity over time
 * Parameters: db - pointer to database
 *            name - the name to chart
 * Displays: histogram with 5-year cohorts showing percentage of population
 */
void drawHistogram(const BabyDatabase* db, const char* name) {
    typedef struct {
        int startYear;
        int endYear;
        int nameCount;
        int totalCount;
        double percentage;
    } Cohort;
    
    Cohort cohorts[30];
    int numCohorts = 0;
    int i = 0;
    int year = 0;
    double maxPercentage = 0.0;
    int maxStars = HISTOGRAM_MAX_WIDTH;
    
    printf("\n%s\n", name);
    
    /* Initialize cohorts */
    for (year = MIN_YEAR; year <= MAX_YEAR; year += COHORT_SIZE) {
        cohorts[numCohorts].startYear = year;
        cohorts[numCohorts].endYear = year + COHORT_SIZE - 1;
        if (cohorts[numCohorts].endYear > MAX_YEAR) {
            cohorts[numCohorts].endYear = MAX_YEAR;
        }
        cohorts[numCohorts].nameCount = 0;
        cohorts[numCohorts].totalCount = 0;
        cohorts[numCohorts].percentage = 0.0;
        numCohorts++;
    }
    
    /* Count frequencies for each cohort */
    for (i = 0; i < db->count; i++) {
        int cohortIndex = (db->records[i].year - MIN_YEAR) / COHORT_SIZE;
        
        if (cohortIndex >= 0 && cohortIndex < numCohorts) {
            cohorts[cohortIndex].totalCount += db->records[i].frequency;
            
            if (compareNames(db->records[i].name, name)) {
                cohorts[cohortIndex].nameCount += db->records[i].frequency;
            }
        }
    }
    
    /* Calculate percentages and find max */
    for (i = 0; i < numCohorts; i++) {
        if (cohorts[i].totalCount > 0) {
            cohorts[i].percentage = (double)cohorts[i].nameCount / cohorts[i].totalCount * 100.0;
            if (cohorts[i].percentage > maxPercentage) {
                maxPercentage = cohorts[i].percentage;
            }
        }
    }
    
    /* Draw histogram from most recent to oldest */
    for (i = numCohorts - 1; i >= 0; i--) {
        int numStars = 0;
        int j = 0;
        
        if (maxPercentage > 0) {
            numStars = (int)((cohorts[i].percentage / maxPercentage) * maxStars);
        }
        
        printf("%d-%d |", cohorts[i].startYear, cohorts[i].endYear);
        
        for (j = 0; j < numStars; j++) {
            printf("*");
        }
        printf("\n");
    }
}

/**
 * Writes combined data to output file
 * Parameters: db - pointer to database
 * Returns: 1 if successful, 0 if failed
 * Creates: combined.txt with year,name,frequency format
 * Note: Combines duplicate names from same year
 */
int writeCombinedFile(const BabyDatabase* db) {
    FILE* file = fopen("combined.txt", "w");
    typedef struct {
        char name[MAX_NAME_LEN];
        int frequency;
    } NameFreq;
    
    NameFreq yearNames[10000];
    int nameCount = 0;
    int year = 0;
    int i = 0;
    int j = 0;
    int minIdx = 0;
    int result = 1;
    
    if (file == NULL) {
        result = 0;
    } else {
        for (year = MIN_YEAR; year <= MAX_YEAR; year++) {
            nameCount = 0;

            for (i = 0; i < db->count; i++) {
                if (db->records[i].year == year) {
                    int found = 0;

                    for (j = 0; j < nameCount; j++) {
                        if (compareNames(yearNames[j].name, db->records[i].name)) {
                            yearNames[j].frequency += db->records[i].frequency;
                            found = 1;
                            j = nameCount;
                        }
                    }

                    if (found == 0 && nameCount < 10000) {
                        strncpy(yearNames[nameCount].name, db->records[i].name, MAX_NAME_LEN - 1);
                        yearNames[nameCount].name[MAX_NAME_LEN - 1] = '\0';
                        yearNames[nameCount].frequency = db->records[i].frequency;
                        nameCount++;
                    }
                }
            }

            for (i = 0; i < nameCount - 1; i++) {
                minIdx = i;
                for (j = i + 1; j < nameCount; j++) {
                    if (strcmp(yearNames[j].name, yearNames[minIdx].name) < 0) {
                        minIdx = j;
                    }
                }
                if (minIdx != i) {
                    NameFreq temp = yearNames[i];
                    yearNames[i] = yearNames[minIdx];
                    yearNames[minIdx] = temp;
                }
            }

            for (i = 0; i < nameCount; i++) {
                fprintf(file, "%d,%s,%d\n", year, yearNames[i].name, yearNames[i].frequency);
            }
        }
        
        fclose(file);
    }
    
    return result;
}

