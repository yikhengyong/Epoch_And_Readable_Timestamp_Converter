/**
* @file     convert-readable-to-epoch.c
* @brief    Convert timestamp to epoch
* @param    epoch_output - epoch time in milliseconds
* @param    year_input - pointer to store the year
* @param    month_input - pointer to store the month
* @param    day_input - pointer to store the day
* @param    hours_input - pointer to store the hours
* @param    minutes_input - pointer to store the minutes
* @param    seconds_input - pointer to store the seconds
* @param    milliseconds_input - pointer to store the milliseconds
* @return   None
*/

#include <stdio.h> 
#include "function.h"

void convert_readable_to_epoch(uint64_t* epoch_output, unsigned short year_input, unsigned char month_input, unsigned char day_input, unsigned char hours_input, unsigned char minutes_input, unsigned char seconds_input, unsigned int milliseconds_input)
{
	if (month_input < 1 || month_input > 12 ||
		day_input < 1 || day_input > 31 ||
		hours_input > 23 || minutes_input > 59 ||
		seconds_input > 59 || milliseconds_input > 999) {

		printf("Invalid input values. Please check the input parameters.\n");

		*epoch_output = 0; 

		return;
	}

	// Step 1.0 Calculate number of leap years from 1970 to timestamp year
	unsigned short year_from_1970;
	unsigned char number_leapyears = 0;

	for (year_from_1970 = 1970; year_from_1970 < year_input; year_from_1970++) {

		if ((year_from_1970 % 4 == 0 && year_from_1970 % 100 != 0) || (year_from_1970 % 400 == 0)) {
			number_leapyears++; //+1 day in leap year
		};
	}

	// Step 2.0  Calculate total days from 1 Jan 1970 to 31st Dec of (year of the string-1)
	uint64_t totaldays_from_string, timestamp_from_string;
	totaldays_from_string = ((uint64_t)(year_input - 1970) * 365) + number_leapyears;

	// Step 3.0 Calculate total days from 1 Jan (year of the string) to 31 of (month of the string-1)
	unsigned char days_in_each_month_ConvertString[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	// Step 3.1 Determine number of days in Febuary in given year
	if ((year_input % 4 == 0 && year_input % 100 != 0) || (year_input % 400 == 0)) {
		days_in_each_month_ConvertString[1] = 29;
	}
	else {
		days_in_each_month_ConvertString[1] = 28;
	};

	// Step 3.2 End  Sum up total days
	for (unsigned char i_month_ConvertString = 0; i_month_ConvertString < (month_input - 1); i_month_ConvertString++) {
		totaldays_from_string = totaldays_from_string + days_in_each_month_ConvertString[i_month_ConvertString];
	};

	// Step 4.0 Calculate total days from from 1 Jan 1970 to string given
	totaldays_from_string = totaldays_from_string + ((uint64_t)(day_input - 1));

	// Step 5.0 GMT
	int GMT = 8;
	int hours_signed = (int)hours_input - GMT;

	if (hours_signed < 0) {
		hours_signed += 24;
		totaldays_from_string -= 1;
	}
	else if (hours_signed > 23) {
		hours_signed -= 24;
		totaldays_from_string += 1;
	};

	hours_input = (unsigned char)hours_signed;

	// Step 6.0  Calculate timestamp in milliseconds
	timestamp_from_string = (totaldays_from_string * 86400000) + ((uint64_t)(hours_input * 3600000)) + ((uint64_t)(minutes_input * 60000)) + ((uint64_t)(seconds_input * 1000)) + milliseconds_input;

	*epoch_output = timestamp_from_string;

}
