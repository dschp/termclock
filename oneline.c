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

void
main(void)
{
  struct tm *tm;
  char est[6], utc[6], jst[6], ltime[9], ldate[12], ldayw[4];

  struct timespec ts = {.tv_sec = 1, .tv_nsec = 0};
  do {
    time_t now = time(NULL);

    setenv("TZ", ":EST", 1);
    tm = localtime(&now);
    strftime(est, sizeof(est), "%R", tm);

    tm = gmtime(&now);
    strftime(utc, sizeof(utc), "%R", tm);

    setenv("TZ", ":Asia/Tokyo", 1);
    tm = localtime(&now);
    strftime(jst, sizeof(jst), "%R", tm);

    setenv("TZ", ":Asia/Bangkok", 1);
    tm = localtime(&now);
    strftime(ldate, sizeof(ldate), "%F", tm);
    strftime(ldayw, sizeof(ldayw), "%a", tm);
    strftime(ltime, sizeof(ltime), "%T", tm);

    printf("\033[2J\033[;1H");
    printf(BOLD " %s (%s) " RESET, ldate, ldayw);
    printf(CYAN BOLD "%s" RESET, ltime);
    printf(" EST:" YELLOW BOLD "%s" RESET, est);
    printf(" UTC:" GREEN BOLD  "%s" RESET, utc);
    printf(" JST:" RED BOLD    "%s " RESET, jst);
    fflush(stdout);
  } while (nanosleep(&ts, NULL) == 0);
}
