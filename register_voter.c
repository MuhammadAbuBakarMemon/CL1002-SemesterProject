
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "voter.h"
#include "validate.h"

void register_voter(struct voter **voters, int *count, int *capacity)
{
    struct date deadline = {29, 11, 2025};
    if (!Deadline(deadline))
    {
        printf("Registration is closed. Deadline has passed.\n");
        sleep(3);
        return;
    }

    if (*count >= *capacity)
    {
        *capacity *= 2;
        struct voter *temp = realloc(*voters, (*capacity) * sizeof(struct voter));
        if (temp == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }
        *voters = temp;
    }

    struct voter *new_voter = &(*voters)[*count];

    getchar();

    printf("Enter Name: ");
    if (fgets(new_voter->name, sizeof(new_voter->name), stdin) == NULL)
    {
        printf("Error reading name.\n");
        return;
    }
    new_voter->name[strcspn(new_voter->name, "\n")] = '\0';

    printf("Enter Father's Name: ");
    if (fgets(new_voter->Fname, sizeof(new_voter->Fname), stdin) == NULL)
    {
        printf("Error reading father's name.\n");
        return;
    }
    new_voter->Fname[strcspn(new_voter->Fname, "\n")] = '\0';

    bool cnicValidated = false;
    int attempts = 3;
    while (attempts > 0)
    {
        printf("\nEnter your CNIC (without dashes): ");
        fgets(new_voter->CNIC, sizeof(new_voter->CNIC), stdin);
        new_voter->CNIC[strcspn(new_voter->CNIC, "\n")] = '\0';

        cnicValidated = validate_CNIC(new_voter->CNIC);
        if (cnicValidated == false)
        {
            printf("Invalid CNIC!\n");
            attempts--;

            if (attempts > 0)
            {
                printf("You have %d attempt(s) remaining.\n", attempts);
            }
            else
            {
                printf("Wrong input. No attempts left.\n");
                return;
            }
        }
        else
        {
            cnicValidated = true;
            break;
        }
    }

    FILE *fp = fopen("voters.csv", "r");
    if (fp != NULL)
    {
        char line[300];
        while (fgets(line, sizeof(line), fp))
        {
            char existing_CNIC[14];
            sscanf(line, "%13[^,]", existing_CNIC);
            if (strcmp(existing_CNIC, new_voter->CNIC) == 0)
            {
                printf("CNIC is already registered.\n");
                sleep(2);
                fclose(fp);
                return;
            }
        }
        fclose(fp);
    }

    printf("Enter Age: ");
    scanf("%d", &new_voter->age);
    if (!validate_age(new_voter->age))
    {
        printf("Age must be in limit i.e \"18 to 100\".\n");
        return;
    }

    printf("Enter Date of Birth (day month year): ");
    scanf("%d %d %d", &new_voter->DoB.day, &new_voter->DoB.month, &new_voter->DoB.year);
    if (!validate_date(new_voter->DoB.day, new_voter->DoB.month, new_voter->DoB.year))
    {
        printf("Invalid date!\n");
        return;
    }

    printf("Enter City Name: ");
    scanf("%24s", new_voter->address.city);

    printf("Enter Country Name: ");
    scanf("%24s", new_voter->address.country);

    printf("Enter PIN(5-digits): ");
    scanf("%5s", new_voter->PIN);
    if (!validate_PIN(new_voter->PIN))
    {
        printf("Invalid Pin! Must be in [11111, 99999].\n");
        return;
    }

    fp = fopen("voters.csv", "a+");
    if (fp == NULL)
    {
        printf("There is an error opening the file!\n");
        return;
    }
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0)
    {
        fprintf(fp, "CNIC,Name,Father's Name,Age,Date of Birth,City,Country,PIN\n");
    }
    fprintf(fp, "%s,%s,%s,%d,%02d/%02d/%04d,%s,%s,%s\n",
            new_voter->CNIC,
            new_voter->name,
            new_voter->Fname,
            new_voter->age,
            new_voter->DoB.day, new_voter->DoB.month, new_voter->DoB.year,
            new_voter->address.city,
            new_voter->address.country,
            new_voter->PIN);
    fclose(fp);
    (*count)++;
    sleep(1);
    printf("\n\nRegistration Successful!\n\n");
    sleep(2);
}
