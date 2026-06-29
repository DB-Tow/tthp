// main.c tthp [DBTow]

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	// Exit program if no main command is given.
	// Need to implement different more robust behavior in the future.
	if (argc < 2) {
		printf("Welcome to the tthp program.\n");
		return 0;
	}

	// Check the argv[1] for a valid command
	if (strcmp(argv[1], "log") == 0) {
		printf("The log command was entered.\n");
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
