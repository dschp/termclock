#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RESET     "\033[0m"
#define BOLD      "\033[1m"
#define UNDERLINE "\033[4m"
#define BLINK     "\033[5m"
#define RED       "\033[31m"
#define GREEN     "\033[32m"
#define YELLOW    "\033[33m"
#define BLUE      "\033[34m"
#define MAGENTA   "\033[35m"
#define CYAN      "\033[36m"
#define WHITE     "\033[37m"

#define FMT_DATE  "%Y-%m-%d (%a)"
#define FMT_TIME  "%H:%M:%S"

void
main(int argc, char *argv[])
{
	struct timespec ts = {.tv_sec = 1, .tv_nsec = 0};
	struct tm *tm;
	char date_buf[20], time_buf[20];

	const char *tzs[][3] = {
		{ "Pacific/Auckland",    "Auckland",    WHITE },
		{ "Australia/Sydney",    "Sydney",      WHITE },
		{ "Asia/Tokyo",          "Tokyo",       MAGENTA },
		{ "Hongkong",            "Hong Kong",   WHITE },
		{ "Asia/Bangkok",        "Bangkok",     CYAN },
		{ "Asia/Dubai",          "Dubai",       WHITE },
		{ "Europe/Athens",       "Athens",      BLUE },
		{ "Europe/London",       "London",      WHITE },
		{ "UTC",                 "",            GREEN },
		{ "Brazil/East",         "Brazil",      WHITE },
		{ "America/New_York",    "New York",    YELLOW },
		{ "America/Chicago",     "Chicago" ,    WHITE },
		{ "America/Los_Angeles", "Los Angeles", RED },
		{ "Pacific/Honolulu",    "Hawaii",      WHITE },
	};

	do {
		printf("\033[2J\033[;1H\n");

		time_t now = time(NULL);

		for (int i = 0; i < sizeof(tzs) / sizeof(tzs[0]); i++) {
			setenv("TZ", tzs[i][0], 1);
			tm = localtime(&now);
			strftime(time_buf, sizeof(date_buf), FMT_TIME, tm);
			strftime(date_buf, sizeof(time_buf), FMT_DATE, tm);
			if (*tzs[i][1] == 0)
				printf(WHITE " %s " BOLD "%s%s" RESET "\n",
					   date_buf, tzs[i][2], time_buf );
			else
				printf(WHITE " %s " BOLD "%s%s" RESET WHITE " / %s\n",
					   date_buf, tzs[i][2], time_buf, tzs[i][1]);
		}

		printf("\n");
		fflush(stdout);
	} while (nanosleep(&ts, NULL) == 0);
}
