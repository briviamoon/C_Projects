#include "../include/main.h"

/**h is the day of the week (0 = Saturday, 1 = Sunday, 2 = Monday, …, 6 = Friday)
 *day is the day of the month
 *month is the month (3 = March, 4 = April, 5 = May, …, 14 = February)
 *year is the year of the century (year % 100).
 *century is the zero-based century (actually ⌊ year/100 ⌋)
 *          For example, the zero-based centuries for 1995 and 2000 are 19 and 20
 *          respectively (to not be confused with the common ordinal century enumeration
 *          which indicates 20th for both cases).
 * In this algorithm January and February are
 * counted as months 13 and 14 of the previous
 * year.E.g. if it is 2 February 2010, the
 * algorithm counts the date as the second day
 * of the fourteenth month of 2009 (02/14/2009
 * in DD/MM/YYYY format)
 * 
 * day + (13 * (month + 1) / 5) + year + (year / 4) + (century / 4) + (5 * century)) % 7
 * 
 */

int zellerCongruence(int d, int m, int y)
{
    int yearin = y % 100;
    int century = y / 100;
    int dateInWeek;
    int mon;

    /*this checks whether the month is january or february*/
    if (m > 2)
    {
        mon = m;
    }
    /*if it is, the number is addedd to 12 to make 13 and 14 as jan & feb */
    else
    {
        mon = (m + 12);
        y -= 1;
    }

    dateInWeek = (d + ((13 * (mon + 1)) / 5) + y + (y / 4) - (y / 100) + (y / 400)) % 7;

    return (dateInWeek);
}
