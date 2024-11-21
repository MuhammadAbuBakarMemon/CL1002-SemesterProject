#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voter.h"

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
        printf("\n--- Voting System ---\n");
        printf("1. Register as a New Voter\n");
        printf("2. Log In\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            register_voter(&voters, &count, &capacity);
            break;
        case 2:
            printf("Login feature is under development.\n");
            break;
        case 3:
            printf("Exiting the system. Goodbye!\n");
            free(voters);
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}
