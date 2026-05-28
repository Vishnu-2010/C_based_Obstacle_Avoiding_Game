#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int login()
{
    char username[50];
    char user[50] = "admin";
    char password[50];
	char pass[50]="itsme";

    printf("Enter username: ");
    scanf("%49s", username);
    if (strcmp(username,"dev") != 0)
    {
        if (strcmp(username, user) == 0)
        {
            printf("Welcome, %s!\n", username);
        }
        else
        {
            printf("Login failed! Invalid username.\n");
            return 0;
        }
        printf("Enter password: ");
        scanf("%49s", password);

        if (strcmp(password, pass) == 0)
        {
            printf("Login successful! Welcome, %s!\n", username);
        }
        else
        {
            printf("Login failed! Invalid username or password.\n");
            return 1;
        }
    }
    return 1;
}