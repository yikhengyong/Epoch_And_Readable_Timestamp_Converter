#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdint.h>

/* ========================= Function Declarations ========================= */

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

void convert_epoch_to_readable(uint64_t epoch_input, unsigned short* year_output, unsigned char* month_output, unsigned char* day_output, unsigned char* hours_output, unsigned char* minutes_output, unsigned char* seconds_output, unsigned int* milliseconds_output);

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

void convert_readable_to_epoch(uint64_t* epoch_output, unsigned short year_input, unsigned char month_input, unsigned char day_input, unsigned char hours_input, unsigned char minutes_input, unsigned char seconds_input, unsigned int milliseconds_input);

#endif // FUNCTION_H 
