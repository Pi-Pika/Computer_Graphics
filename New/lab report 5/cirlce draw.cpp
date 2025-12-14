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
    glutInitWindowSize(400, 400);
    glutCreateWindow("Draw Half Moon");
// registration of callbacks
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    init();
// enter the glut loop
    glutMainLoop();
}
void init()
{
    glClearColor(0, 0, 0, 1); // make bg color to black
}
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT); // clear frame color
    glLoadIdentity();
// left circle
    glColor3f(1.0f, 1.0f, 1.0f);
    circle(180, 180, 0, 0);
// right circle
    glColor3f(0.0f, 0.0f, 0.0f);
    circle(180, 180, 70, 70);
    glutSwapBuffers();
}
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400);
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
