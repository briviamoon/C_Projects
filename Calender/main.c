#include "calendy.h"

/*here we're building a calender*/
/*First we declare variables of month day and date*/
/**/

int findBeginingOfYear(int year);

int main ()
{
	int year;
	int month;
	int weekDay;
	int cycle;
	int lengthOfMonth;
	int startingDay;
	char *months[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
	char *days[] = {"Mon", "Tue", "Wed", "Thur", "Fri","Sat","Sun"};
	int dayOfMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};

	printf("\nEnter Your Year:");
	scanf("%d", &year);

	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
	{
		dayOfMonth[1] = 29;
	}

	startingDay = findBeginingOfYear(year);

	for (month = 0; month < 12; month++)
	{
		/*set max days in a month*/
		lengthOfMonth = dayOfMonth[month];
		int count = 0;

		/*print months*/
		printf("\n\n*********************%s******************\n", months[month]);

		


		/*print weekdays*/
		for (weekDay = 0; weekDay < 7; weekDay++)
		{
			printf(" %5s", days[weekDay]);
		}
		printf("\n");

		/*positioning the starting day*/
		for (count = 0; count < startingDay; count++)
		{
			printf("      ");
		}

		/*print the days*/
		for (cycle = 1; cycle <= lengthOfMonth; cycle++)
		{
			printf("%6d", cycle);

			/*fixing weekdays in sets of 7*/
			if(++count > 6) 
			{
				printf("\n");
				count = 0;
			}
			startingDay = count;
		}
	}
}

// int findBeginingOfYear(int year)
// {
// 	int month = 1, day = 1;

// 	if (month < 3)
// 	{
// 		month += 12;
// 		year -= 1;
// 	}

// 	int h = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;

// 	return(h);

// }