#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LEN 256
#define MAX_NAME_LEN 100

void toLowerCase(char* dest, const char* src) {
    while (*src) {
        *dest = (char)tolower((unsigned char)*src);
        dest++;
        src++;
    }
    *dest = '\0';
}

int compareNamesIgnoreCase(const char* a, const char* b) {
    char la[MAX_NAME_LEN], lb[MAX_NAME_LEN];
    toLowerCase(la, a);
    toLowerCase(lb, b);
    return strcmp(la, lb);
}

int main(void) {
    char inputFile[128];
    char outputFile[128] = "search_results.csv"; 
    char searchName[MAX_NAME_LEN];
    int genderChoice = 0;

    FILE* in  = NULL;
    FILE* out = NULL;
    char line[MAX_LINE_LEN];
    char nameField[MAX_NAME_LEN];
    int year, freq;
    int matches = 0;

    printf("Search in which file?\n");
    printf("  1) malebabynames.csv\n");
    printf("  2) femalebabynames.csv\n");
    printf("Enter 1 or 2: ");
    if (scanf("%d", &genderChoice) != 1 || (genderChoice != 1 && genderChoice != 2)) {
        printf("Invalid choice.\n");
        return 1;
    }

    if (genderChoice == 1) {
        strcpy(inputFile, "malebabynames.csv");
    } else {
        strcpy(inputFile, "femalebabynames.csv");
    }

    printf("Enter name to search for: ");
    if (scanf("%99s", searchName) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    in = fopen(inputFile, "r");
    if (!in) {
        printf("Could not open input file '%s'\n", inputFile);
        return 1;
    }

    out = fopen(outputFile, "w");
    if (!out) {
        printf("Could not open output file '%s'\n", outputFile);
        fclose(in);
        return 1;
    }
    while (fgets(line, sizeof(line), in)) {
        if (sscanf(line, "%d,%99[^,],%d", &year, nameField, &freq) == 3) {
            if (compareNamesIgnoreCase(nameField, searchName) == 0) {
                fputs(line, out);
                matches++;
            }
        }
    }

    fclose(in);
    fclose(out);

    printf("Found %d matching rows for name '%s'.\n", matches, searchName);
    printf("Matching rows were written to '%s'.\n", outputFile);

    return 0;
}


