#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "voter.h"

void logIn()
{
    // Open the file for reading
    FILE *fl = fopen("voters.csv", "r");
    if (fl == NULL)
    {
        printf("Error opening voters.csv for reading!\n");
        return;
    }

    struct voter voters[100];
    int count = 0;

    fseek(fl, 60, SEEK_SET);

    // Loop to read the voter details from the file
    while (!feof(fl))
    {
        if (fscanf(fl, "%13[^,],%30[^,],%30[^,],%02d,%10[^,],%24[^,],%24[^,],%5[^\n]\n",
                   voters[count].CNIC, voters[count].name, voters[count].Fname,
                   &voters[count].age, voters[count].date, voters[count].address.city,
                   voters[count].address.country, voters[count].PIN) == 8)
        {
            count++; // Increment count only when a full record is read
        }
    }
    fclose(fl); // Close the file after reading

    // Variables for login input
    char logCNIC[14];
    char logPIN[6];
    int found = 0;

    // Prompt for user login credentials
    printf("Enter CNIC (without dashes): ");
    scanf("%13s", logCNIC); // Read CNIC input
    printf("Enter PIN: ");
    scanf("%5s", logPIN); // Read PIN input

    // Check if the entered CNIC and PIN match any record
    for (int i = 0; i < count; i++)
    {
        if (strcmp(logCNIC, voters[i].CNIC) == 0 && strcmp(logPIN, voters[i].PIN) == 0)
        {
            found = 1; // Set found to true if credentials match
            printf("CNIC: %s\nName: %s\n Father's Name: %s\nAge: %02d\nDate of Birth: %s\nCity: %s\nCountry: %s\n",
                   voters[i].CNIC, voters[i].name, voters[i].Fname,
                   voters[i].age, voters[i].date, voters[i].address.city,
                   voters[i].address.country);
            break; // Exit loop once a match is found
        }
    }

    // Print login result
    if (found)
    {
        printf("Login successful!\n");
    
        getchar();
        sleep(10);
        system("cls");
    }
    else
    {
        printf("Invalid CNIC or PIN!\n");
        sleep(2);
    }
}