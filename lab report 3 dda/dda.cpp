#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int x0_user, y0_user, x1_user, y1_user;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, 50, 0, 50);
    glPointSize(5.0);
}

void drawLineDDA(int x0, int y0, int x1, int y1)
{
    float dx = x1 - x0;
    float dy = y1 - y0;
    float steps = fabsf(dx) > fabsf(dy) ? fabsf(dx) : fabsf(dy);
    float xInc = dx / steps;
    float yInc = dy / steps;
    float x = x0;
    float y = y0;

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    for (int k = 0; k <= steps; k++)
    {
        glVertex2i((int)roundf(x), (int)roundf(y));
        x += xInc;
        y += yInc;
    }
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawLineDDA(x0_user, y0_user, x1_user, y1_user);
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
    glutCreateWindow("DDA Line Drawing");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
