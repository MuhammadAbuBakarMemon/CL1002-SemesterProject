#ifndef VALIDATE_H
#define VALIDATE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include<stdbool.h>
#include "voter.h"

int validate_CNIC(const char *cnic)
{
    bool flag = true; 
    int size = strlen(cnic);
    if (size == 15) {
        for (int i = 0; i < size; i++) {
            if (i == 5 || i == 13) {
                if (cnic[i] != '-') {
                    flag = false;
                    break;
                }
            } else { 
                if (!isdigit(cnic[i])) { 
                    flag = false;
                    break;
                }
            }
        }
    } else {
        flag = false;
    }
        
    return flag;
}

int validate_age(int age)
{
    return age >= 18 && age <= 100;
}

int isLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        return 1;
    }
    return 0;
}

int validate_date(int day, int month, int year)
{
    if (month < 1 || month > 12)
    {
        return 0;
    }

    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && isLeapYear(year))
    {
        days_in_month[1] = 29;
    }

    if (day < 1 || day > days_in_month[month - 1])
    {
        return 0;
    }

    return 1;
}
int validate_PIN(char *pin)
{
    int PIN = atoi(pin);
    if (PIN <= 11111 || PIN >= (99999 + 1))
    {
        return 0;
    }
}
#endif