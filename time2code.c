// time2code.c
// Assignment 1, COMP1511 18s1: Time To Code.
//
// This program by Dion Earle (z5205292) on INSERT-DATE-HERE

#include <stdio.h>
#include <assert.h>

// You must use these #defines - DO NOT CHANGE THEM

#define TOWN_ADELAIDE       0
#define TOWN_BRISBANE       1
#define TOWN_BROKEN_HILL    2
#define TOWN_CANBERRA       3
#define TOWN_DARWIN         4
#define TOWN_EUCLA          5
#define TOWN_HOBART         6
#define TOWN_LORD_HOWE_IS   7
#define TOWN_MELBOURNE      8
#define TOWN_PERTH          9
#define TOWN_SYDNEY         10

// New Zealand

#define TOWN_AUCKLAND       11
#define TOWN_CHRISTCHURCH   12
#define TOWN_WELLINGTON     13

// Australia

#define TIMEZONE_AWST_OFFSET  800 // Australian Western Standard Time

#define TIMEZONE_ACWST_OFFSET 845 // Australian Central Western Standard Time

#define TIMEZONE_ACST_OFFSET  930 // Australian Central Standard Time
#define TIMEZONE_ACDT_OFFSET 1030 // Australian Central Daylight Time

#define TIMEZONE_AEST_OFFSET 1000 // Australian Eastern Standard Time
#define TIMEZONE_AEDT_OFFSET 1100 // Australian Eastern Daylight Time

#define TIMEZONE_LHST_OFFSET 1030 // Lord Howe Standard Time
#define TIMEZONE_LHDT_OFFSET 1100 // Lord Howe Daylight Time

// New Zealand
#define TIMEZONE_NZST_OFFSET 1200 // NZ Standard Time
#define TIMEZONE_NZDT_OFFSET 1300 // NZ Daylight Time

// returned by get_local_time
#define INVALID_INPUT (-1)


// ADD YOUR #defines (if any) here

//All used when the local time has minutes greater than 60 (as this is invalid)
#define UTC_TIME_LIMIT 2360
#define MAX_HOURS 2400
#define MAX_MINUTES 60
#define OVERFLOW_NEW_HOUR 40

//Months in which daylight savings starts and ends
#define START_DST_MTH 10
#define END_DST_MTH 3

//Days on which daylight savings starts and ends
#define START_DST_DAY 6
#define END_DST_DAY 31
//Times at which daylight savings starts and ends for certain timezones
#define ACDT_SWITCH_HR 1630
#define AEDT_SWITCH_HR 1600
#define LHDT_START_HR 1500
#define LHDT_END_HR 1530
#define NZDT_SWITCH_HR 1400


int get_local_time(int town, int utc_month, int utc_day, int utc_time);
void run_unit_tests(void);


// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE
int is_valid_town(int town);
int is_valid_date(int utc_month, int utc_day);
int is_valid_time(int utc_time);
int choose_timezone(int town, int utc_month, int utc_day, int utc_time);
int final_output_checks(int town, int local_time);


// DO NOT CHANGE THIS FUNCTION

// This main function won't be marked as part of the assignment
// It tests the functions you have to write.
// Do not change this main function.  If it does not work with
// your functions you have misunderstood the assignment.

int main(void) {
    int call_get_local_time = 0;

    printf("Enter 0 to call run_unit_tests()\n");
    printf("Enter 1 to call get_local_time()\n");
    printf("Call which function: ");
    scanf("%d", &call_get_local_time);

    if (!call_get_local_time) {
        printf("calling run_unit_tests()\n");
        run_unit_tests();
        printf("unit tests done\n");
        return 0;
    }

    int town = 0;
    int month = 0;
    int day = 0;
    int time = 0;

    printf("Enter %d for Adelaide\n", TOWN_ADELAIDE);
    printf("Enter %d for Brisbane\n", TOWN_BRISBANE);
    printf("Enter %d for Broken_hill\n", TOWN_BROKEN_HILL);
    printf("Enter %d for Canberra\n", TOWN_CANBERRA);
    printf("Enter %d for Darwin\n", TOWN_DARWIN);
    printf("Enter %d for Eucla\n", TOWN_EUCLA);
    printf("Enter %d for Hobart\n", TOWN_HOBART);
    printf("Enter %d for Lord Howe Island\n", TOWN_LORD_HOWE_IS);
    printf("Enter %d for Melbourne\n", TOWN_MELBOURNE);
    printf("Enter %d for Perth\n", TOWN_PERTH);
    printf("Enter %d for Sydney\n", TOWN_SYDNEY);
    printf("Enter %d for Auckland\n", TOWN_AUCKLAND);
    printf("Enter %d for Christchurch\n", TOWN_CHRISTCHURCH);
    printf("Enter %d for Wellington\n", TOWN_WELLINGTON);

    printf("Which town: ");
    scanf("%d", &town);

    printf("Enter UTC month as integer 1..12: ");
    scanf("%d", &month);

    printf("Enter UTC day as integer 1..31: ");
    scanf("%d", &day);

    printf("Enter UTC time as hour * 100 + minutes\n");
    printf("Enter UTC time as integer [0..2359]: ");
    scanf("%d", &time);

    int local_time = get_local_time(town, month, day, time);

    if (local_time == INVALID_INPUT) {
        printf("invalid input - local time could not be calculated\n");
    } else {
        printf("local_time is %d\n", local_time);
    }
    return 0;
}



// Given an Australian town and a 2018 UTC time
// return the local time in the Australian town
//
// time is returned as hours*100 + minutes
// INVALID_INPUT is return for invalid inputs
//
// utc_month should be 1..12
// utc_day should be 1..31
// utc_time should be 0..2359
// utc_time is hours*100 + minutes
//
// note UTC year is assumed to be 2018
// note UTC seconds is assumed to be zero
//

int get_local_time(int town, int utc_month, int utc_day, int utc_time) {

	int local_time;
	
	//Returns INVALID_INPUT if user input is wrong, else determines timezone
	if (is_valid_town(town) == INVALID_INPUT) {
		local_time = INVALID_INPUT;
	} else if (is_valid_date(utc_month, utc_day) == INVALID_INPUT) {
		local_time = INVALID_INPUT;
	} else if (is_valid_time(utc_time) == INVALID_INPUT) {
		local_time = INVALID_INPUT;
	} else {
		local_time = choose_timezone(town, utc_month, utc_day, utc_time);
	}


	//Checks to see if the local time outputted is correct
    local_time = final_output_checks(town, local_time);

	return local_time;
}

int is_valid_town(int town) {

	int output_town;

	//Basic test to confirm valid town is chosen
	if ((town < 0) || (town > 13)) {
		output_town = INVALID_INPUT;
    } else {
		output_town = 0;
    }

    return output_town;
}

int is_valid_date(int utc_month, int utc_day) {

	int output_date;

	//Basic test to confirm valid month and day is chosen
	if ((utc_month < 1) || (utc_month > 12)) {
		output_date = INVALID_INPUT;
    } else if ((utc_day < 1) || (utc_day > 31)) {
		output_date = INVALID_INPUT;
	} else {
		output_date = 0;
    }

	//Testing for months with less than 31 days
    if (utc_month == 2 && utc_day > 28) {
		output_date = INVALID_INPUT;
    } else if (utc_month == 4 && utc_day > 30) {
		output_date = INVALID_INPUT;
    } else if (utc_month == 6 && utc_day > 30) {
		output_date = INVALID_INPUT;
    } else if (utc_month == 9 && utc_day > 30) {
		output_date = INVALID_INPUT;
    } else if (utc_month == 11 && utc_day > 30) {
		output_date = INVALID_INPUT;
    }

    return output_date;
}

int is_valid_time(int utc_time) {

	int output_time;

	//Basic test to ensure valid utc time is chosen
	if ((utc_time < 0) || (utc_time >= UTC_TIME_LIMIT)) {
		output_time = INVALID_INPUT;
	} else if ((utc_time % 100) >= MAX_MINUTES) {
		output_time = INVALID_INPUT;
	} else {
		output_time = 0;
    }

    return output_time;
}

int choose_timezone(int town, int utc_month, int utc_day, int utc_time) {

	int output_timezone;

	//Returning timezone for Adelaide & Broken Hill
	if ((town == TOWN_ADELAIDE) || (town == TOWN_BROKEN_HILL)) {
		if ((utc_month < END_DST_MTH) || (utc_month > START_DST_MTH)) {
		    output_timezone = utc_time + TIMEZONE_ACDT_OFFSET;
		} else if (((utc_month == END_DST_MTH) && (utc_day < END_DST_DAY))
		    || ((utc_month == START_DST_MTH) && (utc_day > START_DST_DAY))) {
		        output_timezone = utc_time + TIMEZONE_ACDT_OFFSET;       
		} else if (((utc_month == END_DST_MTH) && (utc_day == END_DST_DAY) 
		    && (utc_time < ACDT_SWITCH_HR)) || ((utc_month == START_DST_MTH) 
		    && (utc_day == START_DST_DAY) && (utc_time >= ACDT_SWITCH_HR))) {
		        output_timezone = utc_time + TIMEZONE_ACDT_OFFSET;       
		} else {
		    output_timezone = utc_time + TIMEZONE_ACST_OFFSET; 
		}
	}

	//Returning timezone for Brisbane
	if (town == TOWN_BRISBANE) {
		output_timezone = utc_time + TIMEZONE_AEST_OFFSET;
	}

	//Returning timezone for Sydney, Canberrra, Hobart & Melbourne
	if ((town == TOWN_SYDNEY) || (town == TOWN_CANBERRA)
	|| (town == TOWN_HOBART) || (town == TOWN_MELBOURNE)) { 
		if ((utc_month < END_DST_MTH) || (utc_month > START_DST_MTH)) {
		    output_timezone = utc_time + TIMEZONE_AEDT_OFFSET;
		} else if (((utc_month == END_DST_MTH) && (utc_day < END_DST_DAY))
		    || ((utc_month == START_DST_MTH) && (utc_day > START_DST_DAY))) {
		        output_timezone = utc_time + TIMEZONE_AEDT_OFFSET;
		} else if (((utc_month == END_DST_MTH) && (utc_day == END_DST_DAY) 
		    && (utc_time < AEDT_SWITCH_HR)) || ((utc_month == START_DST_MTH) 
		    && (utc_day == START_DST_DAY) && (utc_time >= AEDT_SWITCH_HR))) {
			    output_timezone = utc_time + TIMEZONE_AEDT_OFFSET;
		} else {
			output_timezone = utc_time + TIMEZONE_AEST_OFFSET; 
		}
	}
	
	//Returning timezone for Darwin
	if (town == TOWN_DARWIN) {
		output_timezone = utc_time + TIMEZONE_ACST_OFFSET;
	}

	//Returning timezone for Eucla
	if (town == TOWN_EUCLA) {
		output_timezone = utc_time + TIMEZONE_ACWST_OFFSET;
	}

	//Returning timezone for Lord Howe Island
	if (town == TOWN_LORD_HOWE_IS) {
		if ((utc_month < END_DST_MTH) || (utc_month > START_DST_MTH)) {
		    output_timezone = utc_time + TIMEZONE_LHDT_OFFSET;
		} else if(((utc_month == END_DST_MTH) && (utc_day < END_DST_DAY))
		    || ((utc_month == START_DST_MTH) && (utc_day > START_DST_DAY))) {
			    output_timezone = utc_time + TIMEZONE_LHDT_OFFSET;
		} else if(((utc_month == END_DST_MTH) && (utc_day == END_DST_DAY) 
		    && (utc_time < LHDT_START_HR)) || ((utc_month == START_DST_MTH) 
		    && (utc_day == START_DST_DAY) && (utc_time >= LHDT_END_HR))) {
			    output_timezone = utc_time + TIMEZONE_LHDT_OFFSET;
		} else {
			output_timezone = utc_time + TIMEZONE_LHST_OFFSET;
		}
	}

	//Returning timezone for Perth
	if (town == TOWN_PERTH) {
		output_timezone = utc_time + TIMEZONE_AWST_OFFSET;
	}

	//Returning timezone for Auckland, Christchurch & Wellington
	if (town == TOWN_AUCKLAND  || town == TOWN_CHRISTCHURCH 
	|| town == TOWN_WELLINGTON) {
		if ((utc_month < END_DST_MTH) || (utc_month > START_DST_MTH)) {
		    output_timezone = utc_time + TIMEZONE_NZDT_OFFSET;
		} else if (((utc_month == END_DST_MTH) && (utc_day < END_DST_DAY))
		    || ((utc_month == START_DST_MTH) && (utc_day > START_DST_DAY))) {
		        output_timezone = utc_time + TIMEZONE_NZDT_OFFSET;
		} else if (((utc_month == END_DST_MTH) && (utc_day == END_DST_DAY) 
		    && (utc_time < NZDT_SWITCH_HR)) || ((utc_month == START_DST_MTH) 
		    && (utc_day == START_DST_DAY) && (utc_time >= NZDT_SWITCH_HR))) {
			    output_timezone = utc_time + TIMEZONE_NZDT_OFFSET;
		} else {
			output_timezone = utc_time + TIMEZONE_NZST_OFFSET;
		}
	}

	return output_timezone;
}


int final_output_checks(int town, int local_time) {

    //Changing the minutes if they end in a number greater than 60
	if ((local_time % 100) >= MAX_MINUTES) {
		local_time = local_time + OVERFLOW_NEW_HOUR;
	}
        
    //Changing local time if reaches the 24th hour of a day
    if (local_time >= MAX_HOURS) {
        if (town == TOWN_EUCLA) {
            local_time = (local_time - UTC_TIME_LIMIT);
    } else
        local_time = (local_time - MAX_HOURS);
    }
	
	return local_time;
}

/* To begin, I firstly went through all of the possible cases where the program should return INVALID_INPUT. These were scenarios were a number was entered that did not represent one of the possible towns, months, days, or times. When doing so, I made sure to test close to these boundaries to ensure nothing slipped past.

Next, I ran a simple test for each of the timezones, making sure they all worked under regular conditions. This included both the standard times and daylight savings times, choosing times in the year when these were active. This also ensured I didn't accidentally miss anything.

Finally, the most crucial tests were on the edges of when daylight savings would start and end. I ran four tests for each timezone, testing right before it switched over and as soon as it did switch over for both occurunces in 2018. The many different time changes took quite some time to get my head around, yet it was essential I used these final tests to pick up any miscalculations. */

// run unit tests for get_local_time

void run_unit_tests(void) {
    // 2 example unit tests

    // UTC midnight on 20th March -> time in Sydney: 11am AEDT
    assert(get_local_time(TOWN_SYDNEY, 3, 20, 0) == 1100);

    // 42 is not a valid month
    assert(get_local_time(TOWN_SYDNEY, 42, 0, 0) == INVALID_INPUT);

   
   
    //Set of tests to ensure the user input is valid

	// -1 is not a valid town
	assert(get_local_time(-1, 1, 1, 0) == INVALID_INPUT);

	// 14 is not a valid town
	assert(get_local_time(14, 1, 1, 0) == INVALID_INPUT);

	// 0 is not a valid month
	assert(get_local_time(TOWN_SYDNEY, 0, 1, 0) == INVALID_INPUT);

	// 13 is not a valid month
	assert(get_local_time(TOWN_SYDNEY, 13, 1, 0) == INVALID_INPUT);

	// 0 is not a valid day
	assert(get_local_time(TOWN_SYDNEY, 1, 0, 0) == INVALID_INPUT);

	// 32 is not a valid day
	assert(get_local_time(TOWN_SYDNEY, 1, 32, 0) == INVALID_INPUT);

	// February 29th is not a valid date
	assert(get_local_time(TOWN_SYDNEY, 2, 29, 0) == INVALID_INPUT);

	// April 31st is not a valid date
	assert(get_local_time(TOWN_SYDNEY, 4, 31, 0) == INVALID_INPUT);

	// -1 is not a valid time
	assert(get_local_time(TOWN_SYDNEY, 1, 1, -1) == INVALID_INPUT);

	// 2360 is not a valid time
	assert(get_local_time(TOWN_SYDNEY, 1, 1, 2360) == INVALID_INPUT);

	// 2400 is not a valid time
	assert(get_local_time(TOWN_SYDNEY, 1, 1, 2400) == INVALID_INPUT);

	// 1860 is not a valid time
	assert(get_local_time(TOWN_SYDNEY, 1, 1, 1860) == INVALID_INPUT);



	//Testing each timezone works

	// Australian Western Standard Time
	assert(get_local_time(TOWN_PERTH, 3, 15, 1130) == 1930);

	// Australian Central Western Standard Time
	assert(get_local_time(TOWN_EUCLA, 8, 22, 815) == 1700);

	// Australian Central Standard Time
	assert(get_local_time(TOWN_ADELAIDE, 5, 9, 1700) == 230);

	// Australian Central Daylight Time
	assert(get_local_time(TOWN_BROKEN_HILL, 2, 1, 1400) == 30);

	// Australian Eastern Standard Time
	assert(get_local_time(TOWN_HOBART, 7, 7, 1930) == 530);

	// Australian Eastern Daylight Time
	assert(get_local_time(TOWN_MELBOURNE, 11, 26, 2300) == 1000);

	// Lord Howe Standard Time
	assert(get_local_time(TOWN_LORD_HOWE_IS, 4, 16, 1000) == 2030);

	// Lord Howe Daylight Time
	assert(get_local_time(TOWN_LORD_HOWE_IS, 12, 29, 1500) == 200);

	// NZ Standard Time
	assert(get_local_time(TOWN_WELLINGTON, 7, 13, 1900) == 700);

	// NZ Daylight Time
	assert(get_local_time(TOWN_AUCKLAND, 1, 22, 630) == 1930);
	
	// Extra test for Brisbane 
	assert(get_local_time(TOWN_BRISBANE, 7, 14, 45) == 1045);

	// Extra test for Darwin
	assert(get_local_time(TOWN_EUCLA, 12, 31, 730) == 1700);

	// Extra test for Perth
	assert(get_local_time(TOWN_EUCLA, 8, 1, 2320) == 720);
	
	
	
    //Testing edge cases for when daylight savings starts and ends


	// Eastern Timezones
	
	// Before AEST Begins
	assert(get_local_time(TOWN_CANBERRA, 3, 31, 1559) == 259);

	// After AEST Begins
	assert(get_local_time(TOWN_SYDNEY, 3, 31, 1600) == 200);

	// Before AEDT Begins
	assert(get_local_time(TOWN_MELBOURNE, 10, 6, 1559) == 159);

	// After AEDT Begins
	assert(get_local_time(TOWN_HOBART, 10, 6, 1600) == 300);

	//Lord Howe Island Timezones

	// Before LHST Begins
	assert(get_local_time(TOWN_LORD_HOWE_IS, 3, 31, 1459) == 159);

	// After LHST Begins
	assert(get_local_time(TOWN_LORD_HOWE_IS, 3, 31, 1500) == 130);

	// Before LHDT Begins
	assert(get_local_time(TOWN_LORD_HOWE_IS, 10, 6, 1529) == 159);

	// After LHDT Begins
	assert(get_local_time(TOWN_LORD_HOWE_IS, 10, 6, 1530) == 230);

	//Central Timezones

	// Before ACST Begins
	assert(get_local_time(TOWN_ADELAIDE, 3, 31, 1629) == 259);

	// After ACST Begins
	assert(get_local_time(TOWN_BROKEN_HILL, 3, 31, 1630) == 200);

	// Before ACDT Begins
	assert(get_local_time(TOWN_BROKEN_HILL, 10, 6, 1629) == 159);

	// After ACDT Begins
	assert(get_local_time(TOWN_ADELAIDE, 10, 6, 1630) == 300);

	//New Zealand Timezones

	// Before NZST Begins
	assert(get_local_time(TOWN_AUCKLAND, 3, 31, 1359) == 259);

	// After NZST Begins
	assert(get_local_time(TOWN_WELLINGTON, 3, 31, 1400) == 200);

	// Before NZDT Begins
	assert(get_local_time(TOWN_AUCKLAND, 10, 6, 1359) == 159);

	// After NZDT Begins
	assert(get_local_time(TOWN_CHRISTCHURCH, 10, 6, 1400) == 300);
	
	
    // you should add at least 40 more assert statements to this function
    // with a comment for each test explaining it

    // there should be comment before this function
    // explaining your overall testing strategy
}
