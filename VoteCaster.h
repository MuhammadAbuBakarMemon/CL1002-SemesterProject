#ifndef VOTECAST_H
#define VOTECAST_H

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct vote
{
    char CNIC[14];
    bool hasvoted;
    int election_ID;
    char current_residence;
    // 'p' for in pakistan and 'n' for outside pokistan
};

typedef struct candidate
{
    int election_ID;
    char CandidateName[30];
    char Party_name[30];
    float votes_accumulated;
    char seat_no[6]; // seat in the national assembly (NA-247) the candidate is contesting for in the elections
} can;

void castVote()
{

    printf("You have suuccessfully logged in, Now proceeding towards casting your vote.\n");

    struct date t_date;

    t_date.day = 23;
    t_date.month = 12;
    t_date.year = 2024;

    if (!Deadline(t_date))
    {
        printf("The dealine for voting has passed....\n");
    }
    else
    {
        printf("You are just in time to cast your vote for this year's (2024)'s general elections.\n");

        printf("Below are the details of all the eligible candidates you may cast your vote to:\n\n ");
        printf("Remember as a responsible citizen it is our duty to ensure that the deserving candidate with a genuiine maddate gets the National assembly's seat.\n");

        char s_no[6];

        while (getchar() != '\n')
            ;

        printf("please enter the seat number up for contestation at your registered polling station: ");
        fgets(s_no, sizeof(s_no), stdin);
        s_no[strcspn(s_no, "\n")] = '\0';

        // this file was was created in Adminportal.c
        FILE *fptr = fopen("CandidateDetails.csv", "r");

        if (fptr == NULL)
        {
            printf("file not found.\n");
            printf("Exiting Program.\n");
            return;
        }
        else
        {
            printf("Below are the candidates that are contesting for the national assembly's seat number that you specified\n");
            printf("Please not that if you do not see any output on the screen this means that there was an error in loading the file.\n");
        }

        struct candidate c2;
        int flag = 0;

        // this structure was defined in Adminportal.c
        while (fscanf(fptr, "%d,%29[^,],%29[^,],%f,%5[^\n]\n", &c2.election_ID, c2.CandidateName, c2.Party_name, &c2.votes_accumulated, c2.seat_no) == 5)
        {
            int candidate_counter = 0;

            if (!strcmp(c2.seat_no, s_no))
            {

                flag = 1;

                printf("Candidate number %d's details are as follow: \n", candidate_counter + 1);
                printf("The Election ID of the candidate is: %d.\n", c2.election_ID);
                printf("The Candidate Name is: %29s.\n", c2.CandidateName);
                printf("The Party the candidate 'Election ID: %d' is associated with is: %29s\n", c2.election_ID, c2.Party_name);
                printf("The seat Number is: %5s\n", c2.seat_no);

                candidate_counter++;
            }
        }

        fclose(fptr);

        if (!flag)
        {
            printf("You probably made as error while writing the national Assembly's seat number, because there seems to be no voter registered and contesting for the seat number '%5s'.\n", s_no);
        }

        int procede = 0;

        printf("Press 1 to prooceede to the next page is you have made your decision for voting, kindly remeber your candidate's voting ID.\n");
        if (procede = 1)
        {
            fptr = fopen("votesstorage.csv", "a+");

            if (fptr == NULL)
            {
                printf("File not found.\n");
                printf("Exiting Program.\n");
                return;
            }

            struct vote temp;
            struct vote reader;

            reader.hasvoted = false;

            printf("Please enter your CNIC number: \n");
            fgets(temp.CNIC, 13, stdin);
            temp.CNIC[strcspn(temp.CNIC, "\n")] = '\0';

            while (fscanf(fptr, "%13s,%d,%d,%c\n", temp.CNIC, temp.hasvoted, temp.election_ID, temp.current_residence) == 4)
            {
                if (!strcmp(reader.CNIC, temp.CNIC))
                {
                    if (reader.CNIC)
                    {
                        printf("You have already voted, for this election campagin....\n");
                        sleep(2);
                        printf("Exiting Program...\n");
                        sleep(1);
                        fclose(fptr);
                        return;
                    }
                }
            }

            printf("Please note that crrent pakistani's will have their votes counted by 1 and on the same side an individual who is not a pakistani resident wil have their vote counted as 0.8 weightage.\n");
            printf("'p' for inside pakistan, and 'n' for outside pakistan.\n");
            printf("Enter your current residence status: ");
            scanf(" %c", &temp.current_residence);
            temp.current_residence = tolower(temp.current_residence);

            printf("Please enter the following details of the candidate you have opted to cast your vote to: \n");
            printf("Election Id: ");
            scanf("%d", &temp.election_ID);

            reader.hasvoted = true;

            fprintf(fptr, "%13s,%d,%d,%c\n", temp.CNIC, temp.hasvoted, temp.election_ID, temp.current_residence);
            fclose(fptr);

            fptr = fopen("CandidateDetails.csv", "r+");

            if (fptr == NULL)
            {
                printf("File not found.\n");
                printf("Exiting Program.\n");
                return;
            }

            struct candidate iterater;

            while (fscanf(fptr, "%d %29s %29s %f %5s", &iterater.election_ID, iterater.CandidateName, iterater.Party_name, &iterater.votes_accumulated, iterater.seat_no) == 5)
            {
                if (iterater.election_ID == temp.election_ID)
                {

                    // the below part is the implementatiuon of the feature that iverseas pakistanis may cast
                    // their vote but at a lesser weightage to the pakistanis that currently reside in the country

                    if (temp.current_residence == 'p')
                    {
                        iterater.votes_accumulated += 1;
                        fprintf(fptr, "%d %29s %29s %f %5s", iterater.election_ID, iterater.CandidateName, iterater.Party_name, iterater.votes_accumulated, iterater.seat_no);
                    }
                    else if (temp.current_residence == 'n')
                    {
                        iterater.votes_accumulated += 0.8;
                        fprintf(fptr, "%d %29s %29s %f %5s", iterater.election_ID, iterater.CandidateName, iterater.Party_name, iterater.votes_accumulated, iterater.seat_no);
                    }
                    else
                    {
                        printf("Invalid Residency was entered, most probably a typo from your end...\n");
                        sleep(1);
                    }
                }
                else
                {
                    printf("No such candidate to vote for with the provided election ID...\n");
                    sleep(1);
                }
            }

            fclose(fptr);
        }
    }

    return;
}

#endif
