
#include <stdio.h>
#include <string.h>

struct Admin
{
    char u_name[30];
    int p_code;
};

struct candidate
{
    int election_ID;
    char CandidateName[30];
    char Party_name[30];
    float votes_accumulated;
    char seat_no[50];   // seat in the national assembly (NA-247) the candidate is contesting for in the elections
};

void AdminPortal()
{

    FILE *fptr;
    fptr = fopen("AdminCredentils.csv", "r")

    if (fptr == NULL)
    {
        printf("File could not be found. A third party might have messed up with your files.\n");
        return 0;
    }

    struct Admin ad[20];

    int iterator = 0;

    while (!feof(fl))
    {
        if (fscanf(fptr, "%20s %d", ad[iterator].u_name, ad[iterator].p_code))
        {
            iterator++;
        }
    }

    fclose(fptr);
    
    int flag = 0;
    char u_name[30];
    int p_code = 0;

    pritnf("Please enter your username: \n");
    fgets(u_name, sizeof(u_name), stdin);

    printf("please enter your pasword: \n");
    scanf("%d", &p_code);

    for (int m = 0; m < count; m++)
    {
        if ( (strcmp(u_name, ad[m].u_name) == 0) && (p_code == ad[m].p_code) )
        {
            printf("Admin Credentials matched and verified, You have successfully logged in.\n");
            flag = 1;
            break;
        }
        else
        {
            printf("The credentials you entered are incorrect....\n");
        }
    }

    if (flag == 1)
    {

        int t_entries = 0;

        fptr = fopen("CandidateDetails.csv", "r");

        if (fptr == NULL)
        {
            printf("File does not exist because you're probably making th first candidate's entry.\n");
        }
        else
        {
            fptr = fopen("candidateDetials.csv", "w");
            t_entries = 0;
            fclose(fptr);
        }

        int option = 0;
        
        do 
        {
            printf("Welcome to the Admin Portal.\n");
            printf("1. Add candidate\n");
            printf("2. Disqualify candidate\n");
            printf("3. View Live Votes tally.\n");
            printf("4. Logout.\n");
            scanf("%d", option);

            switch (option) 
            {

                case 1 :
                {
                   printf("Please start providing us with the necessary details to add a candidate: \n"); 

                   printf("Please enter the Election ID Number: \n");

                   printf("Please enteer your candidate's name3: \n");

                   printf("please enter the party the respective candidate is representoing (Mention N/A for Azad Umeedwar): \n");

                   

                   printf("Please enter the seat in the national assembly the candidate is contesting for: \n");
                }
            }


        } while (option != 4)

    }



}
