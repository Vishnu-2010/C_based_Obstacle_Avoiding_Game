#include <stdio.h>      // For printf, scanf
#include <conio.h>      // For _kbhit() and _getch()
#include <windows.h>    // For gotoxy() and Sleep()
#include <time.h>       // For random seed (time)
#include <stdlib.h>     // For rand() and exit()

#define SCREEN_WIDTH 30     // Width of game area
#define SCREEN_HEIGHT 20    // Height of game area
#define MAX_ENEMIES 2       // Number of enemy cars

int carPos = SCREEN_WIDTH / 2;   // Player car starts at middle
int enemyX[MAX_ENEMIES];         // Array to store X positions of enemies
int enemyY[MAX_ENEMIES];         // Array to store Y positions of enemies
int score = 0;                  // Player score

// Function to move cursor to position (x, y)
void gotoxy(int x, int y)
{
    COORD coord;               // Structure to store coordinates
    coord.X = x;               // Set X position
    coord.Y = y;               // Set Y position
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move cursor
}

// Function to draw borders of the game
void drawBorder()
{
    // Draw top border
    for (int i = 0; i <= SCREEN_WIDTH; i++)
    {
        gotoxy(i, 0);          // Move to top row
        printf("=");           // Print horizontal line
    }

    // Draw bottom border
    for (int i = 0; i <= SCREEN_WIDTH; i++)
    {
        gotoxy(i, SCREEN_HEIGHT - 1);  // Bottom row
        printf("=");                   // Print horizontal line
    }

    // Draw side borders
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        gotoxy(0, i);          // Left side
        printf("||");          // Print vertical wall

        gotoxy(SCREEN_WIDTH - 1, i); // Right side
        printf("||");                // Print vertical wall
    }
}

// Initialize game values
void setup()
{
    srand(time(NULL));  // Seed random generator (different each run)

    // Initialize enemies
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        enemyY[i] = 0;   // Start at top
        enemyX[i] = 2 + rand() % (SCREEN_WIDTH - 4); // Random X inside borders
    }
}

// Draw everything on screen
void draw()
{
    system("cls");       // Clear screen

    drawBorder();        // Draw borders

    // Draw player car
    gotoxy(carPos, SCREEN_HEIGHT - 2); // Near bottom
    printf("A");        // Player symbol

    // Draw enemies
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        gotoxy(enemyX[i], enemyY[i]); // Enemy position
        printf("O");                  // Enemy symbol
    }

    // Display score
    gotoxy(SCREEN_WIDTH + 5, 5);  // Outside game area
    printf("Score: %d", score);
}

// Handle user input
void input()
{
    if (_kbhit())  // Check if a key is pressed
    {
        switch (_getch())  // Get pressed key
        {
        case 'a':                         // Move left
            if (carPos > 2)              // Prevent crossing left border
                carPos--;
            break;

        case 'd':                         // Move right
            if (carPos < SCREEN_WIDTH - 3) // Prevent crossing right border
                carPos++;
            break;

        case 'q':                         // Quit game
            exit(0);
        }
    }
}

// Game logic (movement + collision)
void logic()
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        enemyY[i]++;   // Move enemy downward

        // If enemy reaches bottom → respawn at top
        if (enemyY[i] >= SCREEN_HEIGHT - 1)
        {
            enemyY[i] = 0;   // Reset to top
            enemyX[i] = 2 + rand() % (SCREEN_WIDTH - 4); // New random X
            score++;         // Increase score
        }

        // Collision detection
        if (enemyY[i] == SCREEN_HEIGHT - 2 && enemyX[i] == carPos)
        {
            system("cls");   // Clear screen
            printf("\n\n\t GAME OVER!");
            printf("\n\t Final Score: %d", score);
            printf("\n\t Press any key to exit...");
            _getch();        // Wait for key press
            exit(0);         // Exit game
        }
    }
}

// Main function (entry point)
int game()
{
    setup();   // Initialize game

    // Game loop (runs forever)
    while (1)
    {
        draw();    // Draw everything
        input();   // Take input
        logic();   // Update game
        Sleep(70); // Control speed
    }

    return 0;
}
