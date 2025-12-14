// Press '+' to bigger, '-' to smaller, 'r' to reset
#include <GL/freeglut.h>
#include <iostream>
float scaleFactor = 1.0f; // Initial scale
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
// Apply scaling at center
    glTranslatef(400.0f, 300.0f, 0.0f); // Move to window center first
    glScalef(scaleFactor, scaleFactor, 1.0f);
// Draw a square (centered at origin after translate)
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-50, -50);
    glVertex2f(50, -50);
    glVertex2f(50, 50);
    glVertex2f(-50, 50);
    glEnd();
    glutSwapBuffers();
}
void keyboard(unsigned char key, int x, int y)
{
    if (key == '+')
    {
        scaleFactor += 0.1f;
        std::cout << "Bigger: Scale = " << scaleFactor << std::endl;
    }
    else if (key == '-')
    {
        scaleFactor -= 0.1f;
        if (scaleFactor < 0.1f) scaleFactor = 0.1f;
        std::cout << "Smaller: Scale = " << scaleFactor << std::endl;
    }
    else if (key == 'r')
    {
        scaleFactor = 1.0f;
        std::cout << "Reset: Scale = 1.0" << std::endl;
    }
    glutPostRedisplay();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("2D Scaling - Bigger/Smaller");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
