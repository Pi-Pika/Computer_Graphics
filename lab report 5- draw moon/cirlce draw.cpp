#include <GL/glut.h>
#include <cmath>
void init();
void draw();
void reshape(int w, int h);
void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy);
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(300, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Draw Moon");

    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    init();

    glutMainLoop();
}
void init()
{
    glClearColor(0.05f, 0.05f, 0.2f, 1);
}
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw white circle (main moon body)
    glColor3f(1.0f, 1.0f, 0.9f);
    circle(120, 120, -20, 50);

    // Draw dark circle (shadow on moon to create crescent)
    glColor3f(0.05f, 0.05f, 0.2f);
    circle(120, 120, 50, 50);

    glutSwapBuffers();
}
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -300, 300);
    glMatrixMode(GL_MODELVIEW);
}
void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 100; i++)
    {
        float angle = 2 * M_PI * i / 100;
        float x = rx * cosf(angle);
        float y = ry * sinf(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}
