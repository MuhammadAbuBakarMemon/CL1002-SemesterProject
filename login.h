#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "voter.h"

void logIn()
{
    char logCNIC[14];
    char logPIN[6];

    printf("Enter CNIC: ");
    scanf("%13s", logCNIC);
    printf("Enter PIN: ");
    scanf("%5s", logPIN);

    FILE *fl = fopen("voters.csv", "r");
    if (fl == NULL)
    {
        printf("Error opening voters.csv for reading!\n");
        return;
    }

    char fileCNIC[14];
    char filePIN[6];
    int found = 0;

    // Read each line using fscanf
    while (fscanf(fl, "%13[^,],%5[^\n]\n", fileCNIC, filePIN) == 2)
    {
        if (strcmp(logCNIC, fileCNIC) == 0 && strcmp(logPIN, filePIN) == 0)
        {
            found = 1;
            break;
        }
    }

    fclose(fl);

    if (found)
    {
        printf("Login successful!\n");
    }
    else
    {
        printf("Invalid CNIC or PIN!\n");
    }
}
#endif