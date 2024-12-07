#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "voter.h"
#include "voteCaster.h"

void logIn()
{
    FILE *fl = fopen("voters.csv", "r");
    if (fl == NULL)
    {
        printf("Error opening voters.csv for reading!\n");
        return;
    }

    struct voter voters[100];
    int count = 0;

    fseek(fl, 60, SEEK_SET);
    printf("pass 1");
    // Loop to read the voter details from the file
while (!feof(fl))
    {
            printf("pass 2");

         if (fscanf(fl, "%13[^,],%30[^,],%30[^,],%02d,%10[^,],%24[^,],%24[^,],%5[^\n]\n",
                   voters[count].CNIC, voters[count].name, voters[count].Fname,
                   &voters[count].age, voters[count].date, voters[count].address.city,
                   voters[count].address.country, voters[count].PIN) == 8)
        {
            printf("pass 3");
            count++; // Increment count only when a full record is read
        }
    }

    fclose(fl);

    char logCNIC[14];
    char logPIN[6];
    int found = 0;

    printf("Enter CNIC (without dashes): ");
    scanf("%13s", logCNIC);
    printf("Enter PIN: ");
    scanf("%5s", logPIN);

    // Check if the entered CNIC and PIN match any record
    for (int i = 0; i < count; i++)
    {
        if (strcmp(logCNIC, voters[i].CNIC) == 0 && strcmp(logPIN, voters[i].PIN) == 0)
        {
            found = 1;
            printf("CNIC: %s\nName: %s\nFather's Name: %s\nAge: %02d\nDate of Birth: %s\nCity: %s\nCountry: %s\n",
                   voters[i].CNIC, voters[i].name, voters[i].Fname,
                   voters[i].age, voters[i].date, voters[i].address.city,
                   voters[i].address.country);
            break;
        }
    }

    // Print login result
    if (found)
    {
        printf("Login successful!\n");
        getchar();
        sleep(3);
        system("cls");
        castVote();
    }
    else
    {
        printf("Invalid CNIC or PIN!\n");
        sleep(2);
    }
}