-------------------------------------------------------------------------

<div align="center">
  <p><em>Coding & knowledgebase are not always perfect.</em></p>
  <p><em>Feel free to <b>POINT OUT ERRORS</b> and <b>SHARE YOUR IDEAS</b>.</em></p>
  </div>
 

-------------------------------------------------------------------------

<br>

# Epoch_And_Readable_Timestamp_Converter

## About
- A manual implementation of bidirectional conversion between epoch time (in milliseconds) and human-readable timestamps.
- This project deliberately avoids using <time.h>, implementing all conversion logic from scratch (leap year calculation, month decomposition, and timezone offsets). 
- The goal is to remain portable in scenarios lacking standard library support, such as resource-constrained embedded environments. 
- This is a personal toolkit project. Copying, modification, and feedback for improvement are all welcome.

<br>

## Features
- Bidirectional conversion between Epoch (millisecond precision) and human-readable time (Year/Month/Day/Hour/Minute/Second/Millisecond).
- Supports arbitrary integer-hour timezone offsets** (not restricted to a fixed UTC+8).
- Input validation: Invalid inputs are rejected with clear failure signals rather than returning erroneous results silently.
- Includes boundary-case unit tests (leap years, day transitions, year transitions, and positive/negative timezone offsets).

<br>

## Known Limitations

1. Timezone offsets support whole hours only.
	- It does not support half-hour or 45-minute offsets like UTC+5:30 (India) or UTC+5:45 (Nepal). 
	- To support these, the internal conversion unit would need to change from hours to minutes.
	
2. Does not handle Daylight Saving Time (DST).
	- The passed offset is treated as a fixed value and will not automatically adjust based on the date.
	
3. Valid time range
	- This implementation assumes years are no earlier than 1970 (the Unix Epoch origin).
	- The coding does not perform special handling for years exceeding the range of an `unsigned short` (approximately year 65535 AD).
	
4. Offset validation range
	- Assumes the passed GMT offset falls within real-world ranges (approximately -12 to +14 hours). 
	- Extreme inputs outside this range have not been stress-tested.

<br>

## Why No <time.h>?
Most conversion tools directly call standard library functions like `mktime` or `gmtime` for this task. 

This project deliberately writes out the entire process by hand with the aims of: 

- Understanding the actual mathematics behind Unix Epoch and calendar time (leap year rules, month-day decomposition, and timezone offset carry logic) rather than treating it as a black box. 
- Preserving the possibility of porting the code to environments without full C standard library support (such as certain embedded platforms).

<br>

## Folder Structure

	├── include
	│   └── function.h
	├── src
	│   └── convert-readable-to-epoch.c
	│   └── convert-epoch-to-readable.c
	├── main.c
	├── README.md

<br>

## Example

	Epoch: 4107513600000
	Readable: 00:00:00:000 01/03/2100

<br>

## Result
| Test Scenario Description													 | Local Time (UTC+8)	   | Epoch (ms)	   | Result	|
| -------------------------------------------------------------------------- | ----------------------- | ------------- | ------ |
| **Cross-day boundary: Local 03:20 AM**									 | 2026-08-06 03:00:00.000 | 1785956400000 | Pass   |
| **Local last millisecond of the day**										 | 2025-08-05 23:59:59.999 | 1785945599999 | Pass	|
| **Local first millisecond of the day**									 | 2026-08-06 00:00:00.000 | 1785945600000 | Pass	|
| **Leap year: February 29**												 | 2024-02-29 12:00:00.000 | 1709179200000 | Pass	|
| **Common year: February 28 (Next day should jump to 3/1)**				 | 2025-02-28 12:00:00.000 | 1740715200000 | Pass	|
| **New Year boundary: Local 12/31 23:00**									 | 2025-12-31 23:00:00.000 | 1767193200000 | Pass	|
| **New Year boundary: Local 1/1 01:00 AM (Leap-to-common year transition)** | 2026-01-01 01:00:00.000 | 1767200400000 | Pass	|
| **Unix Epoch start (Local 08:00 = UTC 0)**								 | 1970-01-01 08:00:00.000 | 0			   | Pass	|
| **Century leap year 2000 (Divisible by 400)**							     | 2000-02-29 00:00:00.000 | 951753600000  | Pass	|
| **Day after century common year 2100 (Divisible by 100, not by 400)**		 | 2100-03-01 00:00:00.000 | 4107513600000 | Pass	|

<br>

## License
This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.
