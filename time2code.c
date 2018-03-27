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

int get_local_time(int town, int utc_month, int utc_day, int utc_time);
void run_unit_tests(void);


// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE
int is_valid_town(int town);
int is_valid_date(int utc_month, int utc_day);
int is_valid_time(int utc_time);
int choose_timezone(int town, int utc_month, int utc_day, int utc_time);


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
    // CHANGE THIS FUNCTION
    // YOU ARE NOT PERMITTED TO USE ARRAYS, LOOPS, PRINTF OR SCANF
    // SEE THE ASSIGNMENT SPECIFICATION FOR MORE RESTRICTIONS

	//Inside function should be various if statements to choose time offset to use
	//Should also make sure code does not break for weird cases (will test later)
	//These should later be placed into seperate functions that are called
    //Change return statement, as it only works for Sydney (AEDT offset)

	if (is_valid_town(town) == INVALID_INPUT) {
		return INVALID_INPUT;
	} else if (is_valid_date(utc_month, utc_day) == INVALID_INPUT) {
		return INVALID_INPUT;
	} else if (is_valid_time(utc_time) == INVALID_INPUT) {
		return INVALID_INPUT;
	}

	//Insert rules to determine which time zone it is (also if daylight saving or not)
	//In NSW, Daylight savings will end 3am Sunday, 1 April & begins at 2am 7th October
	//Ends: This is 1600 UTC time previous day (since NSW is +1100 DST)
	//Starts: This is 1500 UTC time 6th October (Going back one hour to normal time)

	//MAKE ANOTHER RULE SO IF UTC TIME GOES OVER 23599 GO BACK TO ZERO
	return utc_time + choose_timezone(town, utc_month, utc_day, utc_time);
}


// ADD YOUR FUNCTIONS HERE

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
    //Cases for Feb 31st etc as well as 30 days (September, April, June, November)

    return output_date;
}

int is_valid_time(int utc_time) {

	int output_time;

	//Basic test to ensure valid utc time is chosen
	if ((utc_time < 0) || (utc_time > 2359)) {
		output_time = INVALID_INPUT;
	} else if ((utc_time%100) >= 60) {
		output_time = INVALID_INPUT;
	} else {
		output_time = 0;
    }

    return output_time;
}

int choose_timezone(int town, int utc_month, int utc_day, int utc_time) {

	int output_timezone;

	//Determining what timezone offset should be added to the UTC time
	if (town == TOWN_ADELAIDE) {
		output_timezone = TIMEZONE_ACST_OFFSET; //Change!
	}
	
	if (town == TOWN_SYDNEY) {
		if ((utc_month < 3)
		|| ((utc_month = 3) && (utc_day <= 31) && (utc_time <= 1559))
		|| (utc_month > 10)
		|| ((utc_month = 10) && (utc_day >= 6) && (utc_time >= 1500))) {
			output_timezone = TIMEZONE_AEDT_OFFSET;
		} else {
			output_timezone = TIMEZONE_AEST_OFFSET;
		}
	}

	return output_timezone;
}


// ADD A COMMENT HERE EXPLAINING YOUR OVERALL TESTING STRATEGY

// run unit tests for get_local_time

void run_unit_tests(void) {
    // 2 example unit tests

    // UTC midnight on 20th March -> time in Sydney: 11am AEDT
    assert(get_local_time(TOWN_SYDNEY, 3, 20, 0) == 1100);

    // 42 is not a valid month
    assert(get_local_time(TOWN_SYDNEY, 42, 0, 0) == INVALID_INPUT);

    // ADD YOUR ASSERT STATEMENTS HERE

    // you should add at least 40 more assert statements to this function
    // with a comment for each test explaining it

    // there should be comment before this function
    // explaining your overall testing strategy
}
