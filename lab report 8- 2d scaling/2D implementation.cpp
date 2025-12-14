#include <GL/glut.h>
#include<math.h>
#include <iostream>

float scaleFactor = 1.0f;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(400.0f, 300.0f, 0.0f);
    glScalef(scaleFactor, scaleFactor, 1.0f);

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(0, 0);

    float radius = 50.0f;
    int segments = 100;
    for(int i = 0; i <= segments; i++)
    {
        float angle = 2.0f * 3.14159f * i / segments;
        glVertex2f(radius * cos(angle), radius * sin(angle));
    }

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
    glutCreateWindow("2D Scaling - Circle");
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
