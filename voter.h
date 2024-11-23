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
    char city[25];
    char country[25];
};

struct voter
{
    long int CNIC;
    char name[31];
    char Fname[31];
    int age;
    struct date DoB;
    struct address address;
    int pollingStationID;
    int PIN;
};

void register_voter(struct voter **voters, int *count, int *capacity);
int validate_CNIC(const char *cinc);

#endif