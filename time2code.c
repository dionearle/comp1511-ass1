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
#define UTC_TIME_LIMIT 2360
#define MAX_HOURS 2400

int get_local_time(int town, int utc_month, int utc_day, int utc_time);
void run_unit_tests(void);


// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE
int is_valid_town(int town);
int is_valid_date(int utc_month, int utc_day);
int is_valid_time(int utc_time);
int choose_timezone(int town, int utc_month, int utc_day, int utc_time);
int final_output_checks(int local_time);


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

	int local_time;
	
	//Returning Invalid Input if something wrong is entered, else determining timezone
	if (is_valid_town(town) == INVALID_INPUT) {
		local_time = INVALID_INPUT;
	} else if (is_valid_date(utc_month, utc_day) == INVALID_INPUT) {
		local_time = INVALID_INPUT;
	} else if (is_valid_time(utc_time) == INVALID_INPUT) {
		local_time = INVALID_INPUT;
	} else {
		local_time = choose_timezone(town, utc_month, utc_day, utc_time);
	}

    //Checks to see if the local time to be outputted is correct. (w/ case for Eucla)
    //TEST IF SIMILAR THING NEEDS TO BE DONE FOR LORD_HOWE AND CENTRAL_TIME
    //Since their shift ends in 30 (whilst Eucla ends in 45)
	if ((local_time >= MAX_HOURS) && (town == TOWN_EUCLA)) {
        local_time = (local_time - UTC_TIME_LIMIT);
    } else {
        local_time = final_output_checks(local_time);
    }

	return local_time;
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
	} else if ((utc_time%100) >= 60) {
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
		if ((utc_month < 3) || (utc_month > 10)) {
		    output_timezone = utc_time + TIMEZONE_ACDT_OFFSET;
		} else if (((utc_month == 3) && (utc_day <= 31))
		|| ((utc_month == 10) && (utc_day >= 6))) {
		    output_timezone = utc_time + TIMEZONE_ACDT_OFFSET;       
		} else if (((utc_month == 3) && (utc_day == 31) && (utc_time < 1630))
		|| ((utc_month == 10) && (utc_day == 6) && (utc_time >= 1630))) {
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
		if ((utc_month < 3) || (utc_month > 10)) {
		    output_timezone = utc_time + TIMEZONE_AEDT_OFFSET;
		} else if (((utc_month == 3) && (utc_day <= 31))
		|| ((utc_month == 10) && (utc_day >= 6))) {
		    output_timezone = utc_time + TIMEZONE_AEDT_OFFSET;
		} else if (((utc_month == 3) && (utc_day == 31) && (utc_time < 1600))
		|| ((utc_month == 10) && (utc_day == 6) && (utc_time >= 1600))) {
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
		if ((utc_month < 3) || (utc_month > 10)) {
		    output_timezone = utc_time + TIMEZONE_LHDT_OFFSET;
		} else if(((utc_month == 3) && (utc_day <= 31))
		|| ((utc_month == 10) && (utc_day >= 6))) {
			output_timezone = utc_time + TIMEZONE_LHDT_OFFSET;
		} else if(((utc_month == 3) && (utc_day == 31) && (utc_time < 1500))
		|| ((utc_month == 10) && (utc_day == 6) && (utc_time >= 1530))) {
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
		if ((utc_month < 3) || (utc_month > 10)) {
		    output_timezone = utc_time + TIMEZONE_NZDT_OFFSET;
		} else if (((utc_month == 3) && (utc_day <= 31))
		|| ((utc_month == 10) && (utc_day >= 6))) {
		    output_timezone = utc_time + TIMEZONE_NZDT_OFFSET;
		} else if (((utc_month == 3) && (utc_day == 31) && (utc_time < 1400))
		|| ((utc_month == 10) && (utc_day == 6) && (utc_time >= 1400))) {
			output_timezone = utc_time + TIMEZONE_NZDT_OFFSET;
		} else {
			output_timezone = utc_time + TIMEZONE_NZST_OFFSET;
		}
	}

	return output_timezone;
}


int final_output_checks(int local_time) {

    //Changing the minutes if they are greater than 60
	if ((local_time % 100) >= 60) {
		local_time = local_time + 40;
	}
        
    //Changing local time if reaches the 24th hour of a day (MAX_HOURS)
    if (local_time >= MAX_HOURS) {
        local_time = (local_time - MAX_HOURS);
    }
	
	return local_time;
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
