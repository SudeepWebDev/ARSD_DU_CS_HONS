#include <iostream>
#include <graphics.h> // Ensure you have the WinBGIm library installed
#include <cmath>

void drawLine(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xIncrement = dx / (float) steps;
    float yIncrement = dy / (float) steps;

    float x = x0;
    float y = y0;
    for (int i = 0; i <= steps; i++) {
        putpixel(round(x), round(y), WHITE);
        x += xIncrement;
        y += yIncrement;
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int x0 = 100, y0 = 100, x1 = 200, y1 = 200;
    drawLine(x0, y0, x1, y1);

    getch();
    closegraph();
    return 0;
}
