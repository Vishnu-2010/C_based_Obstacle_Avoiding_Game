#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
/* prototype for login function implemented in login.c */
int login(void);
/* prototype for game function implemented in game.c */
int game(void);
    

/* clear the console using WinAPI (more reliable than system("cls")) */
static void clearScreen(void)
{
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStd == INVALID_HANDLE_VALUE)
    {
        /* fallback */
        system("cls");
        return;
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hStd, &csbi))
    {
        system("cls");
        return;
    }

    DWORD cellCount = (DWORD)(csbi.dwSize.X) * (DWORD)(csbi.dwSize.Y);
    COORD homeCoords = { 0, 0 };
    DWORD count;

    FillConsoleOutputCharacterA(hStd, ' ', cellCount, homeCoords, &count);
    FillConsoleOutputAttribute(hStd, csbi.wAttributes, cellCount, homeCoords, &count);
    SetConsoleCursorPosition(hStd, homeCoords);
}

int main()
{
    /*require successful login before showing the menu */
    if (!login())
    {
        printf("Access denied. Exiting.\n");
        return 0;
    }

    int choice;
    while (1)
    {
        /* clear previous output before showing the menu */
        clearScreen();
        printf("=====================================\n");
        printf("          Turbo Zone Racing          \n");
        printf("=====================================\n");
        printf("\tStart Game\t1\n");
        printf("\tInstructions\t2\n");
        printf("\tQuit\t\t3\n");
        printf("\tCredits\t\t4\n");
        printf("-------------------------------------\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            int ch;
            /* consume the rest of the line */
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            printf("\nInvalid input! Please enter a number.\n");
            /* prompt the user so the message isn't cleared immediately */
            printf("Press Enter to continue...");
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
            game();
            break;

        case 2:
            printf("\n--- INSTRUCTIONS ---\n");
            printf("Use 'A' to turn left and 'D' to turn right.\n");
            printf("Avoid the obstacles and reach the finish line!\n\n");
            break;

        case 3:
            printf("\nThanks for playing! See you again.\n");
            exit(0);

        case 4:
            printf("\n--- CREDITS ---\n");
            printf("Game developed by:        Vishnu A S\n");
            break;
        case 5:
            secret_game();
			break;

        case 6:
            printf("\n--- SECRET CODE ---\n");
            printf("Congratulations! You've found the secret code!\n");
			printf("Here's a special message for you: Keep racing and never give up!\n\n");
            printf("Press Enter to continue...");

        default:
            printf("\nInvalid choice. Please try again.\n\n");
            break;
        }

        /* pause so the user can see the result before the menu is cleared */
        {
            int ch;
            /* consume leftover newline from scanf */
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            printf("Press Enter to continue...");
            (void)getchar();
        }
    }
    return 0;
}