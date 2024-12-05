#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Structure for admin credentials
struct Admin
{
    char u_name[30];
    int p_code;
};

// Structure for candidates
typedef struct candidate
{
    int election_ID;
    char CandidateName[30];
    char Party_name[30];
    float votes_accumulated;
    char seat_no[50]; // Seat in the national assembly (e.g., NA-247)
} can;

// Function to trim leading and trailing spaces from a string
void trim(char *str)
{
    char *end;

    // Trim leading spaces
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0) // If the string is empty
        return;

    // Trim trailing spaces
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    *(end + 1) = 0;
}

// Function for the admin portal
void AdminPortal()
{
    FILE *fptr;
    fptr = fopen("AdminCredentials.csv", "a+");

    if (fptr == NULL)
    {
        printf("File could not be found. A third party might have messed up with your files....\n");
        return; // Exit if the file can't be opened
    }

    fseek(fptr, 0, SEEK_END);
    if (ftell(fptr) == 0)
    {
        // File is empty, writing default credentials
        fprintf(fptr, "AbuBakar,1223\n");
        printf("Default credentials added successfully.\n");
    }
    fclose(fptr); // Close after checking and writing if necessary

    struct Admin ad[20];
    int iterator = 0;

    // Reopen file in read mode to load admin data
    fptr = fopen("AdminCredentials.csv", "r");
    if (fptr == NULL)
    {
        printf("Error reopening the file to read admin data.\n");
        return;
    }

    while (fscanf(fptr, "%29[^,],%d", ad[iterator].u_name, &ad[iterator].p_code) == 2)
    {
        trim(ad[iterator].u_name); // Trim spaces from read data
        iterator++;
    }

    fclose(fptr);

    int flag = 0;
    char u_name[30];
    int p_code = 0;
    getchar();
    // User input for authentication
    printf("Please enter your username: ");
    fgets(u_name, sizeof(u_name), stdin);
    u_name[strcspn(u_name, "\n")] = '\0'; // Remove trailing newline
    trim(u_name);                         // Trim spaces from user input

    printf("Please enter your password: ");
    if (scanf("%d", &p_code) != 1)
    {
        printf("Invalid input. Please enter a valid number for the password.\n");
        while (getchar() != '\n')
            ; // Clear the input buffer
        return;
    }

    // Authenticate the user
    for (int m = 0; m < iterator; m++)
    {
        if ((strcmp(u_name, ad[m].u_name) == 0) && (p_code == ad[m].p_code))
        {
            printf("Admin Credentials matched and verified, you have successfully logged in.\n");
            flag = 1;
            break;
        }
    }

    if (!flag)
    {
        printf("The credentials you entered are incorrect....\n");
        return;
    }

    int expected_Candidates = 0;
    int total_candidates_count = 0;
    struct candidate *ptr;

    fptr = fopen("CandidateDetails.csv", "r");
    if (fptr == NULL)
    {
        printf("File does not exist because you're probably making the first candidate's entry.\n");
        printf("Creating the file.\n");
        fptr = fopen("CandidateDetails.csv", "w");
        if (fptr == NULL)
        {
            printf("Error creating the file.\n");
            return;
        }
        fclose(fptr); // Close after creating the file
    }
    else
    {
        fptr = fopen("CandidateDetails.csv", "a+");
        if (fptr == NULL)
        {
            printf("Error reopening the file for reading and writing.\n");
            return;
        }

        printf("Please enter the number of expected candidates to register. Don't worry if the estimation is off; we can reallocate the memory in our database.\n");
        printf("Candidates: ");
        if (scanf("%d", &expected_Candidates) != 1)
        {
            printf("Invalid input! Please enter a valid number.\n");
            fclose(fptr);
            return;
        }

        // Allocate memory for the candidates dynamically
        ptr = (can *)malloc(expected_Candidates * sizeof(can));
        if (ptr == NULL)
        {
            printf("Insufficient memory to create a chunk of the structure for the required size dynamically.\n");
            printf("Exiting Program.\n");
            fclose(fptr);
            return;
        }

        // Read candidates from the file
        while (fscanf(fptr, "%d,%29[^,],%29[^,],%f,%49[^\n]", &ptr[total_candidates_count].election_ID,
                      ptr[total_candidates_count].CandidateName, ptr[total_candidates_count].Party_name,
                      &ptr[total_candidates_count].votes_accumulated, ptr[total_candidates_count].seat_no) == 5)
        {
            trim(ptr[total_candidates_count].CandidateName);
            trim(ptr[total_candidates_count].Party_name);
            trim(ptr[total_candidates_count].seat_no);
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
        printf("Enter Option: ");
        if (scanf("%d", &option) != 1)
        {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (option)
        {
        case 1:
        {
            if (total_candidates_count >= expected_Candidates)
            {
                printf("Reallocation of memory is required to add more candidates.\n");
                printf("Now, based on the number of registrations, please augment the number of candidates: ");
                if (scanf("%d", &expected_Candidates) != 1)
                {
                    printf("Invalid input! Please enter a valid number.\n");
                    continue;
                }

                can *temp = realloc(ptr, expected_Candidates * sizeof(can));
                if (temp == NULL)
                {
                    printf("Insufficient memory.\n");
                    printf("Exiting Program.\n");
                    free(ptr);
                    return;
                }
                ptr = temp;
            }

            // Collect candidate details
            printf("Please enter the Election ID: ");
            if (scanf("%d", &ptr[total_candidates_count].election_ID) != 1)
            {
                printf("Invalid input! Please enter a valid number for the Election ID.\n");
                while (getchar() != '\n')
                    ; // Clear the input buffer
                continue;
            }
            printf("Please enter the candidate's name: ");
            scanf(" %[^\n]", ptr[total_candidates_count].CandidateName);
            trim(ptr[total_candidates_count].CandidateName); // Trim spaces
            printf("Please enter the party name: ");
            scanf(" %[^\n]", ptr[total_candidates_count].Party_name);
            trim(ptr[total_candidates_count].Party_name); // Trim spaces
            printf("Please enter the seat number: ");
            scanf(" %[^\n]", ptr[total_candidates_count].seat_no);
            trim(ptr[total_candidates_count].seat_no); // Trim spaces
            ptr[total_candidates_count].votes_accumulated = 0.0;

            FILE *fp;
            fp = fopen("CandidateDetails.csv", "a+");
            if (fp == NULL)
            {
                printf("Error opening CandidateDetails.csv for writing.\n");
                free(ptr);
                return;
            }

            fprintf(fp, "%d,%s,%s,%.2f,%s\n", ptr[total_candidates_count].election_ID,
                    ptr[total_candidates_count].CandidateName, ptr[total_candidates_count].Party_name,
                    ptr[total_candidates_count].votes_accumulated, ptr[total_candidates_count].seat_no);
            fclose(fp);

            printf("\n\nCandidate entry made successfully!\n\n");
            total_candidates_count++;
            break;
        }

        case 2:
        {
            int disqualifyID = 0;
            printf("Please enter the election ID of the candidate you would like to disqualify: ");
            if (scanf("%d", &disqualifyID) != 1)
            {
                printf("Invalid input! Please enter a valid number for the election ID.\n");
                while (getchar() != '\n')
                    ; // Clear the input buffer
                continue;
            }

            FILE *o_fptr = fopen("CandidateDetails.csv", "r");
            if (o_fptr == NULL)
            {
                printf("File not found. It might have been deleted or moved.\n");
                break;
            }

            FILE *t_fptr = fopen("TemporaryCandidateDetails.csv", "w");
            if (t_fptr == NULL)
            {
                printf("Failed to create a temporary file for storing the details of the candidates.\n");
                fclose(o_fptr);
                break;
            }

            int found = 0;
            while (fscanf(o_fptr, "%d,%29[^,],%29[^,],%f,%49[^\n]", &ptr[total_candidates_count].election_ID,
                          ptr[total_candidates_count].CandidateName, ptr[total_candidates_count].Party_name,
                          &ptr[total_candidates_count].votes_accumulated, ptr[total_candidates_count].seat_no) == 5)
            {
                if (ptr[total_candidates_count].election_ID != disqualifyID)
                {
                    fprintf(t_fptr, "%d,%s,%s,%.2f,%s\n", ptr[total_candidates_count].election_ID,
                            ptr[total_candidates_count].CandidateName, ptr[total_candidates_count].Party_name,
                            ptr[total_candidates_count].votes_accumulated, ptr[total_candidates_count].seat_no);
                }
                else
                {
                    found = 1; // Candidate found for disqualification
                }
                total_candidates_count++;
            }

            fclose(o_fptr);
            fclose(t_fptr);

            if (found)
            {
                remove("CandidateDetails.csv");
                rename("TemporaryCandidateDetails.csv", "CandidateDetails.csv");
                printf("Candidate disqualified successfully.\n");
            }
            else
            {
                printf("No candidate found with the provided election ID.\n");
            }
            break;
        }

        case 3:
        {
            printf("Feature not implemented yet.\n");
            break;
        }

        case 4:
        {
            printf("Logging out...\n");
            break;
        }

        default:
            printf("Invalid option. Please select a valid menu item.\n");
            break;
        }

    } while (option != 4);

    free(ptr); // Free allocated memory before exiting
}
