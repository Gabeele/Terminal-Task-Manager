//PROG71985 Programing Princples 
//Assignment Group Project
//
//Gavin Abeele, Kevin McDaniel, Brayden Bowler
//
//Framework to validate any user inputs within the program

#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_YEAR 9999
#define MIN_YEAR 1900
#define DAY_MAX_LONG 31
#define DAY_MAX_SHORT 30
#define DAY_FEB 28
#define DAY_FEB_LEAP_YEAR 29
#define LEAP_YEAR_GAP 4		//Delay of when leap years occurs 
#define LEAP_YEAR_SKIP 100		//Amount of years when the leap year does not occur
#define LEAP_YEAR_NO_SKIP 400		//Amount of years where the leap year does occur
#define ABORT_VALUE_INT 0
#define ABORT_VALUE_CHAR '0'

enum months { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };

int integerValidation();
bool dateValidation(int, int, int);
bool verifyAbortInt(int);
bool verifyAbortChar(char[]);
void clearStdin();

