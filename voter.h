#ifndef VOTER_H
#define VOTER_H

#include <time.h>
#include <stdbool.h>

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
    char CNIC[14];
    char name[31];
    char Fname[31];
    int age;
    struct date DoB;
    char date[21];
    struct address address;
    char PIN[6];
};

void register_voter(struct voter **voters, int *count, int *capacity);
int validate_CNIC(const char *cinc);
void logIn();
void castVote();
bool Deadline(struct date deadline);
void AdminPortal();
void feedback();

#endif