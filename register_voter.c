#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include "voter.h"
#include "validate.h"
#include "deadline.h"

void register_voter(struct voter **voters, int *count, int *capacity)
{
    struct date deadline = {27, 11, 2024};
    if (!Deadline(deadline))
    {
        printf("Registration is closed. Deadline has passed.");
        return;
    }

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

    getchar();

    printf("Enter Name: ");
    fgets(new_voter->name, sizeof(new_voter->name), stdin);
    new_voter->name[strcspn(new_voter->name, "\n")] = '\0';

    printf("Enter Father's Name: ");
    fgets(new_voter->Fname, sizeof(new_voter->Fname), stdin);
    new_voter->Fname[strcspn(new_voter->Fname, "\n")] = '\0';

    printf("Enter CNIC (13 digits): ");
    scanf("%13s", new_voter->CNIC);
    if (!(validate_CNIC(new_voter->CNIC)))
    {
        printf("Invalid CNIC!");
        return;
    }

    FILE *fp = fopen("voters.csv", "r");
    if (fp != NULL)
    {
        char line[300];
        while ((fgets(line, sizeof(line), fp)))
        {
            char existing_CNIC[14];
            sscanf(line, "%13[^,]", existing_CNIC);
            if (strcmp(existing_CNIC, new_voter->CNIC) == 0)
            {
                printf("CNIC is already registered.");
                fclose(fp);
            }
        }
    }
    fclose(fp);

    printf("Enter Age: ");
    scanf("%d", &new_voter->age);
    if (!(validate_age(new_voter->age)))
    {
        printf("Age must be in limit i.e \"18 to 100\".");
        return;
    }

    printf("Enter Date of Birth (day month year): ");
    scanf("%d %d %d", &new_voter->DoB.day,
          &new_voter->DoB.month, &new_voter->DoB.year);
    if (!(validate_date(new_voter->DoB.day, new_voter->DoB.month, new_voter->DoB.year)))
    {
        printf("Invalid date!");
        return;
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
        return;
    }

    (*count)++;

    fp = fopen("voters.csv", "a+");
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0)
    {
        fprintf(fp, "CNIC,Name,Father's Name,Age,Date of Birth,City,Country,PIN\n");
    }
    if (fp == NULL)
    {
        printf("There is error opening the file!");
        return;
    }
    fprintf(fp, "%s,%s,%s,%d,%02d/%02d/%04d,%s,%s,%d\n",
            new_voter->CNIC,
            new_voter->name,
            new_voter->Fname,
            new_voter->age,
            new_voter->DoB.day, new_voter->DoB.month, new_voter->DoB.year,
            new_voter->address.city,
            new_voter->address.country,
            new_voter->PIN);
    fclose(fp);
    sleep(1);
    printf("\n\nRegistration Successful!\n\n");
    sleep(2);
}