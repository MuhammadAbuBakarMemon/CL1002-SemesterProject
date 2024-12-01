#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Admin
{
    char u_name[30];
    int p_code;
};


typedef struct candidate
{
    int election_ID;
    char CandidateName[30];
    char Party_name[30];
    float votes_accumulated;
    char seat_no[50];       // seat in the national assembly (NA-247) the candidate is contesting for in the elections
} can ;

void AdminPortal()
{
    FILE *fptr;
    fptr = fopen("AdminCredentils.csv", "r");

    if (fptr == NULL)
    {
        printf("File could not be found. A third party might have messed up with your files....\n");
        return;
    }

    struct Admin ad[20];
    int iterator = 0;

    while (fscanf(fptr, "%29s %d", ad[iterator].u_name, &ad[iterator].p_code) == 2)
    {
        iterator++;
    }

    fclose(fptr);

    int flag = 0;
    char u_name[30];
    int p_code = 0;


    printf("Please enter your username: \n");
    fgets(u_name, sizeof(u_name), stdin);
    u_name[strcspn(u_name, "\n")] = 0;

    printf("Please enter your password: \n");
    scanf("%d", &p_code);

    for (int m = 0; m < iterator; m++)
    {
        if ((strcmp(u_name, ad[m].u_name) == 0) && (p_code == ad[m].p_code))
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
            printf("File does not exist because you're probably making the first candidate's entry.\n");
            printf("Creating the file.\n");
            fptr = fopen("CandidateDetails.csv", "w");
            t_entries = 0;
            fclose(fptr);
        }
        else
        {
            iterator = 0;
            int expected_Candidates= 0;

            struct Candidate *ptr;
            printf("Please enter the number of expected candidates to register, don't worry as of now, if the estimation is incorrect and more/less candidates register in the end. We can reallocate the memory in our database.\n");
            scanf("%d", &expected_Candidates);

            ptr = (can *) malloc(expectd_Candidates * (sizeof(can)));
            can c = ptr;

            while (fscanf(fptr, "%d %29s %29s %f %49s", &c[iterator].election_ID, c[iterator].CandidateName, c[iterator].Party_name, &c[iterator].votes_accumulated, c[iterator].seat_no) == 5)
            {
                iterator++;
            }
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
            scanf("%d", &option);

            switch (option)
            {

                case 1:
                    {
                        
                        if (iterator >= expected_Candidates)
                        {
                            printf("Reallocation of memory is required to add more candidates.\n");
                            printf("Now based on the number of registeration, Please augment the number of candidates: \n");
                            scanf("%d", &expected_Candidates);

                            ptr = realloc(ptr, expected_Candidates * sizeof(can));

                        }

                        printf("Please enter the Election ID: ");
                        scanf("%d", &c[iterator].election_ID);

                        printf("Please enter the candidate's name: ");
                        scanf("%s", c[iterator].CandidateName);

                        printf("Please enter the party name: ");
                        scanf("%s", c[iterator].Party_name);

                        printf("Please enter the seat number: ");
                        scanf("%s", c[iterator].seat_no);

                        c[iterator].votes_accumulated = 0.0;

                        printf("Candidate entry made successfully.\n");

                        iterator++;
                        break;
                    }

                case 2:
                    break;
                case 3:
                    break;

                case 4:
                {
                    printf("Logging out.\n");
                    printf("jazakallah for using the Online Voter Sysytem, If you have any releavnt feedback do prvide it to us. \n");
                    break;
                }

                default:
                {
                    printf("Invalid option was chosen. Please try again.\n");
                    break;
                }

            }

        } while (option != 4);
    }
}

int main() {
    AdminPortal();
    return 0;
}
