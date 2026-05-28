#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

#define EG_WIDTH 40
#define EG_HEIGHT 20
#define EG_ENEMIES 2

int eg_playerX = EG_WIDTH / 2;
int eg_enemyX[EG_ENEMIES];
int eg_enemyY[EG_ENEMIES];
int eg_points = 0;

// Move cursor to (x, y)
void eg_gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Hide cursor (for smooth visuals)
void eg_hideCursor()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize = 100;
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(h, &ci);
}

// Draw fancy borders
void eg_drawBorder()
{
    // Top
    eg_gotoxy(0, 0);
    printf("+");
    for (int i = 1; i < EG_WIDTH - 1; i++) printf("-");
    printf("+");

    // Bottom
    eg_gotoxy(0, EG_HEIGHT - 1);
    printf("+");
    for (int i = 1; i < EG_WIDTH - 1; i++) printf("-");
    printf("+");

    // Sides
    for (int i = 1; i < EG_HEIGHT - 1; i++)
    {
        eg_gotoxy(0, i); printf("|");
        eg_gotoxy(EG_WIDTH - 1, i); printf("|");
    }
}

// Initialize game
void eg_init()
{
    system("cls");  // Clear screen once

    srand((unsigned int)time(NULL));
    eg_hideCursor();

    for (int i = 0; i < EG_ENEMIES; i++)
    {
        eg_enemyY[i] = 1;
        eg_enemyX[i] = 2 + rand() % (EG_WIDTH - 6);
    }

    eg_drawBorder();
}

// Draw objects
void eg_render()
{
    // Player car
    eg_gotoxy(eg_playerX, EG_HEIGHT - 2);
    printf("<A>");

    // Enemy cars
    for (int i = 0; i < EG_ENEMIES; i++)
    {
        eg_gotoxy(eg_enemyX[i], eg_enemyY[i]);
        printf("[X]");
    }

    // Score
    eg_gotoxy(EG_WIDTH + 3, 5);
    printf("Score: %d", eg_points);
}

// Clear previous positions
void eg_clear()
{
    eg_gotoxy(eg_playerX, EG_HEIGHT - 2);
    printf("   "); // clear player (3 chars)

    for (int i = 0; i < EG_ENEMIES; i++)
    {
        eg_gotoxy(eg_enemyX[i], eg_enemyY[i]);
        printf("   "); // clear enemy
    }
}

// Handle input
void eg_controls()
{
    if (_kbhit())
    {
        int key = _getch();

        switch (key)
        {
        case 'a': // Move left
            if (eg_playerX > 2) eg_playerX--;
            break;

        case 'd': // Move right
            if (eg_playerX < EG_WIDTH - 5) eg_playerX++;
            break;

        case 'q': // Quit
            exit(0);
        }
    }
}

// Game logic
void eg_update()
{
    for (int i = 0; i < EG_ENEMIES; i++)
    {
        eg_enemyY[i]++; // Move straight down only

        // Respawn at top
        if (eg_enemyY[i] >= EG_HEIGHT - 1)
        {
            eg_enemyY[i] = 1;

            // 🎯 Smart spawn (fake tracking)
            if (rand() % 10 < 7) // 70% chance
            {
                int offset = (rand() % 5) - 2; // -2 to +2
                eg_enemyX[i] = eg_playerX + offset;

                // Keep inside borders
                if (eg_enemyX[i] < 2) eg_enemyX[i] = 2;
                if (eg_enemyX[i] > EG_WIDTH - 6) eg_enemyX[i] = EG_WIDTH - 6;
            }
            else
            {
                eg_enemyX[i] = 2 + rand() % (EG_WIDTH - 6);
            }

            eg_points++;
        }

        // Collision detection (consider width)
        if (eg_enemyY[i] == EG_HEIGHT - 2 &&
            eg_enemyX[i] >= eg_playerX &&
            eg_enemyX[i] <= eg_playerX + 2)
        {
            eg_gotoxy(10, 10);
            printf("GAME OVER! Score: %d", eg_points);
            _getch();
            exit(0);
        }
    }
}

// Main function
int secret_game()
{
    eg_init();

    while (1)
    {
        eg_clear();     // erase old frame
        eg_controls();  // input
        eg_update();    // update positions
        eg_render();    // draw new frame
        Sleep(50);      // smooth speed
    }

    return 0;
}