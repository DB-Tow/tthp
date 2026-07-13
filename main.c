// main.c tthp [DBTow]

#include <stdio.h>
#include <string.h>

int validateDuration(const char *token);
int validateDate(const char *token, char *formattedDate);
int validateTitle(const char *token, char *title);

int main(int argc, char *argv[])
{

	// Exit program if no main command is given.
	// Need to implement different more robust behavior in the future.
	if (argc < 2) {
		printf("Welcome to the tthp program.\n");
		return 0;
	}

	// Temporary validation variables
	int duration_found = 0;
	char date_found[11] = "";
	char title_found[100] = "";

	// Check the argv[1] for a valid command
	if (strcmp(argv[1], "log") == 0) {
		printf("The log command was entered.\n");
		for (int i = 2; i < argc ; i++) {
			int givenTime = validateDuration(argv[i]);
			if (givenTime > 0) {
				duration_found = 1;
				printf("A valid time format was found. Here is the total seconds: %d seconds.\n", givenTime);
				printf("The original time given was: %s\n", argv[i]);
			}
			if (validateDate(argv[i], date_found) == 0) {
				printf("A valid date format was found. The original date input: %s\n", argv[i]);
				printf("The newly formatted date: %s\n", date_found);
			}
			if (validateTitle(argv[i], title_found) == 0) {
				printf("A valid title was found. The title is: %s\n", title_found);
			}
		}

		if (duration_found == 0) {
			printf("No valid time format was found.\n");
		}
		if (date_found[0] == '\0') {
			printf("No valid date format was found.\n");
		}
		if (title_found[0] == '\0') {
			printf("No valid title was found.\n");
		}
	}

	else if (strcmp(argv[1], "list") == 0) {
		printf("The list command was entered.\n");
	}

	else if (strcmp(argv[1], "timer") == 0) {
		printf("The timer command was entered.\n");
	}

	else {
		printf("No recognizable command was entered.\n");
	}

	return 0;
}

// Validator Functions //

// Validate Duration Function
int validateDuration(const char *token)
{
	int total_seconds = 0;
	int offset = 0;
	int number_read;
	char character_read;

	int h_consumed, m_consumed, s_consumed;
	h_consumed = m_consumed = s_consumed = 0;

	while (sscanf(token, "%d%c%n", &number_read, &character_read, &offset) == 2) {
		if (character_read == 'h') {
			if (h_consumed == 0) {
				h_consumed = 1;
				total_seconds += (number_read * 3600);
			}
			else {
				return -1;
			}
		}

		else if (character_read == 'm') {
			if (m_consumed == 0) {
				m_consumed = 1;
				total_seconds += (number_read * 60);
			}
			else {
				return -1;
			}
		}

		else if (character_read == 's') {
			if (s_consumed == 0) {
				s_consumed = 1;
				total_seconds += (number_read);
			}
			else {
				return -1;
			}
		}

		else {
			return -1;
		}

		token += offset;
	}

	if (total_seconds > 0)
		return total_seconds;
	else
		return -1;
}

// Validate Date Function
int validateDate(const char *token, char *formattedDate)
{
	if (strlen(token) != 10)
		return -1;

	char inputDate[11];

	strncpy(inputDate, token, sizeof(inputDate) - 1);
	// Explicitly null-terminate the array
	inputDate[sizeof(inputDate) - 1] = '\0';

	for (int i = 0; i < 10; i++) {
		if (inputDate[i] == '/')
			inputDate[i] = '-';
		if ((inputDate[i] < '0' || inputDate[i] > '9') && (inputDate[i] != '-'))
			return -1;
	}
	
	int number1, number2, number3, consumedCount;
	int month, day, year;

	if (sscanf(inputDate, "%d%n-%d-%d", &number1, &consumedCount, &number2, &number3) == 3) {
		if (consumedCount == 2) {
			month = number1;
			day = number2;
			year = number3;
		}

		if (consumedCount == 4) {
			year = number1;
			month = number2;
			day = number3;
		}
	}

	else
		return -1;

	// Validating accurate date ranges 
	
	// Setting a leapYear variable. 0 indicates not a leap year. 1 indicates a leap year.
	int leapYear = 0;
	
	// Month validation check
	if (month < 1 || month > 12)
		return -1;

	// Year validation check	
	// Only accepts time logs that were tracked after the start of 2026
	if (year < 2026)
		return -1;
	// Check for leap year
	if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
		leapYear = 1;

	// Day validation check
	// Days in months array: Jan, Feb, Mar, Apr, May, Jun, July, Aug, Sep, Oct, Nov, Dec
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	// Adjust for February in leap years
	if (leapYear == 1)
		daysInMonth[1] = 29;
	// Check if it is a valid date for the given month
	if ((day < 1) || (day > daysInMonth[month - 1]))
		return -1;

	
	snprintf(formattedDate, 11, "%04d-%02d-%02d", year, month, day);

	return 0;
}

// Validate Title Function //
int validateTitle(const char *token, char *title)
{
	if (token[0] == '-' && (token[1] != '-')) {
		// Check if the input exceeds the maximum title length.
		// Maximum title length is 100 characters.

		int tokenSize = (strlen(token) - 1);
	
		// Need to make max title length a symbolic constant not a magic number
		if (tokenSize > 100) {
			return -1;
		}
		strncpy(title, (token + 1), tokenSize);

		// Explicitly null terminate the string
		title[tokenSize] = '\0';

		// Ensure title is not empty "-"
		if (strlen(title) == 0)
			return -1;
		else
			return 0;
	}
	else
		return -1;
}
