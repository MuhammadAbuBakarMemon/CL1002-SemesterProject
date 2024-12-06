#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void feedback()
{
    char response;

    printf("Would you like to provide feedback on the election process? (y/n): ");
    scanf(" %c", &response);

    response = tolower(response);
    if (response == 'y')
    {
        FILE *feedbackFile = fopen("feedback.txt", "a+");
        if (feedbackFile == NULL)
        {
            printf("Error: Unable to open feedback file.\n");
            printf("Exiting the adding feedback page/option.\n");
            return;
        }

        char feedbackText[500];
        printf("Please provide your feedback: ");

        getchar();
        
        fgets(feedbackText, sizeof(feedbackText), stdin);
        feedbackText[strcspn(feedbackText, "\n")] = '\0';

        fprintf(feedbackFile, "Feedback for Portal: %s\n", feedbackText);
        fclose(feedbackFile);
        printf("Thank you for your feedback!\n");
    }
    else
    {
        printf("No feedback provided. Thank you for voting!\n");
    }
}

#endif