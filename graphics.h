include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h> // Required for the delay() function

int main() {
    int gd = DETECT, gm;
    int x, y, dx = 5, dy = 5, radius = 20;
    int maxx, maxy;

    // Initialize the graphics system
    // Change "C:\\Turboc3\\BGI" to your BGI file path if necessary
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    maxx = getmaxx(); // Get maximum x-coordinate
    maxy = getmaxy(); // Get maximum y-coordinate

    x = radius; // Initial x position
    y = radius; // Initial y position

    while (!kbhit()) { // Loop until a key is pressed
        // Draw the ball at the current position
        setcolor(RED);
        circle(x, y, radius);
        setfillstyle(SOLID_FILL, RED);
        floodfill(x, y, RED);

        // Add a delay to control animation speed
        delay(20);

        // Clear the screen for the next frame
        cleardevice();

        // Update position
        x += dx;
        y += dy;

        // Check for boundaries and change direction
        if (x + radius >= maxx || x - radius <= 0) {
            dx = -dx;
        }
        if (y + radius >= maxy || y - radius <= 0) {
            dy = -dy;
        }
    }

    closegraph(); // Close the graphics system
    return 0;
}
