#ifndef VOTER_H
#define VOTER_H

struct date
{
    int day;
    int month;
    int year;
};

struct address
{
    char city[20];
    char country[20];
};

struct voter
{
    long int CNIC;
    char name[25];
    char Fname[25];
    int age;
    struct date DoB;
    struct address address;
    int pollingStationID;
};
#endif