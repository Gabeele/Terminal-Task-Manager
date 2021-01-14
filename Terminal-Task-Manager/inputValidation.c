//PROG71985 Programing Princples 
//Assignment Group Project
//
//Gavin Abeele, Kevin McDaniel, Brayden Bowler
//
//Framework to validate any user inputs within the program

#include "inputValidation.h"


/// <summary>
/// Valdidates integers inputs (No spaces, no charaters)
/// Prompts if invalid 
/// </summary>
/// <returns>A validated integer</returns>
/// <author>Everybody</author>
int integerValidation() {

    int input;
    int scannedValues;

     do
     {
         scannedValues = scanf_s("%d", &input);

         clearStdin();

         if (scannedValues != 1) 
            printf("Invalid Input\nEnter value again: ");
         
     } while (scannedValues != 1);

    return input;

}

/// <summary>
/// Validates a date
/// </summary>
/// <param name="year">Year as an intager</param>
/// <param name="month">Month as an intager</param>
/// <param name="day">Day as an intager</param>
/// <returns>true if valid date</returns>
/// <author>Gavin</author>
bool dateValidation(int year, int month, int day) {

    if (year >= MIN_YEAR && year <= MAX_YEAR) 
    {
        if (month >= JAN && month <= DEC) 
        {
            if (day >= 1 && day <= DAY_MAX_LONG && (month == JAN || month == MAR || month == MAY || month == JUL || month == AUG || month == OCT || month == DEC))
            {
                return true;
            }
            else if (day >= 1 && day <= DAY_MAX_SHORT && (month == APR || month == JUN || month == SEP || month == NOV))
            {
                return true;

            }
            else if (day >= 1 && day <= DAY_FEB && (month == FEB)) {
                return true;
            }
            else if (day == DAY_FEB_LEAP_YEAR && month == FEB && (year % LEAP_YEAR_NO_SKIP == 0 || (year % LEAP_YEAR_GAP == 0 && year % LEAP_YEAR_SKIP !=0))) {
                return true;

            }
        }
    }
    printf("Invalid Input\n");
    return false;
   
}

/// <summary>
/// Verifies if the abort input is entered
/// </summary>
/// <param name="input">User input integer</param>
/// <returns>True if the value is abort value</returns>
/// <author>Everbody</author>
bool verifyAbortInt(int input) {

    if (input == ABORT_VALUE_INT) {
        return true;
    }

    return false;
}

/// <summary>
/// Verifies if the abort input is entered
/// </summary>
/// <param name="input">User input char</param>
/// <returns>True if the value is abort value</returns>
/// <author>Everbody</author>
bool verifyAbortChar(char input[]) {

    if ((strlen(input) == 1) && (input[0] == ABORT_VALUE_CHAR)) {
        return true;

    }

    return false;
}

/// <summary>
/// Clear out any remain characters in the stdin
/// </summary>
/// <author>Kevin</author>
void clearStdin()
{
    char tempVal;
    do
    {
        tempVal = getchar();
    } while (tempVal != '\0' && tempVal != '\n');
}