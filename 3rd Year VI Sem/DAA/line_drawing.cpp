#include <iostream>
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
        std::cout << "(" << round(x) << ", " << round(y) << ")" << std::endl;
        x += xIncrement;
        y += yIncrement;
    }
}

int main() {
    int x0 = 100, y0 = 100, x1 = 200, y1 = 200;
    drawLine(x0, y0, x1, y1);
    return 0;
}
