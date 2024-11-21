#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voter.h"

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

    printf("Enter details for voter %d:\n", *count + 1);

    printf("Enter Name: ");
    scanf("%19s", (*voters)[*count].name);

    printf("Enter Father's Name: ");
    scanf("%19s", (*voters)[*count].Fname);

    printf("Enter CNIC (13 digits): ");
    scanf("%13s", (*voters)[*count].CNIC);

    printf("Enter Age: ");
    scanf("%d", &(*voters)[*count].age);

    printf("Enter Date of Birth (day month year): ");
    scanf("%d %d %d", &(*voters)[*count].DoB.day,
          &(*voters)[*count].DoB.month, &(*voters)[*count].DoB.year);

    printf("Enter City Name: ");
    scanf("%24s", (*voters)[*count].address.city);

    printf("Enter Country Name: ");
    scanf("%24s", (*voters)[*count].address.country);

    (*count)++;
}
