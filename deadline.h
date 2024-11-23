#ifndef DEADLINE_H
#define DEADLINE_H

#include <time.h>
#include "voter.h"

int Deadline(struct date deadline)
{
    time_t t = time(NULL);
    struct tm *current_date = localtime(&t);

    if (current_date->tm_year + 1900 < deadline.year)
    {
        return 1;
    }
    else if ((current_date->tm_year + 1900) == deadline.year)
    {
        if (current_date->tm_mon + 1 < deadline.month)
        {
            return 1;
        }
        else if (current_date->tm_mon + 1 == deadline.month)
        {
            if (current_date->tm_mday < deadline.day)
            {
                return 1;
            }
        }
    }
    return 0;
}

#endif