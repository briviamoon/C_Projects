#include "./include/main.h"

/**
 * main - prints out a callendar.
 */

void main(void)
{
    char *daysOfWeek[] = {
        "Sat",
        "Sun",
        "Mon",
        "Tue",
        "Wed",
        "Thu",
        "Fri",
    };
    char *month[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int daysCount, monthCount, weekday;
    int d, m, y;
    int opt;

    printf("----------------------------------------------------------\n");
    printf("##########################################################\n");
    printf("                    Zeller's Congruence                   \n");
    printf("        find the day of the week of any day of a year     \n");
    printf("            program was writen by *Brivia Allan*          \n");
    printf("                let me take you on a date \\^^/\n");
    printf("##########################################################\n");
    printf("----------------------------------------------------------\n\n\n\n");

    printf("                Enter a day, month, and year\n                     Day Month Year\n");
    scanf("%d %d %d", &d, &m, &y);

    /*calling the zellers congrunce function*/
    weekday = zellerCongruence(d, m, y);

    /*checking for a leap year*/
    if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0))
    {
        daysInMonth[1] = 29;
    }

    printf("\n\n%d/%d/%d was on a %s\n", d, m, y, daysOfWeek[weekday]);
    printf("\n\nDo you want to view the full Year's calendar?\n 1 if Yes & 2 to Skip: ");
    scanf("%d", &opt);

    /*call funtion to print a calender*/
    /*this finction takes the option from user*/
    /*also takes weekday for the starting day of the day in the week*/
    printCalendar(opt, weekday, d, m, y);
}
