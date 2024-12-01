#include <stdio.h>


void CastVote()
{

    printf("You have suuccessfully logged in, Now proceeding towards casting your vote.\n");

    struct Date t_date;
    t_date.tm_date = 23;
    t_date.tm_month = 12;
    t_date.tm_year = 2024;

    if (!Deadline(t_date))
    {
        printf("The dealine for voting has passed....\n");;
    }
    else
    {
        printf("You are just in time to cast your vote for this year's (2024)'s general elections.\n");

         printf("Below are the details of all the candidates: ")


    }
   
}

int main(void)
{

    return 0;
}
