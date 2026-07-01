// main.c tthp [DBTow]

#include <stdio.h>
#include <string.h>

int validateDuration(const char *token);

int main(int argc, char *argv[])
{

	// Exit program if no main command is given.
	// Need to implement different more robust behavior in the future.
	if (argc < 2) {
		printf("Welcome to the tthp program.\n");
		return 0;
	}

	// Temporary validation variable
	int duration_found = 0;

	// Check the argv[1] for a valid command
	if (strcmp(argv[1], "log") == 0) {
		printf("The log command was entered.\n");
		for (int i = 2; i < argc ; i++) {
			int givenTime = validateDuration(argv[i]);
			if (givenTime > 0) {
				duration_found = 1;
				printf("A valid time format was found. Here is the total seconds: %d seconds.\n", givenTime);
			}
		}

		if (duration_found == 0) {
			printf("No valid time format was found.\n");
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
