#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

int x0_user, y0_user, x1_user, y1_user;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, 50, 0, 50);
    glPointSize(5.0);
}

void drawLineBresenham(int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    while (1)
    {
        glVertex2i(x0, y0);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawLineBresenham(x0_user, y0_user, x1_user, y1_user);
    glFlush();
}

int main(int argc, char** argv)
{
    printf("Enter x0 y0 x1 y1 (0-50): ");
    scanf("%d %d %d %d", &x0_user, &y0_user, &x1_user, &y1_user);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(300, 300);
    glutCreateWindow("Bresenham Line Drawing");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
