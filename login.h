#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void logIn()
{
    char logCNIC[14], logPIN[6];

    printf("Enter CNIC(13 digits): ");
    fgets(logCNIC, sizeof(logCNIC), stdin);
    logCNIC[strcspn(logCNIC, "\n")] = '\0';

    printf("Enter PIN: ");
    fgets(logPIN, sizeof(logPIN), stdin);
    logPIN[strcspn(logPIN, "\n")] = '\0';

    FILE *fl = fopen("voters.csv", "r");
    if (fl == NULL)
    {
        printf("Error!");
        return;
    }

    char line[300];
    int found = 0;

    while (fgets(line, sizeof(line), fl))
    {
        char fileCNIC[14];
        char filePIN[6];

        sscanf(line, "%13[^,],%5[^,\n]", fileCNIC, filePIN);

        if (strcmp(logCNIC, fileCNIC) == 0 && strcmp(logPIN, filePIN) == 0)
        {
            found = 1;
            break;
        }
    }
    fclose(fl);

    if (found)
    {
        system("cls");
        sleep(1);
        printf("\nLog In Successful!\n");
    }
    else
    {
        system("cls");
        printf("\nInvalid CNIC or PIN!\n");
    }
}

#endif
