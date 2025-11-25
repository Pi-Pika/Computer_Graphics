Circle Code:
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);  // Set background to blue
    gluOrtho2D(0, 500, 0, 500);        // Set coordinate system
}

// Function to draw a circle
void drawCircle(int h, int k, int rx, int ry)
{
    glColor3f(1.0, 1.0, 1.0);  // Yellow color
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        glVertex2f(h + rx * cos(3.14159 * i / 180), k + ry * sin(3.14159 * i / 180));
    }
    glEnd();
}

// Function to draw a triangle
/*void drawTriangle(void)
{
    glColor3f(1.0, 1.0, 0.0);  // Yellow color
    glBegin(GL_TRIANGLES);
        glVertex2i(150, 150);  // Bottom-left
        glVertex2i(350, 150);  // Bottom-right
        glVertex2i(250, 300);  // Top peak
    glEnd();
}
*/
// Function to display both the circle and triangle
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);  // Clear screen (sets background to blue)

    drawCircle(250, 350, 50, 50);  // Draw the circle at (250, 350)
   // drawTriangle();                // Draw the triangle at predefined coordinates

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Circle and Triangle");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
