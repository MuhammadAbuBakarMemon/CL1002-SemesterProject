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

        fptr = fopen("CandidateDetails.csv", "r");

        if (fptr == NULL)
        {
            printf("File does not exist because you're probably making the first candidate's entry.\n");
            printf("Creating the file.\n");
            fptr = fopen("CandidateDetails.txt", "w");

            if (fptr == NULL)
            {
                printf("Error creating the file.\n");
                return 0;
            }

            fclose(fptr);
        }
        else
        {

            fptr = fopen("CandidateDetails.csv", "r+");

            int expected_Candidates = 0;
            int total_candidates_count = 0;

            struct Candidate *ptr;

            printf("Please enter the number of expected candidates to register, don't worry as of now, if the estimation is off and more or less candidates register in the end. We can reallocate the memory in our database.\n");
            scanf("%d", &expected_Candidates);

            ptr = (can *) malloc(expected_Candidates * (sizeof(can)));

            if (ptr == NULL)
            {
                printf("Insufficient memory to create a chunk of the structure for the reqquired size dynamically.\n");
                printf("Exiting Program.\n");
                return;
            }

            while (fscanf(fptr, "%d %29s %29s %f %49s", &ptr[total_candidates_count].election_ID, ptr[total_candidates_count].CandidateName, ptr[total_candidates_count].Party_name, &ptr[total_candidates_count].votes_accumulated, ptr[total_candidates_count].seat_no) == 5)
            {
                total_candidates_count++;
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
                        
                        if (total_candidates_count >= expected_Candidates)
                        {
                            printf("Reallocation of memory is required to add more candidates.\n");
                            printf("Now based on the number of registeration, Please augment the number of candidates: \n");
                            scanf("%d", &expected_Candidates);

                            can *temp;

                            temp = realloc(ptr, expected_Candidates * sizeof(can));

                            if (temp == NULL)
                            {
                                printf("Insufficient memory.\n");
                                printf("Exiting Program.\n");\

                                free(ptr);
                                return;
                            }
                            ptr = temp;

                        }

                        printf("Please enter the Election ID: ");
                        scanf("%d", &ptr[total_candidates_count].election_ID);

                        printf("Please enter the candidate's name: ");
                        scanf("%s", ptr[total_candidates_count].CandidateName);

                        printf("Please enter the party name: ");
                        scanf("%s", ptr[total_candidates_count].Party_name);

                        printf("Please enter the seat number: ");
                        scanf("%s", ptr[total_candidates_count].seat_no);

                        ptr[total_candidates_count].votes_accumulated = 0.0;

                        printf("Candidate entry made successfully.\n");

                        total_candidates_count++;
                        break;
                    }

                case 2:
                {

                    int disqualify = 0;

                    printf("Please enter the voter whom you would like to disqualify: \n");
                    scanf("%d", &disqualify);

                    FILE *fptr;
                    fptr = fopen("CandidateDetails.csv", "r+");

                    int candidate_counter = 0;

                    while (!feof(fptr))
                    {
                        candidate_counter = 
                    }

                    break;
                }
                    
                case 3:
                    break;

                case 4:
                {
                    printf("Logging out.\n");
                    printf("jazakallah for using the Online Voter System, If you have any releavnt feedback do prvide it to us. \n");
                    break;
                }

                default:
                {
                    printf("Invalid option was chosen. Please try again.\n");
                    break;
                }

            }

        } while (option != 4);

        free(ptr)
    }
}

int main() {
    AdminPortal();
    return 0;
}



