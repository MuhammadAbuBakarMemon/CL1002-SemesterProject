#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "voter.h"
#include "login.h"
#include "register_voter.h"
#include <time.h>

int main()
{
    int count = 0;
    int capacity = 1;
    struct voter *voters = malloc(capacity * sizeof(struct voter));

    if (voters == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    int choice;
    while (1)
    {
        system("cls");
        printf("\n--- Voting System ---\n");
        printf("1. Register as a New Voter\n");
        printf("2. Log In\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            system("cls");
            printf("------Registration------\n");
            register_voter(&voters, &count, &capacity);
            break;
        case 2:
            system("cls");
            printf("------Log-In------\n");
            logIn();
            break;
        case 3:
            system("cls");
            sleep(2);
            printf("Exiting the system. Goodbye!\n");
            free(voters);
            return 0;
        default:
            system("cls");
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
