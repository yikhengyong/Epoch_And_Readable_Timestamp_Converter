/**
* @file     main.c
* @brief    Print out epoch and timestamp result
* @return   None
*/

#include <stdio.h>
#include "function.h" 

void main() {

    struct readable_timestamp {
        unsigned short year;
        unsigned char month;
        unsigned char day;
        unsigned char hours;
        unsigned char minutes;
        unsigned char seconds;
        unsigned int milliseconds;
    };

    // Step 1   Convert readable timestamp to epoch
    struct readable_timestamp current_readable_time = { 0 };
    uint64_t current_epoch_time = 0;

    current_readable_time.year = 2026;
    current_readable_time.month = 8;
    current_readable_time.day = 6;
    current_readable_time.hours = 13; // 0-23
    current_readable_time.minutes = 47;
    current_readable_time.seconds = 1;
    current_readable_time.milliseconds = 1;

    convert_readable_to_epoch(&current_epoch_time,
        current_readable_time.year,
        current_readable_time.month,
        current_readable_time.day,
        current_readable_time.hours,
        current_readable_time.minutes,
        current_readable_time.seconds,
        current_readable_time.milliseconds);

    printf("Epoch: %lld\n", current_epoch_time);
    
    // Step 2   Reset
    current_epoch_time = 0;

    current_readable_time.year = 0;
    current_readable_time.month = 0;
    current_readable_time.day = 0;
    current_readable_time.hours = 0; 
    current_readable_time.minutes = 0;
    current_readable_time.seconds = 0;
    current_readable_time.milliseconds = 0;

    // Step 3   Convert epoch to readable timestamp
	current_epoch_time = 1785995221001; // Milliseconds

    convert_epoch_to_readable(current_epoch_time,
        &current_readable_time.year,
        &current_readable_time.month,
        &current_readable_time.day,
        &current_readable_time.hours,
        &current_readable_time.minutes,
        &current_readable_time.seconds,
        &current_readable_time.milliseconds);

    printf("Readable: %02d:%02d:%02d:%03d %02d/%02d/%04d\n\r", current_readable_time.hours,
        current_readable_time.minutes,
        current_readable_time.seconds,
        current_readable_time.milliseconds,
        current_readable_time.day,
        current_readable_time.month,
        current_readable_time.year);

}
