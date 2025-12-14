#include <GL/glut.h>
#include <math.h>
void drawRectangle(float x, float y, float w, float h)
{
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}
void drawCircle(float cx, float cy, float r)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        float theta = i * 3.1416 / 180;
        glVertex2f(cx + r * cos(theta), cy + r * sin(theta));
    }
    glEnd();
}
void drawSun()
{
    glColor3f(1, 1, 0);
// Rays
    glColor3f(1, 0.9, 0);
    for (int i = 0; i < 12; i++)
    {
        glPushMatrix();
        glTranslatef(0.6, 0.55, 0);
        glRotatef(i * 30, 0, 0, 1);
        glBegin(GL_LINES);
        glVertex2f(0, 0);
        glVertex2f(0.18, 0);
        glEnd();
        glPopMatrix();
    }
    drawCircle(0.6, 0.55, 0.10);
}
void drawTree(float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
// Leaves
    glColor3f(0.0, 0.5, 0.0);
    drawTriangle(-0.03, 0, 0.03, 0, 0, 0.25);
// Trunk
    glColor3f(0.5, 0.2, 0.1);
    drawRectangle(-0.01, -0.1, 0.02, 0.1);
    glPopMatrix();
}
void drawFlower(float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(1, 0, 0);
    drawCircle(0.03, 0.03, 0.02);
    drawCircle(-0.03, 0.03, 0.02);
    drawCircle(0.03, -0.03, 0.02);
    drawCircle(-0.03, -0.03, 0.02);
    glColor3f(1, 1, 0);
    drawCircle(0, 0, 0.02);
    glColor3f(0, 0.6, 0);
    drawRectangle(-0.01, -0.1, 0.02, 0.1);
    glPopMatrix();
}
void drawBigTree(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1);
// Leaves (bigger)
    glColor3f(0.0, 0.5, 0.0);
    drawTriangle(-0.06, 0, 0.06, 0, 0, 0.45);
// Trunk
    glColor3f(0.5, 0.2, 0.1);
    drawRectangle(-0.02, -0.15, 0.04, 0.15);
    glPopMatrix();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);// Background sky
    glColor3f(0.52, 0.80, 0.98);
    drawRectangle(-1, -1, 2, 2);
// Mountains
    glColor3f(0.8, 0.6, 0.3);
    drawTriangle(-1, -0.3, -0.4, 0.5, 0.2, -0.3);
    drawTriangle(-0.2, -0.3, 0.3, 0.6, 0.8, -0.3);
// Sun
    drawSun();
// House body
    glColor3f(1, 0.8, 0);
    drawRectangle(-0.4, -0.6, 0.8, 0.5);
// Roof
    glColor3f(0.9, 0.2, 0.2);
    drawTriangle(-0.45, -0.1, 0.45, -0.1, 0, 0.3);
// Door
    glColor3f(1, 0.3, 0.1);
    drawRectangle(-0.08, -0.6, 0.16, 0.3);
// Windows
    glColor3f(0, 0.6, 1);
    drawRectangle(-0.32, -0.35, 0.20, 0.18);
    drawRectangle(0.12, -0.35, 0.20, 0.18);// Big Trees
    drawBigTree(-0.55, -0.35, 1.5); // Left big tree
    drawBigTree(0.55, -0.35, 1.5); // Right big tree
// Small Trees on right
    drawTree(0.75, -0.4);
    drawTree(0.90, -0.4);
    drawTree(1.05, -0.4);
// Small Tree on left
    drawTree(-0.8, -0.4);
// Flowers
    drawFlower(-0.55, -0.65);
    drawFlower(-0.38, -0.65);
    glFlush();
}
void init()
{
    glClearColor(1, 1, 1, 1); // White background
    gluOrtho2D(-1, 1, -1, 1);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Scenery using Primitives & 2D Transformations");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
