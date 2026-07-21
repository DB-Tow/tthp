#ifndef LOG_H
#define LOG_H


#define MAX_COMMENTS 10
#define COMMENT_LENGTH 501
#define TITLE_LENGTH 101
#define CATEGORY_LENGTH 101
#define DATE_LENGTH 11

struct logData {
	int seconds_logged;
	char date[DATE_LENGTH];
	char title[TITLE_LENGTH];
	char comments[MAX_COMMENTS][COMMENT_LENGTH];
	int comment_count;
	char category[CATEGORY_LENGTH];
};

#endif
