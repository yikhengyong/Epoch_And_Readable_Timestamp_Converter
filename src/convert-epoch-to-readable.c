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
	uint64_t totaldays_before_month_adjust;
	unsigned int remain_seconds, remain_milliseconds;
	totaldays_before_month_adjust = epoch_input / (24ULL * 60 * 60 * 1000);
	remain_milliseconds = (unsigned int)epoch_input % (24ULL * 60 * 60 * 1000);
	remain_seconds = remain_milliseconds / 1000;

	// Step 2.0 Adjust GMT
	int hours_signed = (int)(remain_seconds / 3600);
	remain_seconds = remain_seconds % 3600;

	int GMT = 8;
	hours_signed += GMT;
	if (hours_signed < 0) {
		hours_signed += 24;
		totaldays_before_month_adjust -= 1;
	}
	else if (hours_signed > 23) {
		hours_signed -= 24;
		totaldays_before_month_adjust += 1;
	}

	// Step 3.0  Calculate Year from 1970
	unsigned short year = 1970; //Unix epoch start in 1 Jan 1970 00:00:00
	unsigned char leap_year_adjustment = 0;

	// totaldays_before_month_adjust is unsigned int, but use totaldays_before_month_adjust in iteration, last iteration will be negative value (signed) and cause error.
	int64_t i = (int64_t)totaldays_before_month_adjust;

	/** Reason of Use for (;;) instead of while (i >= 0)
	* The leap year status is calculated on the fly at the start of each iteration.
	* The same value is used for both the loop condition and the day deduction.
	* So there are no state inconsistencies across year boundaries.
	*/

	for (;;) { 
		
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			leap_year_adjustment = 1;
		}
		else {
			leap_year_adjustment = 0;
		}

		unsigned int days_this_year = (unsigned int)(365 + leap_year_adjustment);

		// If there aren't enough days left to consume another full year; it stops at this one.
		if (i < (int64_t)days_this_year) {
			break; 
		}

		i -= days_this_year;
		year++;
	}

	/** After the loop finishes, i always satisfies 0 <= i < number of days in the current year.
	 * So there is no risk of an out-of-bounds error.
	 */
	unsigned int totaldays = (unsigned int)i;

	// Step 4.0  Determine Months
	unsigned char days_in_each_month[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	// Step 4.1  Determine number of days in Febuary
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
		days_in_each_month[1] = 29;
	}
	else {
		days_in_each_month[1] = 28;
	}

	// Step 4.2  Calculate month
	unsigned char month = 0;
	while (totaldays >= days_in_each_month[month]) {
		totaldays -= days_in_each_month[month];
		month++;
	}

	// Step 4.3  Calibrate day and month
	unsigned char day = (unsigned char)(totaldays + 1); // start count from 1st day of the month, so need +1
	month++; // int month = 0 (January), so need +1          

	// Step 5.0  Determine minutes, seconds and milliseconds
	unsigned char minutes = (unsigned char)(remain_seconds / 60);
	unsigned char seconds = (unsigned char)(remain_seconds % 60);
	remain_milliseconds = remain_milliseconds % 1000;

	//Step 6.0  Output
	*year_output = year;
	*month_output = month;
	*day_output = day;
	*hours_output = (unsigned char)hours_signed;
	*minutes_output = minutes;
	*seconds_output = seconds;
	*milliseconds_output = remain_milliseconds;
}
