
#include <GL/gl.h>
#include<windows.h>
#ifdef APPLE
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>
//float p=-10.0; // Display Measurement with ortho starting from the left -10 and right 10
float p=6.0;
void drawCircle(int h, int k, int rx, int ry)
{
    glColor3f(0.0, 1.0, 0.0);  // Yellow color (1.0, 1.0, 1.0 is White)
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        // Corrected the line by replacing non-breaking spaces
        // The angle needs to be in radians for sin/cos
        float angle = 3.14159 * i / 180.0;
        glVertex2f(h + rx * cos(angle), k + ry * sin(angle));
    }
    glEnd();
}
void display(void)
{
 glClear(GL_COLOR_BUFFER_BIT);
       if(p<=10) //moving limit with the display measurement
        p=p-.0005; // changing the object position for redisplaying
//      else
//        p=-10; // For backing the object continuously
    glutPostRedisplay(); // To redraw the object in the display



    glBegin(GL_QUADS);
    glVertex2f(p-1,3);       // To draw the object position from the left limit,p
    glVertex2f(p-1,6);
    glVertex2f(p+4,6);      // Left to right
    glVertex2f(p+4,3);
    glEnd();
    drawCircle(p+1, 3, 1, 1);
    drawCircle(p+3, 3, 1, 1);

glColor3f(0.0, 0.0, 1.0);
glBegin(GL_QUADS);

    glVertex2f(p,4);       // To draw the object position from the left limit,p
    glVertex2f(p,5);
    glVertex2f(p+1,5);      // Left to right
    glVertex2f(p+1,4);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);

    glBegin(GL_QUADS);

    glVertex2f(p+2,4);       // To draw the object position from the left limit,p
    glVertex2f(p+2,5);
    glVertex2f(p+3,5);      // Left to right
    glVertex2f(p+3,4);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);


  glFlush();
}
void init(void)
{
  glClearColor (1.0, 0.0, 0.0, 0.0); // Background Color
  glOrtho(-10.00,10.00,-10.00,10.00,-10.00,10.00); // To specify the coordinate & Specify the distances to the nearer and farther depth clipping planes.
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); //Single Frame
  glutInitWindowSize (600, 600);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("moving_object");
  init();                              // Set up constants with default values
    glutDisplayFunc(display);
  glutMainLoop();               // It enters the GLUT event processing loop.should be called at most once in a GLUT program. Once called, this routine will never return. It will call as necessary any callbacks that have been registered.
  return 0;
}
