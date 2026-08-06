/**
* @file     convert-epoch-to-readable.c
* @brief    Convert epoch to readable timestamp
* @param    epoch_input - epoch time in milliseconds
* @param    year_output - pointer to store the year
* @param    month_output - pointer to store the month
* @param    day_output - pointer to store the day
* @param    hours_output - pointer to store the hours
* @param    minutes_output - pointer to store the minutes
* @param    seconds_output - pointer to store the seconds
* @param    milliseconds_output - pointer to store the milliseconds
* @return   None
*/

#include <stdio.h> 
#include "function.h"

void convert_epoch_to_readable(uint64_t epoch_input, unsigned short* year_output, unsigned char* month_output, unsigned char* day_output, unsigned char* hours_output, unsigned char* minutes_output, unsigned char* seconds_output, unsigned int* milliseconds_output)
{

	// Step 1.0  Calculate Total Days
	unsigned int totaldays, remain_seconds, remain_milliseconds;
	totaldays = epoch_input / (24ULL * 60 * 60 * 1000);
	remain_milliseconds = epoch_input % (24ULL * 60 * 60 * 1000);
	remain_seconds = remain_milliseconds / 1000;

	// Step 2.0  Calculate Year from 1970
	unsigned short year = 1970; //Unix epoch start in 1 Jan 1970 00:00:00
	unsigned char leap_year_adjustment = 0;//1970 is not leap year, so initialize to 0

	signed int i = totaldays;//totaldays is unsigned int, but use totaldays in iteration, last iteration will be negative value (signed) and cause error.

	while (i >= (365 + leap_year_adjustment)) {

		/*
		Step 2.1  Determine leap year
			1) Divisible by 4 && Not Divisible by 100
			2) Or Divisible by 400.
		*/

		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			leap_year_adjustment = 1; //365+1=366 days
		}
		else {
			leap_year_adjustment = 0; //365+0=365 days
		}

		// Step 2.2  Add 1 year
		year++;
		i -= (365 + leap_year_adjustment); // 365 or 366 days in totaldays been used for add 1 year
	}

	// Step 2.3 Calibrate totaldays
	if (i < 0) {
		totaldays = i + (365 + leap_year_adjustment);
		year--; // If don't have these code, exp:31-12-2024 will become 2025
	}
	else {
		totaldays = i;
	}

	// Step 3.0  Determine Months
	unsigned char days_in_each_month[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	// Step 3.1  Determine number of days in Febuary
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
		days_in_each_month[1] = 29;
	}
	else {
		days_in_each_month[1] = 28;
	}

	// Step 3.2  Calculate month
	unsigned char month = 0;
	while (totaldays >= days_in_each_month[month]) {
		totaldays -= days_in_each_month[month];
		month++;
	}

	// Step 3.3  Calibrate day and month
	unsigned char day = totaldays + 1; // start count from 1st day of the month, so need +1
	month++; // int month = 0 (January), so need +1          

	// Step 4.0  Determine hours
	unsigned char hours;
	hours = (remain_seconds / (60 * 60));
	remain_seconds = remain_seconds % (60 * 60);

	// Step 4.1 Adjust GMT
	signed char GMT = 8;
	hours = hours + GMT;

	if (hours < 0) {
		hours = hours + 24;
		totaldays = totaldays - 1;
	}
	else if (hours > 23) {
		hours = hours - 24;
		totaldays = totaldays + 1;
	};

	// Step 5.0  Determine minutes and seconds
	unsigned char minutes, seconds;
	minutes = remain_seconds / 60;
	seconds = remain_seconds % 60;
	remain_milliseconds = remain_milliseconds % 1000;

	//Step 6.0  Output
	*year_output = year;
	*month_output = month;
	*day_output = day;
	*hours_output = hours;
	*minutes_output = minutes;
	*seconds_output = seconds;
	*milliseconds_output = remain_milliseconds;
}
