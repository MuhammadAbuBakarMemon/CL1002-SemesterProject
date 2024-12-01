#include <stdio.h>
#include <string.h>

struct vote
{
    CNIC
};

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

        printf("Press 1 to prooceede to the next page is you have made your decision for voting.\n");
        if (procede = 1)
        {
            fptr = fopen("votesstorage.csv". "w");

            if (fptr == NULL)
            {
                printf("file not found.\n");
                printf("Exiting Program.\n");
                return;
            }

            printf("")
        }

    }
   
}

int main(void)
{

    return 0;
}
