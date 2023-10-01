#include "../include/main.h"

/**
 * printCalender - prints a year's calender
 */

void printCalendar(int opt, int weekday, int d, int m, int y)
{
    (void)d;
    (void)m;

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
    int monthCount, daysCount;
    int day, months, years;

    if (opt == 1)
    {
        /*print the calender*/
        printf("\n\t\t\tThe year of %d\n\n", y);

        /*print the months*/

        for (monthCount = 0; monthCount < 12; monthCount++)
        {
            int counter = 0;

            printf("\t\t\t    %s\n", month[monthCount]);
            printf("   ################################################################\n");
            printf("   ****************************************************************\n\n");

            /*Print the days of the wek*/

            for (daysCount = 0; daysCount < 7; daysCount++)
            {
                printf("\t %3s", daysOfWeek[daysCount]);
            }
            printf("\n\n");

            /*this part of the code is going to fill space*/
            /*that are not the starting day of a month/year*/

            for (counter = 0; counter < weekday; counter++)
            {
                printf("        ");
            }

            /*now to print the days of the month*/
            for (daysCount = 1; daysCount <= daysInMonth[monthCount]; daysCount++)
            {
                printf("\t%4d", daysCount);

                if (++counter > 6)
                {
                    printf("\n");
                    counter = 0;
                }
                weekday = counter;
            }
            printf("\n\n");
        }
        printf("you can follow me on Github @briviamoon\n\thttps://github.com/briviamoon");
    }
    else
    {
        printf("you can follow me on Github @briviamoon\n\thttps://github.com/briviamoon");
    }
}