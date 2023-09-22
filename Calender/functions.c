#include "calendy.h"

/*FINDING THE DATE OF THE FIRST DAY OF THE YEAR*/
/*#####ZELLER'S CONGRUENCE######*/
/*h = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7*/



int findBeginingOfYear(int year)
{
	int month = 1, day = 1;

	if (month < 3)
	{
		month += 12;
		year -= 1;
	}

	int h = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;

	return(h);

}