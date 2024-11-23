#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "voter.h"
#include "validate.h"

void register_voter(struct voter **voters, int *count, int *capacity)
{
    if (*count >= *capacity)
    {
        *capacity *= 2;
        *voters = realloc(*voters, (*capacity) * sizeof(struct voter));
        if (*voters == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }

    struct voter *new_voter = &(*voters)[*count];

    printf("Enter details for voter %d:\n", *count + 1);

    getchar();

    printf("Enter Name: ");
    fgets(new_voter->name, sizeof(new_voter->name), stdin);
    new_voter->name[strcspn(new_voter->name, "\n")] = '\0';

    printf("Enter Father's Name: ");
    fgets(new_voter->Fname, sizeof(new_voter->Fname), stdin);
    new_voter->Fname[strcspn(new_voter->Fname, "\n")] = '\0';

    printf("Enter CNIC (13 digits): ");
    scanf("%ld", &new_voter->CNIC);

    printf("Enter Age: ");
    scanf("%d", &new_voter->age);
    if (!(validate_age(new_voter->age)))
    {
        printf("Age must be in limit i.e \"18 to 100\".");
        goto end;
    }

    printf("Enter Date of Birth (day month year): ");
    scanf("%d %d %d", &new_voter->DoB.day,
          &new_voter->DoB.month, &new_voter->DoB.year);
    if (!(validate_date(new_voter->DoB.day, new_voter->DoB.month, new_voter->DoB.year)))
    {
        printf("Invalid date");
        goto end;
    }

    printf("Enter City Name: ");
    scanf("%24s", new_voter->address.city);

    printf("Enter Country Name: ");
    scanf("%24s", new_voter->address.country);

    printf("Enter PIN(5-digits): ");
    scanf("%d", &new_voter->PIN);
    if (!(validate_PIN(new_voter->PIN)))
    {
        printf("Invalid Pin! Must be in [11111, 99999].");
        goto end;
    }

    (*count)++;
end:
}
