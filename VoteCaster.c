#include <stdio.h>
#include <string.h>
#include <tsdbool.h>
#include <stdbool.h>

struct vote
{
    char CNIC[14];
    bool hasvoted = false; 
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
    char seat_no[50];       // seat in the national assembly (NA-247) the candidate is contesting for in the elections
} can ;


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

        printf("Below are the details of all the eligible candidates you may cast your vote to: ");
        printf("remember as a responsible citizen it is our duty to ensure that the deserving candidate with a genuiine maddate gets the National assembly's seat.\n");

        char s_no[50];

        while (getchar != '\n');

        printf("please enter the seat number up for contestation at your registered polling station: \n");
        fgets(s_no, sizeof(s_no), stdin);
        s_no[strcspn(s_no, "\n")] = '\0';

        FILE *fptr;
        // this file was was created in Adminportal.c
        fptr = fopen("CandidateDetails.csv", "r");

        if (fptr == NULL)
        {
            printf("file not found.\n");
            printf("Exiting Program.\n");
            return;
        }

        printf("Below are the candidates that are contesting for the national assembly's seat number that you specified\n");
        pritnf("Please not that if you do not see any output on the screen this means that there was an error in inputting the ")
        
        struct candidate c2;
        int flag = 0;

        // this structure was defined in Adminportal.c
        while (fscanf(fptr, "%d %29s %29s %f %49s", &c2.election_ID, c2.CandidateName, c2.Party_name, &c2.votes_accumulated, c2.seat_no) == 5)
        {
            int candidate_counter = 0;

            if (c2.seat_no == s_no)
            {

                flag = 1;

                printf("Candidate number (%d)'s details are as follow: \n", candidate_counter + 1);
                printf("The Election ID of the candidate is: %d.\n", c2.election_ID);
                printf("The Candidate Name is: %29s.\n", c2.CandidateName);
                printf("The Party the candidate {Election ID: }(%d) is associated with is: %29s\n", c2.election_ID, c2.Party_name);
                printf("The seat Number is: %49s\n", c2.seat_no);

               candidate_counter++; 
            }
        }

        fclose(fptr);

        if (!flag)
        {
            printf("You probably made as error while writing the national Assembly's seat number, because there seems to be no voter registered and contesting for the seat number {%49s}.\n", s_no);
        }

        int procede = 0;

        printf("Press 1 to prooceede to the next page is you have made your decision for voting, kindly remeber your candidate's voting ID.\n");
        if (procede = 1)
        {
            fptr = fopen("votesstorage.csv". "a+");

            if (fptr == NULL)
            {
                printf("File not found.\n");
                printf("Exiting Program.\n");
                return;
            }

            struct vote temp;
            struct vote reader;

            printf("Please enter your CNIC number: \n");
            fgets(temp.CNIC, 13, stdin);
            temp.CNIC[strcspn(temp.CNIC, "\n")] = '\0';

            while(fscanf(fptr, "%13s %d %d %c", reader.CINC, reader.hasvoted, reader.election_ID, reader.) == 4)
            {
                if (reader.CNIC == temp.CNIC)
                {
                    if (reader.CNIC == true)
                    {
                        printf("You have already voted, for this election campagin....\n");
                        pritnf("Exiting Program.\n");
                        fclose(fptr);
                        return;
                    }
                }
            }

            printf("Please enter your current residence status 'p' for inside pakistan, and 'n' for outside pakistan: ");
            printf("Please note that crrent pakistani's will have their votes counted by 1 and on the samke side an individual who is not a current pakistani resident wil have therivoted counted as 0.8 wightage.\n");
            scanf(" %c", &temp.residence);
            temp.residence = to_lower(temp.residence);

            printf("Please enter the Election Id of the candidate you have opted to cast your vote to: \n");
            scanf("%d", &temp.election_ID);

            hasvoted = true;

            fpritnf(fptr, "%13s %d %d %c", temp.CNIC, temp.hasvoted, temp.election_ID, temp.current_residence);
            fclose(fptr);

            fptr = fopen("CandidateDetails.csv", "r+");

            if (fptr == NULL)
            {
                printf("File not found.\n");
                printf("Exiting Program.\n");
                return;
            }

            struct candidate iterater;

            while (fscanf(fptr, "%d %29s %29s %f %49s", &iterater.election_ID, iterater.CandidateName, iterater.Party_name, &iterater.votes_accumulated, iterater.seat_no) == 5)
            {
                if (iterater.election_ID == temp.election_ID)
                {

                    // the below part is the implementatiuon of the feature that iverseas pakistanis may cast 
                    // their vote but at a lesser weightage to the pakistanis that currently reside in the country

                    if (temp.current_residence == 'p')
                    {
                        iterater.votes_accumulated += 1;
                        fprintf(fptr, "%d %29s %29s %f %49s", iterater.election_ID, iterater.CandidateName, iterater.Party_name, iterater.votes_accumulated, iterater.seat_no);
                    }
                    else if (temp.current_residence == 'n')
                    {
                        iterater.votes_accumulated += 0.8;
                        fprintf(fptr, "%d %29s %29s %f %49s", iterater.election_ID, iterater.CandidateName, iterater.Party_name, iterater.votes_accumulated, iterater.seat_no);    
                    }
                    else
                    {
                        printf("Invalid nationality was entered, most probably a typo from your end....\n");
                    }
                }
                else
                {
                    printf("No such candidate to vote for with the provided election ID....\n");
                }

            }

            fclose(fptr);=

        }

    }

    return 0;
   
}

int main(void)
{
    // castVote();
    return 0;
}
