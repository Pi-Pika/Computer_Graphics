#include<windows.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

using namespace std;

float _move = 0.0f;
float _move1 = 0.0f;
float _move2 = 0.0f;
float _move3 = 0.0f;
float _move4 = 0.0f;
float _move5 = 0.0f;
float _move6 = 0.0f;
float _move7 = 0.0f;





void drawScene () {
	glClear (GL_COLOR_BUFFER_BIT);
	glClearColor (1.0,1.0,1.0,0.0);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

glPushMatrix ();
   glBegin(GL_POLYGON);
   glColor3f(0.49,1.0,1.0);
   glVertex3f(-25,0.0,0.0);
   glVertex3f(-25,11.5,0.0);
   glVertex3f(25,11.5,0.0);
   glVertex3f(25,0.0,0.0);
   glEnd();
   glPopMatrix();


   glPushMatrix();

   glTranslatef(0.8,0.8,0.0);
   glColor3f(1.0,1.0,0.0);
   glColor3f(1.0,1.0,0.0);
   glBegin(GL_POLYGON);

   for (int i=0;i<600;i++)
   {
	   float pi=3.1416;
	   float A=(i*2*pi)/100;
	   float r=0.1;
	   float x= r * cos (A);
	   float y= r * sin (A);
	   glVertex2f(x,y);


   }
   glEnd();
   glPopMatrix();


   glBegin(GL_LINES);
   glColor3f(1.0,10.,0.0);
   glVertex3f(0.8,0.8,0.0);
   glVertex3f(0.8,0.6,0.0);
   glEnd();
   glBegin(GL_LINES);
   glColor3f(1.0,1.0,0.0);
   glVertex3f(0.7,0.6,0.0);
   glEnd();
   glBegin(GL_LINES);
   glColor3f(1.0,1.0,0.0);
   glVertex3f(0.8,0.8,0.0);
   glVertex3f(0.9,0.6,0.0);
   glEnd();
   glBegin(GL_LINES);
   glColor3f(1.0,1.0,0.0);
   glVertex3f(0.8,0.8,0.0);
   glVertex3f(0.8,1.0,0.0);
   glEnd();
   glBegin(GL_LINES);
   glColor3f(1.0,1.0,0.0);
   glVertex3f(0.8,0.8,0.0);
   glVertex3f(0.9,1.0,0.0);
   glEnd();
   glBegin(GL_LINES);
   glColor3f(1.0,1.0,0.0);
   glVertex3f(0.8,0.8,0.0);
   glVertex3f(0.7,1.0,0.0);
   glEnd();
   glBegin(GL_LINES);
   glColor3f(1.0,1.0,0.0);
   glVertex3f(0.8,0.8,0.0);
   glVertex3f(1.2,1.0,0.0);
   glEnd();
   glBegin(GL_LINES);
   glColor3f(1.0,1.0,0.0);
   glVertex3f(0.8,0.8,0.0);
   glVertex3f(1.0,0.8,0.0);
   glEnd();
   glBegin(GL_LINES);
   glColor3f(1.0,1.0,0.0);
   glVertex3f(0.8,0.8,0.0);
   glVertex3f(1.0,0.6,0.0);
   glEnd();
   glBegin(GL_LINES);
   glColor3f(1.0,1.0,0.0);
   glVertex3f(0.8,0.8,0.0);
   glVertex3f(0.5,0.7,0.0);
   glEnd();
   glBegin(GL_LINES);
   glColor3f(1.0,1.0,0.0);
   glVertex3f(0.8,0.8,0.0);
   glVertex3f(0.5,0.5,0.0);
   glEnd();
   glBegin(GL_LINES);
   glColor3f(1.0,1.0,0.0);
   glVertex3f(0.8,0.8,0.0);
   glVertex3f(0.5,0.8,0.0);
   glEnd();
   glEnd();



   glPushMatrix();

   glTranslatef(_move6+0.2,0.8,0.0);
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);

   for(int i=0;i<600;i++)
   {
	   float pi=3.1416;
	   float A=(i*2*pi)/100;
	   float r=0.05;
	   float x = r * cos(A);
	   float y = r * sin (A);
	   glVertex2f(x,y);

   }
   glEnd();
   glPopMatrix();
     glPushMatrix();

   glTranslatef(_move6+0.28,0.8,0.0);
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);


   for(int i=0;i<600;i++)
   {
	   float pi=3.1416;
	   float A=(i*2*pi)/100;
	   float r=0.05;
	   float x=r * cos(A);
	   float y=r * sin(A);
	   glVertex2f(x,y);


	}
   glEnd();
   glPopMatrix();
   glPushMatrix();

   glTranslatef(_move6+0.35,0.8,0.0);
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);

   for(int i=0;i<600;i++)
   {
	   float pi=3.1416;
	   float A=(i*2*pi)/100;
	   float r=0.05;
	   float x=r * cos (A);
	   float y=r * sin (A);
	   glVertex2f(x,y);

   }
   glEnd();
   glPopMatrix();
   glPushMatrix();

   glTranslatef(_move6+0.2,0.75,0.0);
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);

   for(int i=0;i<600;i++)
   {
	   float pi=3.1416;
	   float A=(i*2*pi)/100;
	   float r=0.05;
	   float x=r * cos(A);
	   float y=r * sin(A);
	   glVertex2f(x,y);

   }
   glEnd();
   glPopMatrix();
   glPushMatrix();

   glTranslatef(_move6+0.28,0.75,0.0);
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);

   for(int i=0;i<600;i++)
   {
	   float pi=3.1416;
	   float A=(i*2*pi)/100;
	   float r=0.05;
	   float x=r * cos(A);
	   float y=r * sin(A);
	   glVertex2f(x,y);

   }
   glEnd();
   glPopMatrix();
   glPushMatrix();

   glTranslatef(_move6+0.35,0.75,0.0);
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);

   for(int i=0;i<600;i++)
   {
	   float pi=3.1416;
	   float A=(i*2*pi)/100;
	   float r=0.05;
	   float x=r * cos(A);
	   float y=r * sin(A);
	   glVertex2f(x,y);

	}
   glEnd();
   glPopMatrix();
   glPushMatrix();

   glTranslatef(_move6+0.15,0.77,0.0);
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);

   for(int i=0;i<600;i++)
   {
	   float pi=3.1416;
	   float A=(i*2*pi)/100;
	   float r=0.05;
	   float x=r * cos(A);
	   float y=r * sin(A);
	   glVertex2f(x,y);


   }
   glEnd();
   glPopMatrix();
   glPushMatrix();

   glTranslatef(_move6+0.39,0.77,0.0);
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);

   for(int i=0;i<600;i++)
   {
	   float pi=3.1416;
	   float A=(i*2*pi)/100;
	   float r=0.05;
	   float x=r * cos(A);
	   float y=r * sin(A);
	   glVertex2f(x,y);

   }
   glEnd();
   glPopMatrix();
   glPushMatrix();

   glTranslatef(_move7+0.6,0.6,0.0);
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);

   for(int i=0;i<600;i++)
   {
	   float pi=3.1416;
	   float A=(i*2*pi)/100;
	   float r=0.05;
	   float x=r * cos(A);
	   float y=r * sin(A);
	   glVertex2f(x,y);
   }
   glEnd();
   glPopMatrix();
   glPushMatrix();

   glTranslatef(_move7+0.68,0.6,0.0);
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);

   for(int i=0;i<600;i++)
   {
	   float pi=3.1416;
	   float A=(i*2*pi)/100;
	   float r=0.05;
	   float x=r * cos(A);
	   float y=r * sin(A);
	   glVertex2f(x,y);

   }
   glEnd();
   glPopMatrix();
   glPushMatrix();

   glTranslatef(_move7+0.75,0.6,0.0);
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);

   for(int i=0;i<600;i++)
   {
	   float pi=3.1416;
	   float A=(i*2*pi)/100;
	   float r=0.05;
	   float x=r * cos(A);
	   float y=r * sin(A);
	   glVertex2f(x,y);
   }
   glEnd();
   glPopMatrix();
   glPushMatrix();

   glTranslatef(_move7+0.6,0.65,0.0 );
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);

   for(int i=0;i<600;i++)
   {
	   float pi=3.1416;
	   float A=(i*2*pi)/100;
	   float r=0.05;
	   float x=r * cos(A);
	   float y=r * sin(A);
	   glVertex2f(x,y);
   }
   glEnd();
   glPopMatrix();
   glPushMatrix();

   glTranslatef(_move7+0.68,0.65,0.0);
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);

   for(int i=0;i<600;i++)
   {
	   float pi=3.1416;
	   float A=(i*2*pi)/100;
	   float r=0.05;
	   float x=r * cos(A);
	   float y=r * sin(A);
	   glVertex2f(x,y);
   }
   glEnd();
   glPopMatrix();
   glPushMatrix();

   glTranslatef(_move+0.75,0.65,0.0);
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);

   for(int i=0;i<600;i++)
   {
	       float pi=3.1416;
	   	   float A=(i*2*pi)/100;
	   	   float r=0.05;
	   	   float x=r * cos(A);
	   	   float y=r * sin(A);
	   	   glVertex2f(x,y);
   }
   glEnd();
   glPopMatrix();
   glPushMatrix();

   glTranslatef(_move+0.55,0.62,0.0);
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);

   for(int i=0;i<600;i++)
   {
	   float pi=3.1416;
	   float A=(i*2*pi)/100;
	   float r=0.05;
	   float x=r * cos(A);
	   float y=r * sin(A);
	   glVertex2f(x,y);

   }
   glEnd();
   glPopMatrix();
   glPushMatrix();

   glTranslatef(_move7+0.79,0.62,0.0);
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);

   for(int i=0;i<600;i++)
   {
	   float pi=3.1416;
	   float A=(i*2*pi)/100;
	   float r=0.05;
	   float x=r * cos(A);
	   float y=r * sin(A);
	   glVertex2f(x,y);
   }
   glEnd();
   glPopMatrix();
   glPushMatrix();

   glTranslatef(_move5,0.0f,0.0f);

   glBegin(GL_POLYGON);
   glColor3f(0.0,0.0,0.0);
   glVertex3f(0.933,0.4f,0.0);
   glVertex3f(1.0f,0.4166f,0.0);
   glVertex3f(0.966f,0.45,0.0);
   glEnd();


   glBegin(GL_POLYGON);
   glColor3f(1.0,0.0,0.0);
   glVertex3f(0.933f,0.4f,0.0);
   glVertex3f(0.966f,0.45,0.0);
   glVertex3f(0.933f,0.466f,0.0);
   glVertex3f(0.85f,0.466f,0.0);
   glVertex3f(0.883f,0.4166f,0.0);
   glEnd();


   glBegin(GL_POLYGON);
   glColor3f(0.37,0.37,0.37);
   glVertex3f(0.833f,0.4f,0.0);
   glVertex3f(0.883f,0.433f,0.0);
   glVertex3f(0.85f,0.466f,0.0);
   glEnd();


   glBegin(GL_POLYGON);
   glColor3f(0.0,0.0,0.0);
   glVertex3f(0.866f,0.466f,0.0f);
   glVertex3f(0.916f,0.466f,0.0);
   glVertex3f(0.883f,0.533f,0.0);
   glEnd();


   glBegin(GL_POLYGON);
   glColor3f(0.0,0.0,0.0);
   glVertex3f(0.9f,0.466f,0.0);
   glVertex3f(0.933f,0.466f,0.0);
   glVertex3f(0.925f,0.512f,0.0);
   glEnd();

   glPopMatrix();


   glPushMatrix();
   glBegin(GL_POLYGON);
   glColor3f(0.698,0.745,0.7098);
   glVertex3f(-1.0f,-0.33f,0.0);
   glVertex3f(1.0f,-0.33f,0.0);
   glVertex3f(1.0f,0.0f,0.0);
   glVertex3f(-1.0f,0.0f,0.0);
   glEnd();
   glPopMatrix();


   glPushMatrix();
   glBegin(GL_POLYGON);
   glColor3f(1.0,1.0,1.0);
   glVertex3f(-1.0f,-0.166f,0.0);
   glVertex3f(-0.5f,-0.166f,0.0);
   glVertex3f(-0.5f,0.13f,0.0);
   glVertex3f(-1.0f,-0.13f,0.0);
   glEnd();


   glBegin(GL_POLYGON);
   glColor3f(1.0,1.0,1.0);
   glVertex3f(-0.33f,0.166f,0.0);
   glVertex3f(0.166f,-0.166f,0.0);
   glVertex3f(0.166f,-0.13f,0.0);
   glVertex3f(-0.33f,-0.13f,0.0);
   glEnd();


   glBegin(GL_POLYGON);
   glColor3f(1.0,1.0,1.0);
   glVertex3f(0.33f,-0.166f,0.0);
   glVertex3f(0.833f,-0.166,0.0);
   glVertex3f(0.833f,-0.13f,0.0);
   glVertex3f(0.33f,-0.13f,0.0);
   glEnd();


   glBegin(GL_POLYGON);
   glColor3f(1.0,1.0,1.0);
   glVertex3f(0.833f,-0.166f,0.0);
   glVertex3f(1.0f,-0.166f,0.0);
   glVertex3f(1.0f,-0.13f,0.0);
   glVertex3f(0.833f,-0.13f,0.0);
   glEnd();
   glPopMatrix();


   glPushMatrix();
   glBegin(GL_POLYGON);
   glColor3f(0.23,0.70,0.81);
   glVertex3f(-1.0f,-1.0f,0.0);
   glVertex3f(1.0f,-1.0f,0.0);
   glVertex3f(1.0f,-0.33f,0.0);
   glVertex3f(-1.0f,-0.33f,0.0);
   glEnd();
   glPushMatrix();


   glPushMatrix();
   glBegin(GL_POLYGON);
   glColor3f(0.2,0.098,0.0);
   glVertex3f(-1.0f,-0.33f,0.0);
   glVertex3f(1.0f,-0.33f,0.0);
   glVertex3f(1.0f,-0.416f,0.0);
   glVertex3f(-1.0f,-0.416f,0.0);
   glEnd();

   glBegin(GL_POLYGON);
   glColor3f(0.0,0.0,0.0);
   glVertex3f(-1.0f,-0.35f,0.0);
   glVertex3f(1.0f,-0.35f,0.0);
   glVertex3f(1.0f,-0.33f,0.0);
   glVertex3f(-1.0f,-0.35f,0.0);
   glEnd();
   glPushMatrix();



   glPushMatrix();
   glTranslatef(_move1,0.0f,0.0f);
   glBegin(GL_POLYGON);
   glColor3f(0.0,0.56,0.698);
   glVertex3f(-1.0f,-0.5f,0.0);
   glVertex3f(-0.966f,0.416f,0.0);
   glVertex3f(-0.933f,-0.5f,0.0);
   glVertex3f(-0.9f,-0.416f,0.0);
   glVertex3f(-0.866f,-0.5f,0.0);
   glVertex3f(-0.833f,-0.416f,0.0);
   glVertex3f(-0.8f,0.5f,0.0);
   glEnd();
   glPopMatrix();


   glPushMatrix();
   glTranslatef(_move2,0.0f,0.0f);
   glBegin(GL_POLYGON);
   glColor3f(0.0,0.56,0.698);
   glVertex3f(0.8f,-0.66f,0.0);
   glVertex3f(0.833f,-0.583f,0.0);
   glVertex3f(0.866f,-0.66f,0.0);
   glVertex3f(0.9f,-0.583f,0.0);
   glVertex3f(0.933f,-0.66f,0.0);
   glVertex3f(0.966f,-0.583f,0.0);
   glVertex3f(1.0f,-0.66f,0.0);
   glEnd();

   glPushMatrix();
   glTranslatef(_move,0.0f,0.0f);


   glBegin(GL_POLYGON);
   glColor3f(1.0,1.0,1.0);
   glVertex3f(-1.0f,0.5f,0.0f);
   glVertex3f(-0.5f,0.5f,0.0f);
   glVertex3f(-0.366f,0.55f,0.0f);
   glVertex3f(-0.45f,0.616f,0.0f);
   glVertex3f(-0.5f,0.66f,0.0f);
   glVertex3f(-1.0f,0.66f,0.0f);
   glEnd();

   glBegin(GL_POLYGON);
   glColor3f(1.0,0.0,0.0);
   glVertex3f(-0.966f,0.55f,0.0f);
   glVertex3f(-0.916f,0.55f,0.0f);
   glVertex3f(-0.916f,0.63f,0.0f);
   glVertex3f(-0.966f,0.63f,0.0f);
   glEnd();
   glBegin(GL_POLYGON);
   glColor3f(1.0,0.0,1.0);
   glVertex3f(-0.866f,0.55f,0.0f);
   glVertex3f(-0.816f,0.55f,0.0f);
   glVertex3f(-0.816f,0.63f,0.0f);
   glVertex3f(-0.866f,0.63f,0.0f);
   glEnd();

   glBegin(GL_POLYGON);
   glColor3f(1.0,0.0,0.0);
   glVertex3f(-0.766f,0.55f,0.0f);
   glVertex3f(-0.716f,0.55f,0.0f);
   glVertex3f(-0.716f,0.63f,0.0f);
   glVertex3f(-0.766f,0.63f,0.0f);
   glEnd();

   glBegin(GL_POLYGON);
   glColor3f(1.0,0.0,1.0);
   glVertex3f(-0.666f,0.55f,0.0f);
   glVertex3f(-0.616f,0.55f,0.0f);
   glVertex3f(-0.616f,0.63f,0.0f);
   glVertex3f(-0.666f,0.63f,0.0f);
   glEnd();

   glBegin(GL_POLYGON);
   glColor3f(1.0,0.0,0.0);
   glVertex3f(-0.566f,0.55f,0.0f);
   glVertex3f(-0.516f,0.55f,0.0f);
   glVertex3f(-0.516f,0.63f,0.0f);
   glVertex3f(-0.566f,0.63f,0.0f);
   glEnd();

   glBegin(GL_POLYGON);
   glColor3f(0.0,0.0,1.0);
   glVertex3f(-0.916f,0.66f,0.0f);
   glVertex3f(-0.83f,0.66f,0.0f);
   glVertex3f(-0.833f,0.833f,0.0f);
   glVertex3f(-0.916f,0.833f,0.0f);
   glEnd();

   glBegin(GL_POLYGON);
   glColor3f(0.0,0.0,1.0);
   glVertex3f(-0.66f,0.66f,0.0f);
   glVertex3f(-0.583f,0.66f,0.0f);
   glVertex3f(-0.633f,0.833f,0.0f);
   glVertex3f(-0.7f,0.833f,0.0f);
   glEnd();

   glBegin(GL_POLYGON);
   glColor3f(0.0,0.0,1.0);
   glVertex3f(-0.66f,0.33f,0.0f);
   glVertex3f(-0.616f,0.33f,0.0f);
   glVertex3f(-0.583f,0.516f,0.0f);
   glVertex3f(-0.68,0.516f,0.0f);
   glEnd();
   glPopMatrix();



   glPushMatrix();
   glBegin(GL_POLYGON);
   glVertex3f(-0.66f,0.0f,0.0f);
   glVertex3f(-0.416f,0.0f,0.0f);
   glVertex3f(-0.416f,0.25f,0.0f);
   glVertex3f(-0.66f,0.25f,0.0f);
   glEnd();

   glPushMatrix();
   glBegin(GL_POLYGON);
   glColor3f(0.8,1.0,0.6);
   glVertex3f(-0.25,0.0f,0.0f);
   glVertex3f(0.0f,0.0f,0.0f);
   glVertex3f(0.0f,0.25f,0.0f);
   glVertex3f(-0.25f,0.25f,0.0f);
   glEnd();

   glBegin(GL_POLYGON);
   glColor3f(0.6,0.0,0.29);
   glVertex3f(0.33,0.0,0.0);
   glVertex3f(0.5f,0.0f,0.0f);
   glVertex3f(0.5f,0.25f,0.0f);
   glVertex3f(0.33f,0.25f,0.0f);
   glEnd();

   glBegin(GL_POLYGON);
   glColor3f(1.0,0.69,0.5);
   glVertex3f(0.833f,0.0f,0.0f);
   glVertex3f(1.0f,0.0f,0.0f);
   glVertex3f(1.0f,0.25f,0.0f);
   glVertex3f(0.833f,0.25f,0.0f);
   glEnd();



   glBegin(GL_POLYGON);
   glColor3f(1.0,0.69,0.4);
   glVertex3f(-0.65f,0.166f,0.0f);
   glVertex3f(-0.566f,0.166f,0.0f);
   glVertex3f(-0.566f,0.216f,0.0f);
   glVertex3f(-0.65f,0.216f,0.0f);
   glEnd();

   glBegin(GL_POLYGON);
   glColor3f(1.0,0.69,0.4);
   glVertex3f(-0.65f,0.15f,0.0f);
   glVertex3f(-0.566f,0.15,0.0f);
   glVertex3f(-0.566f,0.1f,0.0f);
   glVertex3f(-0.65f,0.1f,0.0f);
   glEnd();

   glBegin(GL_POLYGON);
   glColor3f(1.0,0.69,0.4);
   glVertex3f(-0.65f,0.083f,0.0f);
   glVertex3f(-0.566f,0.083f,0.0f);
   glVertex3f(-0.566f,0.33f,0.0f);
  glVertex3f(-0.65f,0.033f,0.0f);
   glEnd();

   glBegin(GL_POLYGON);
   glColor3f(1.0,0.69,0.4);
   glVertex3f(-0.55f,0.166f,0.0f);
  glVertex3f(-0.5f,0.166f,0.0f);
  glVertex3f(0.5f,0.216f,0.0f);
  glVertex3f(-0.55f,0.216f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.69,0.4);
  glVertex3f(-0.55f,0.15f,0.0f);
  glVertex3f(-0.5f,0.15f,0.0f);
  glVertex3f(-0.5f,0.1f,0.0f);
  glVertex3f(-0.55f,0.1f,0.0f);
  glEnd();


  glBegin(GL_POLYGON);
  glColor3f(1.0,0.69,0.4);
  glVertex3f(-0.55f,0.083f,0.0f);
  glVertex3f(-0.5f,0.083f,0.0f);
  glVertex3f(-0.5f,0.033f,0.0f);
  glVertex3f(-0.55f,0.033f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.69,0.4);
  glVertex3f(-0.483,0.166f,0.0f);
  glVertex3f(-0.433f,0.166f,0.0f);
  glVertex3f(-0.433f,0.216f,0.0f);
  glVertex3f(-0.483f,0.216f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.69,0.4);
  glVertex3f(-0.483f,0.15f,0.0f);
  glVertex3f(-0.433f,0.15f,0.0f);
  glVertex3f(-0.433f,0.1f,0.0f);
  glVertex3f(-0.483f,0.1f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.69,0.4);
  glVertex3f(-0.483f,0.083f,0.0f);
  glVertex3f(-0.433f,0.083f,0.0f);
  glVertex3f(-0.433f,0.033f,0.0f);
  glVertex3f(-0.483f,0.033f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.0,0.4,0.4);
  glVertex3f(-0.233f,0.166f,0.0f);
  glVertex3f(-0.166f,0.166f,0.0f);
  glVertex3f(-0.166f,0.216f,0.0f);
  glVertex3f(-0.233f,0.216f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.0,0.4,0.4);
  glVertex3f(-0.233f,0.15f,0.0f);
  glVertex3f(-0.166f,0.15f,0.0f);
  glVertex3f(-0.166f,0.1f,0.0f);
  glVertex3f(-0.233f,0.1f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.0,0.4,0.4);
  glVertex3f(-0.233f,0.083f,0.0);
  glVertex3f(-0.166f,0.083f,0.0f);
  glVertex3f(-0.166f,0.033f,0.0f);
  glVertex3f(-0.233f,0.033f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.0,0.4,0.4);
  glVertex3f(-0.15f,0.166f,0.0f);
  glVertex3f(-0.066f,0.166f,0.0f);
  glVertex3f(-0.066f,0.216f,0.0f);
  glVertex3f(-0.15f,0.216f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.0,0.4,0.4);
  glVertex3f(-0.15f,0.15f,0.0f);
  glVertex3f(-0.066f,0.15f,0.0f);
  glVertex3f(-0.066f,0.1f,0.0f);
  glVertex3f(-0.15,0.1f,0.0f);

  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.0,0.4,0.4);
  glVertex3f(-0.15f,0.083f,0.0f);
  glVertex3f(-0.066f,0.083f,0.0);
  glVertex3f(-0.066f,0.033f,0.0f);
  glVertex3f(-0.15f,0.033f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.0,0.4,0.4);
  glVertex3f(-0.05,0.166f,0.0f);
  glVertex3f(0.0f,0.166f,0.0f);
  glVertex3f(0.0f,0.216f,0.0f);
  glVertex3f(-0.05f,0.216f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.0,0.4,0.4);
  glVertex3f(-0.05f,0.15f,0.0f);
  glVertex3f(0.0f,0.15f,0.0f);
  glVertex3f(0.0f,0.1f,0.0f);
  glVertex3f(-0.05f,0.1f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.0,0.4,0.4);
  glVertex3f(-0.05f,0.083f,0.0f);
  glVertex3f(0.0f,0.083f,0.0f);
  glVertex3f(-0.0f,0.033f,0.0f);
  glVertex3f(-0.05f,0.033f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.8,1.0);
  glVertex3f(0.366f,0.166f,0.0f);
  glVertex3f(0.466f,0.166f,0.0f);
  glVertex3f(0.466f,0.216f,0.0f);
  glVertex3f(0.366f,0.216f,0.0f);
  glEnd();


  glBegin(GL_POLYGON);
  glColor3f(1.0,0.8,1.0);
  glVertex3f(0.366f,0.15f,0.0f);
  glVertex3f(0.466f,0.15f,0.0);
  glVertex3f(0.466f,0.1f,0.0f);
  glVertex3f(0.366f,0.1f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.8,1.0);
  glVertex3f(0.366f,0.083f,0.0f);
  glVertex3f(0.466f,0.083f,0.0f);
  glVertex3f(0.466f,0.033f,0.0f);
  glVertex3f(0.366f,0.033f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,1.0,0.4);
  glVertex3f(0.866f,0.166f,0.0f);
  glVertex3f(0.966f,0.166f,0.0f);
  glVertex3f(0.966f,0.216f,0.0f);
  glVertex3f(0.866f,0.216f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,1.0,0.4);
  glVertex3f(0.866f,0.15f,0.0f);
  glVertex3f(0.966f,0.15f,0.0f);
  glVertex3f(0.966f,0.1f,0.0f);
  glVertex3f(0.866f,0.1f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,1.0,0.4);
  glVertex3f(0.866f,0.083f,0.0f);
  glVertex3f(0.966f,0.083f,0.0f);
  glVertex3f(0.966f,0.033f,0.0f);
  glVertex3f(0.866f,0.033f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.4,0.8,0.0);
  glVertex3f(-0.4166f,0.0f,0.0);
  glVertex3f(-0.33f,0.33f,0.0);
  glVertex3f(-0.25,0.0f,0.0);
  glEnd();

  glPushMatrix();
  glTranslatef(_move4,0.0f,0.0f);
  glBegin(GL_POLYGON);
  glColor3f(1.0,0.0,0.0);
  glVertex3f(0.5f,-0.166f,0.0f);
  glVertex3f(1.0f,-0.166f,0.0f);
  glVertex3f(1.0f,0.0f,0.0f);
  glVertex3f(0.55f,0.0f,0.0f);
  glVertex3f(0.5f,-0.033f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,1.0,0.0f);
  glVertex3f(0.5f,-0.1f,0.0f);
  glVertex3f(0.5166f,-0.1f,0.0f);
  glVertex3f(0.1566f,-0.066f,0.0f);
  glVertex3f(0.5f,-0.066f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.0,0.0);
  glVertex3f(0.55f,0.0f,0.0f);
  glVertex3f(1.0f,0.0f,0.0f);
  glVertex3f(1.0f,0.116f,0.0f);
  glVertex3f(0.55f,0.116f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.26,0.26,0.26);
  glVertex3f(0.5833f,0.016f,0.0f);
  glVertex3f(0.633f,0.016f,0.0f);
  glVertex3f(0.633f,0.1f,0.0f);
  glVertex3f(0.5833f,0.1f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.26,0.26,0.26);
  glVertex3f(0.65f,0.016f,0.0f);
  glVertex3f(0.7f,0.016f,0.0f);
  glVertex3f(0.7f,0.1f,0.0f);
  glVertex3f(0.65f,0.1f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.26,0.26,0.26);
  glVertex3f(0.716f,0.016f,0.0f);
  glVertex3f(0.766f,0.016f,0.0f);
  glVertex3f(0.766f,0.1f,0.0f);
  glVertex3f(0.716f,0.1f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.26,0.26,0.26);
  glVertex3f(0.783f,0.016f,0.0f);
  glVertex3f(0.833f,0.016f,0.0f);
  glVertex3f(0.833f,0.1f,0.0f);
  glVertex3f(0.783f,0.1f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.26,0.26,0.26);
  glVertex3f(0.85f,0.016f,0.0f);
  glVertex3f(0.9f,0.016f,0.0f);
  glVertex3f(0.9f,0.1f,0.0f);
  glVertex3f(0.85f,0.1f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.26,0.26,0.26);
  glVertex3f(0.916f,0.016f,0.0f);
  glVertex3f(0.966f,0.016f,0.0f);
  glVertex3f(0.966f,0.1f,0.0f);
  glVertex3f(0.916f,0.1f,0.0f);
  glEnd();
  glPopMatrix();


  glPushMatrix();

  glTranslatef(_move4+0.6,-0.2,0.0);
  glColor3f(0.0,0.0,0.0);
  glBegin(GL_POLYGON);

  for(int i=0;i<600;i++)
  {
	  float pi=3.1416;
	  float A=(i*2*pi)/100;
	  float r=0.06;
	  float x=r * cos(A);
	  float y=r * sin(A);
	  glVertex2f(x,y);
  }
  glEnd();
  glPopMatrix();
  glPushMatrix();
  glTranslatef(_move4+0.6,-0.2,0.0);
  glColor3f(1.0,1.0,1.0);
  glBegin(GL_POLYGON);

  for(int i=0;i<600;i++)
  {
	  float pi=3.1416;
	  float A=(i*2*pi)/100;
	  float r=0.03;
	  float x=r * cos(A);
	  float y=r * sin(A);
	  glVertex2f(x,y);
  }
  glEnd();
  glPopMatrix();
  glPushMatrix();

  glTranslatef(_move4+0.92,0.2,0.0);
  glColor3f(0.0,0.0,0.0);
  glBegin(GL_POLYGON);

  for (int i=0;i<600;i++)
  {
	  float pi=3.1416;
	  float A=(i*2*pi)/100;
	  float r=0.06;
	  float x=r * cos(A);
	  float y=r * sin(A);
	  glVertex2f(x,y);
  }
  glEnd();
  glPopMatrix();
  glPushMatrix();

  glTranslatef(_move4+0.92,-0.2,0.0);
  glColor3f(1.0,1.0,1.0);
  glBegin(GL_POLYGON);

  for(int i=0;i<600;i++)
  {
	  float pi=3.1416;
	  float A=(i*2*pi)/100;
	  float r=0.03;
	  float x=r * cos(A);
	  float y=r * sin(A);
	  glVertex2f(x,y);

  }
  glEnd();
  glPopMatrix();



  glPushMatrix();
  glBegin(GL_POLYGON);
  glColor3f(1.0,1.0,0.6);
  glVertex3f(-1.0f,-0.33f,0.0f);
  glVertex3f(-0.66f,-0.33f,0.0f);
  glVertex3f(-0.66f,0.33f,0.0f);
  glVertex3f(-1.0f,0.33f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.8,0.6,1.0);
  glVertex3f(-0.5f,-0.33f,0.0f);
  glVertex3f(-0.166f,-0.33f,0.0f);
  glVertex3f(-0.166f,0.166f,0.0f);
  glVertex3f(-0.5f,0.166f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.2,0.2);
  glVertex3f(0.0f,-0.33f,0.0f);
  glVertex3f(0.33f,-0.33f,0.0f);
  glVertex3f(0.33f,0.33f,0.0f);
  glVertex3f(0.0f,0.33f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.6,0.2);
  glVertex3f(0.5f,-0.33f,0.0f);
  glVertex3f(0.833f,-0.33f,0.0f);
  glVertex3f(0.833f,0.33f,0.0f);
  glVertex3f(0.5f,0.33f,0.0f);
  glEnd();
  glPopMatrix();


  glBegin(GL_POLYGON);
  glColor3f(1.0,0.6,0.0);
  glVertex3f(-0.966f,0.166f,0.0f);
  glVertex3f(-0.883f,0.166f,0.0f);
  glVertex3f(-0.883f,0.25f,0.0f);
  glVertex3f(-0.966f,0.25f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.6,0.8);
  glVertex3f(-0.7833f,0.166f,0.0f);
  glVertex3f(-0.7f,0.166f,0.0f);
  glVertex3f(-0.7f,0.25f,0.0f);
  glVertex3f(-0.7833f,0.25f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.6,0.8);
  glVertex3f(-0.7833f,0.0f,0.0f);
  glVertex3f(-0.7f,0.0f,0.0f);
  glVertex3f(-0.7f,0.0833f,0.0f);
  glVertex3f(-0.7833f,0.0833f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.6,0.8);
  glVertex3f(-0.966f,0.0f,0.0f);
  glVertex3f(-0.883f,0.0f,0.0f);
  glVertex3f(-0.883f,0.0833f,0.0f);
  glVertex3f(-0.966f,0.0833f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.6,0.8);
  glVertex3f(-0.966f,-0.0833f,0.0f);
  glVertex3f(-0.883f,-0.0833f,0.0f);
  glVertex3f(-0.883f,-0.166f,0.0f);
  glVertex3f(-0.966f,-0.166f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.6,0.8);
  glVertex3f(-0.7833f,-0.0833f,0.0f);
  glVertex3f(-0.7f,-0.0883f,0.0f);
  glVertex3f(-0.7f,-0.166f,0.0f);
  glVertex3f(-0.7833f,-0.166f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.25,0.0);
  glVertex3f(-0.466f,-0.25f,0.0f);
  glVertex3f(-0.383f,-0.25f,0.0f);
  glVertex3f(-0.383f,0.083f,0.0f);
  glVertex3f(-0.466f,0.083f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.25,0.0);
  glVertex3f(-0.33f,-0.25f,0.0f);
  glVertex3f(-0.25f,-0.25f,0.0f);
  glVertex3f(-0.25f,-0.166f,0.0f);
  glVertex3f(-0.33f,-0.166f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.25,0.0);
  glVertex3f(-0.33f,-0.15f,0.0f);
  glVertex3f(-0.25f,-0.15f,0.0f);
  glVertex3f(-0.25f,-0.033f,0.0f);
  glVertex3f(-0.33f,-0.033f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.25,0.0);
  glVertex3f(-0.33f,0.0f,0.0f);
  glVertex3f(-0.25f,0.0f,0.0f);
  glVertex3f(-0.25f,0.0833f,0.0f);
  glVertex3f(-0.33f,0.0833f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,1.0,0.6);
  glVertex3f(0.0166f,0.166f,0.0f);
  glVertex3f(0.0833f,0.166f,0.0f);
  glVertex3f(0.0833f,0.25f,0.0f);
  glVertex3f(0.0166f,0.25f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,1.0,0.6);
  glVertex3f(0.1166f,0.166f,0.0f);
  glVertex3f(0.1833f,0.166f,0.0f);
  glVertex3f(0.1833f,0.25f,0.0f);
  glVertex3f(0.1166f,0.25f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,1.0,0.6);
  glVertex3f(0.233f,0.166f,0.0f);
  glVertex3f(0.3f,0.166f,0.0f);
  glVertex3f(0.3f,0.25f,0.0f);
  glVertex3f(0.233f,0.25f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,1.0,0.6);
  glVertex3f(0.0166f,0.0833f,0.0f);
  glVertex3f(0.0833f,0.0833f,0.0f);
  glVertex3f(0.0833f,0.0f,0.0f);
  glVertex3f(0.0166f,0.0f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,1.0,0.6);
  glVertex3f(0.1166f,0.0833f,0.0f);
  glVertex3f(0.1833f,0.0833f,0.0f);
  glVertex3f(0.1833f,0.0f,0.0f);
  glVertex3f(0.1166f,0.0f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,1.0,0.6);
  glVertex3f(0.233f,0.0833f,0.0f);
  glVertex3f(0.3f,0.0833f,0.0f);
  glVertex3f(0.3f,0.0f,0.0f);
  glVertex3f(0.233f,0.0f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,1.0,0.6);
  glVertex3f(0.0166f,-0.0833f,0.0f);
  glVertex3f(0.0833f,-0.0833f,0.0f);
  glVertex3f(0.0833f,-0.166f,0.0f);
  glVertex3f(0.0166f,-0.166f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,1.0,0.6);
  glVertex3f(0.1166f,-0.0833f,0.0f);
  glVertex3f(0.1833f,-0.0833f,0.0f);
  glVertex3f(0.1833f,-0.166f,0.0f);
  glVertex3f(0.1166f,-0.166f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,1.0,0.6);
  glVertex3f(0.233f,-0.0833f,0.0f);
  glVertex3f(0.3f,-0.0833f,0.0f);
  glVertex3f(0.3f,-0.166f,0.0f);
  glVertex3f(0.233f,-0.166f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.25,0.0);
  glVertex3f(0.583f,0.166f,0.0f);
  glVertex3f(0.65f,0.166f,0.0f);
  glVertex3f(0.65f,0.25f,0.0f);
  glVertex3f(0.583f,0.25f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.25,0.0);
  glVertex3f(0.683f,0.166f,0.0f);
  glVertex3f(0.75f,0.166f,0.0f);
  glVertex3f(0.75f,0.25f,0.0f);
  glVertex3f(0.683f,0.25f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.25,0.0);
  glVertex3f(0.583f,0.083f,0.0f);
  glVertex3f(0.65f,0.083f,0.0f);
  glVertex3f(0.65f,0.0f,0.0f);
  glVertex3f(0.583f,0.0f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.25,0.0);
  glVertex3f(0.683f,0.083f,0.0f);
  glVertex3f(0.75f,0.083f,0.0f);
  glVertex3f(0.75f,0.0f,0.0f);
  glVertex3f(0.683f,0.0f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.25,0.0);
  glVertex3f(0.583f,-0.083f,0.0f);
  glVertex3f(0.65f,-0.083f,0.0f);
  glVertex3f(0.65f,-0.166f,0.0f);
  glVertex3f(0.583f,-0.166f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.25,0.0);
  glVertex3f(0.683f,-0.083f,0.0f);
  glVertex3f(0.75f,-0.083f,0.0f);
  glVertex3f(0.75f,-0.166f,0.0f);
  glVertex3f(0.683f,-0.166f,0.0f);
  glEnd();


  glPushMatrix();
  glBegin(GL_POLYGON);
  glColor3f(0.6,0.298,0.0);
  glVertex3f(-0.6f,-0.33f,0.0f);
  glVertex3f(-0.566f,-0.33f,0.0f);
  glVertex3f(-0.566f,0.166f,0.0f);
  glVertex3f(-0.6f,0.166f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.6,0.298,0.0);
  glVertex3f(-0.1f,-0.33f,0.0f);
  glVertex3f(-0.066f,-0.33f,0.0f);
  glVertex3f(-0.066f,0.166f,0.0f);
  glVertex3f(-0.1f,0.166f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.6,0.298,0.0);
  glVertex3f(0.4f,-0.33f,0.0f);
  glVertex3f(0.433f,-0.33f,0.0f);
  glVertex3f(0.433f,0.166f,0.0f);
  glVertex3f(0.4f,0.166f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.6,0.298,0.0);
  glVertex3f(0.9f,-0.33f,0.0f);
  glVertex3f(0.933f,-0.33f,0.0f);
  glVertex3f(0.933f,0.166f,0.0f);
  glVertex3f(0.9f,0.166f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.0,0.4,0.0);
  glVertex3f(-0.65f,-0.166f,0.0f);
  glVertex3f(-0.516f,-0.166f,0.0f);
  glVertex3f(-0.583f,0.0f,0.0f);

  glBegin(GL_POLYGON);
  glColor3f(0.0,0.4,0.0);
  glVertex3f(-0.15f,-0.166f,0.0f);
  glVertex3f(-0.016f,-0.166f,0.0f);
  glVertex3f(-0.0833f,0.0f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.0,0.4,0.0);
  glVertex3f(0.35f,-0.166f,0.0f);
  glVertex3f(0.483f,-0.166f,0.0f);
  glVertex3f(0.4166f,0.0f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.0,0.4,0.0);
  glVertex3f(0.85f,-0.166f,0.0f);
  glVertex3f(0.983f,-0.166f,0.0f);
  glVertex3f(0.9166f,0.0f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.4,0.8,0.0);
  glVertex3f(-0.65f,0.05f,0.0f);
  glVertex3f(-0.516f,-0.05,0.0f);
  glVertex3f(-0.583f,0.33f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.4,0.8,0.0);
  glVertex3f(-0.15f,-0.05f,0.0f);
  glVertex3f(-0.16f,-0.05f,0.0f);
  glVertex3f(-0.0833f,0.33f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.4,0.8,0.0);
  glVertex3f(0.35f,-0.05,0.0f);
  glVertex3f(0.483f,-0.05f,0.0f);
  glVertex3f(0.416f,0.33f,0.0f);
  glEnd();
  glBegin(GL_POLYGON);
  glColor3f(0.4,0.8,0.0);
  glVertex3f(0.85f,-0.05f,0.0f);
  glVertex3f(0.983f,-0.05f,0.0f);
  glVertex3f(0.9166f,0.33f,0.0f);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(_move3,0.0f,0.0f);
  glBegin(GL_POLYGON);
  glColor3f(0.4,0.0,0.0);
  glVertex3f(-0.833f,-0.66f,0.0);
  glVertex3f(-0.33f,-0.66f,0.0);
  glVertex3f(-0.25,-0.583f,0.0);
  glVertex3f(-0.916f,-0.583f,0.0);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,1.0,0.4);
  glVertex3f(-0.833f,-0.583f,0.0);
  glVertex3f(-0.33f,-0.583f,0.0);
  glVertex3f(-0.416f,-0.5f,0.0);
  glVertex3f(-0.75f,-0.5f,0.0);
  glEnd();


  glBegin(GL_POLYGON);
  glColor3f(1.0,0.4,0.698);
  glVertex3f(-0.66f,-0.5f,0.0);
  glVertex3f(-0.5f,-0.5f,0.0);
  glVertex3f(-0.583,-0.33f,0.0);
  glEnd();

  glBegin(GL_LINES);
  glColor3f(0.0,0.0,0.0);
  glVertex3f(-0.583f,-0.33f,0.0);
  glVertex3f(-0.583f,-0.166f,0.0);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.0,0.0);
  glVertex3f(-0.583,-0.283f,0.0);
  glVertex3f(-0.55f,0.25f,0.0);
  glVertex3f(-0.583f,-0.2166f,0.0);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.0,0.0);
  glVertex3f(-0.75f,-0.566f,0.0f);
  glVertex3f(-0.7f,-0.566f,0.0f);
  glVertex3f(-0.7,-0.516f,0.0f);
  glVertex3f(0.75f,-0.516f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.0,0.0);
  glVertex3f(-0.633f,-0.566f,0.0f);
  glVertex3f(-0.583f,-0.566f,0.0f);
  glVertex3f(-0.583,-0.516f,0.0f);
  glVertex3f(-0.633f,-0.516f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0,0.0,0.0);
  glVertex3f(-0.516f,-0.566f,0.0f);
  glVertex3f(-0.46f,-0.556f,0.0f);
  glVertex3f(-0.46f,-0.516f,0.0f);
  glVertex3f(-0.516f,-0.516f,0.0f);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.0,0.56,0.698);
  glVertex3f(-0.833f,-0.6833f,0.0f);
  glVertex3f(-0.33f,-0.6833f,0.0f);
  glVertex3f(-0.33f,-0.66f,0.0f);
  glVertex3f(-0.833f,-0.66f,0.0f);
  glEnd();

  glPopMatrix();



  glutSwapBuffers();
}


  void update (int value)
  {
	  _move +=0.0001f;
	  if(_move-1.5>1.0)
	  {
		  _move = -1.0;
	  }


	  _move1 += .005;
	  if(_move1-1.966>1.0)
	  {
		  _move1 = -1.0;
	  }



	  _move2 += .01;
	  if(_move2-1.663>1.0)
	  {
		  _move2 = -1.0;
	  }


	  _move3 += .001;
	  if(_move3-1.663>1.0)
	  {
		  _move3 = -1.0;
	  }

	  _move4 -= .01;
	  if(_move4+1.5 < -1.0)
	  {
		  _move4 = 1.0;
	  }
	  _move5 -= .01;
	  if (_move5+1.966 < - 1.0)
	  {
		  _move5 = 1.0;
	  }

	  _move6 += .0005;
	  if(_move6-0.39>1.0)
	  {
		  _move6 = -1.4;
	  }

	  _move7 += .0006;
	  if(_move7-0.79>1.0)
	  {
		  _move7 = -1.4;
	  }
	  glutPostRedisplay();

	  glutTimerFunc(25, update, 0);
  }

  int main(int argc, char** argv) {
	  glutInit(&argc,argv);
	  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	  glutInitWindowSize(1200,1200);
	  glutCreateWindow("City By The Lake");
	  glutDisplayFunc(drawScene);
	  glutTimerFunc(25, update, 0);

	  glutMainLoop();
	  return 0;




  }

