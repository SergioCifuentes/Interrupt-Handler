#include <stdio.h>
#include <time.h>

/*
 * The result should look something like
 * Fri 2008-08-22 15:21:59 WAST
 */

int main(void)
{
    time_t     now;
    struct tm *ts;
    char       buf[80];

    /* Get the current time */
    now = time(NULL);

    /* Format and print the time, "ddd yyyy-mm-dd hh:mm:ss zzz" */
    ts = localtime(&now);
    strftime(buf, sizeof(buf), "%H:%M:%S", ts);
    puts(buf);

    return 0;
}

