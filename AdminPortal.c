
#include <stdio.h>
#include <string.h>

struct Admin
{
    char u_name[30];
    int p_code;
};

void AdminPortal()
{

    FILE *fptr;
    fptr = fopen("AdminCredentils.csv", "r")

    if (fptr == NULL)
    {
        printf("File could not be found. A third party might have messed up with your files.\n");
        return 0;
    }

    struct Admin ad[20];

    int iterator = 0;

    while (!feof(fl))
    {
        if (fscanf(fptr, "%20s %d", ad[iterator].u_name, ad[iterator].p_code))
        {
            iterator++;
        }
    }

    fclose(fptr);
    
    int flag = 0;
    char u_name[30];
    int p_code = 0;

    pritnf("Please enter your username: \n");
    fgets(u_name, sizeof(u_name), stdin);

    printf("please enter your pasword: \n");
    scanf("%d", &p_code);

    for (int m = 0; m < count; m++)
    {
        if ( (strcmp(u_name, ad[m].u_name) == 0) && (p_code == ad[m].p_code) )
        {
            printf("Admin Credentials matched and verified, You have successfully logged in.\n");
            flag = 1;
            break;
        }
        else
        {
            printf("The credentials you entered are incorrect....\n");
        }
    }

    if (flag == 1)
    {
        
    }



}
