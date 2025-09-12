/***************************************************************** 

    File: lab1.c
    
    Author: [Arman Ataeipour]
    Seneca email: [aataeipour1@myseneca.ca]

    To compile program in codespaces, in terminal pane type:
        gcc -Wall lab1.c
    To run program in codespaces, in terminal pane type:
        ./a.out
        
***************************************************************/


#include <stdio.h>
int main(void)
{
    int celsius;
    float fahrenheit;
    printf("Please enter the temperature in Celsius: ");
    
    scanf("%d", &celsius);
    fahrenheit = (9.0f / 5.0f * (float)celsius) + 32.0f;

    printf("%d degrees Celsius is %.2f degrees Fahrenheit\n", celsius, fahrenheit);
    return 0;
}