#include <time.h>
#include <stdbool.h>  // Include for `bool`, `true`, `false`
#include "voter.h"

bool Deadline(struct date deadline)
{
    time_t t = time(NULL);
    struct tm *current_date = localtime(&t);

    int current_year = current_date->tm_year + 1900;
    int current_month = current_date->tm_mon + 1;
    int current_day = current_date->tm_mday;

    // Check if the current date is before the deadline
    if (current_year < deadline.year ||
        (current_year == deadline.year && current_month < deadline.month) ||
        (current_year == deadline.year && current_month == deadline.month && current_day < deadline.day))
    {
        return true;
    }

    return false;
}
