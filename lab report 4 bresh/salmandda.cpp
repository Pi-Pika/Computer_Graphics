#include <GL/glut.h>
#include <cmath>
#include <iostream>

const int MIN_X = 0;
const int MAX_X = 50;
const int MIN_Y = 0;
const int MAX_Y = 50;

void drawLineBresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int x = x1, y = y1;

    glPointSize(8.0);
    glBegin(GL_POINTS);
    while (true) {
        glVertex2i(x, y);
        if (x == x2 && y == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x += sx; }
        if (e2 < dx) { err += dx; y += sy; }
    }
    glEnd();
}

void drawGrid() {
    glColor3f(0.2, 0.2, 0.2);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    for (int i = MIN_X; i <= MAX_X; i++) { glVertex2i(i, MIN_Y); glVertex2i(i, MAX_Y); }
    for (int i = MIN_Y; i <= MAX_Y; i++) { glVertex2i(MIN_X, i); glVertex2i(MAX_X, i); }
    glEnd();
}

void drawAxes() {
    glColor3f(0.5, 0.5, 0.5);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2i(MIN_X, 0); glVertex2i(MAX_X, 0);
    glVertex2i(0, MIN_Y); glVertex2i(0, MAX_Y);
    glEnd();
}

void drawRocket() {
    // Rocket body (sleeker)
    glColor3f(0.7, 0.7, 0.9);  // Light blue-gray
    drawLineBresenham(21, 15, 21, 37);  // Left side
    drawLineBresenham(29, 15, 29, 37);  // Right side
    drawLineBresenham(21, 15, 29, 15);  // Bottom
    drawLineBresenham(21, 37, 29, 37);  // Top

    // Rocket nose (sharper triangle)
    glColor3f(1.0, 0.5, 0.0);  // Orange
    drawLineBresenham(21, 37, 25, 45);  // Left side
    drawLineBresenham(29, 37, 25, 45);  // Right side
    drawLineBresenham(21, 37, 29, 37);  // Base

    // Left fin
    glColor3f(0.0, 0.6, 0.0);  // Green
    drawLineBresenham(21, 20, 16, 10);
    drawLineBresenham(21, 15, 16, 10);
    drawLineBresenham(21, 15, 21, 20);

    // Right fin
    drawLineBresenham(29, 20, 34, 10);
    drawLineBresenham(29, 15, 34, 10);
    drawLineBresenham(29, 15, 29, 20);

    // Window (larger square)
    glColor3f(0.8, 0.9, 1.0);  // Pale cyan
    drawLineBresenham(23, 28, 27, 28);
    drawLineBresenham(27, 28, 27, 32);
    drawLineBresenham(27, 32, 23, 32);
    drawLineBresenham(23, 32, 23, 28);

    // Window reflection
    glColor3f(1.0, 1.0, 0.8);
    glPointSize(6.0);
    glBegin(GL_POINTS);
    glVertex2i(24, 30);
    glVertex2i(25, 31);
    glEnd();

    // Flames
    glColor3f(1.0, 0.3, 0.0);  // Red-orange
    drawLineBresenham(23, 15, 21, 7);
    drawLineBresenham(21, 7, 24, 15);
    drawLineBresenham(24, 15, 23, 15);

    drawLineBresenham(26, 15, 27, 7);
    drawLineBresenham(27, 7, 28, 15);
    drawLineBresenham(28, 15, 26, 15);

    // Inner yellow flame highlights
    glColor3f(1.0, 1.0, 0.0);
    drawLineBresenham(23, 15, 22, 10);
    drawLineBresenham(22, 10, 24, 15);
    drawLineBresenham(26, 15, 28, 10);
    drawLineBresenham(28, 10, 27, 15);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawAxes();
    drawRocket();

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(10, 46);
    const char* title = " ";
    for (const char* c = title; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(MIN_X - 1, MAX_X + 1, MIN_Y - 1, MAX_Y + 1);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Rocket");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
