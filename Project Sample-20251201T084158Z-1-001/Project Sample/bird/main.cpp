#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
static float	yx	=  0.0;
static float	yy	= 0.0;
static float	bm	=  0.0;
static float	hr	=  0.0;
static float	sm	=  -66.0;
static float sk=30.0;
static float cr=0.0;

int a=1;
int serial=0;
static void Timer(int value)
{
    serial += 1;

    glutPostRedisplay();
    // 100 milliseconds
    glutTimerFunc(1000, Timer, 0);
}
void delay(){
    for(int i=0;i<100000000;i++);
}

void circle(GLfloat rx, GLfloat ry, GLfloat x, GLfloat y)
{
    int i=0;
    float angle;
    GLfloat PI= 2.0f * 3.1416;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x,y);
    for(i=0;i<100;i++)
    {
        angle = 2 * PI * i/100;
        glVertex2f(x+(cos(angle)*rx),y+(sin(angle)* ry));
    }
    glEnd();
}
void Sky()
{
    glColor3ub(182,209,255);
    glBegin(GL_QUADS);
    glVertex2d(0,55);
    glVertex2d(0,100);
    glVertex2d(100,100);
    glVertex2d(100,0);
    glEnd();
}


void yellow_bird()
{
    glColor3ub(236, 255, 94);
        circle(1.4,1,5,87);
         glColor3ub(60, 229, 13);
        circle(0.6,0.7,7,87);


          //eye
           glColor3ub(0,0,0);
          circle(0.2,0.2,7,87);

          //lip
           glColor3ub(60, 229, 13);
     glBegin(GL_TRIANGLES);

      glVertex2d(7,86.8);
      glVertex2d(7,87.2);
 glColor3ub(206, 46, 18);
      glVertex2d(8,85.7);
    glEnd();


          //pakha

     glColor3ub(242, 234, 19);
     glBegin(GL_QUADS);

      glVertex2d(4.5,87.5);
      glVertex2d(5.5,87.5);
       glColor3ub(60, 229, 13);
      glVertex2d(6.5,89);
      glVertex2d(3.5,89);
    glEnd();
    //tail
    glColor3ub(60, 229, 13);
     glBegin(GL_TRIANGLES);

      glVertex2d(2,90);
      glVertex2d(2,87);
 glColor3ub(242, 234, 19);
      glVertex2d(4,87);
    glEnd();



    //2
        glColor3ub(229, 4, 29);
        circle(1.4,1,25,85);
         glColor3ub(242, 234, 19);
        circle(0.6,0.7,27,85);


          //eye
           glColor3ub(0,0,0);
          circle(0.2,0.2,27,85);

          //lip
           glColor3ub(0,0,0);
     glBegin(GL_TRIANGLES);

      glVertex2d(27,84.8);
      glVertex2d(27,85.2);
 glColor3ub(229, 4, 29);
      glVertex2d(28,83.7);
    glEnd();


          //pakha

     glColor3ub(242, 234, 19);
     glBegin(GL_QUADS);

      glVertex2d(24.5,85.5);
      glVertex2d(25.5,85.5);
       glColor3ub(229, 4, 29);
      glVertex2d(26.5,87);
      glVertex2d(23.5,87);
    glEnd();
    //tail
    glColor3ub(60, 229, 13);
     glBegin(GL_TRIANGLES);

      glVertex2d(22,88);
      glVertex2d(22,85);
      glColor3ub(229, 4, 29);
      glVertex2d(24,85);


    glEnd();


}
void yellow_bird_fly()
{
    yx=yx+1;
    if (yx>100)
        yx=-27;
    glutPostRedisplay();

}

void HillTree()
{
    glColor3ub(122,10,10);
    glBegin(GL_QUADS);
    glVertex2d(78,58);
    glVertex2d(79,58);
    glVertex2d(79,63);
    glVertex2d(78,63);
    glEnd();
    glColor3ub(43,165,12);
    glBegin(GL_POLYGON);
    glVertex2d(76,63);
    glVertex2d(78.5,66);
    glVertex2d(81,63);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(76,64);
    glVertex2d(78.5,67);
    glVertex2d(81,64);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(76,65);
    glVertex2d(78.5,69);
    glVertex2d(81,65);
    glEnd();
    //
    glColor3ub(122,10,10);
    glBegin(GL_QUADS);
    glVertex2d(82,58);
    glVertex2d(83,58);
    glVertex2d(83,63);
    glVertex2d(82,63);
    glEnd();
    glColor3ub(43,165,12);
    glBegin(GL_POLYGON);
    glVertex2d(80,63);
    glVertex2d(82.5,66);
    glVertex2d(85,63);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(80,64);
    glVertex2d(82.5,67);
    glVertex2d(85,64);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(80,65);
    glVertex2d(82.5,69);
    glVertex2d(85,65);
    glEnd();
    //
    glColor3ub(122,10,10);
    glBegin(GL_QUADS);
    glVertex2d(86,58);
    glVertex2d(87,58);
    glVertex2d(87,63);
    glVertex2d(86,63);
    glEnd();
    glColor3ub(43,165,12);
    glBegin(GL_POLYGON);
    glVertex2d(84,63);
    glVertex2d(86.5,66);
    glVertex2d(89,63);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(84,64);
    glVertex2d(86.5,67);
    glVertex2d(89,64);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(84,65);
    glVertex2d(86.5,69);
    glVertex2d(89,65);
    glEnd();

        //
    glColor3ub(122,10,10);
    glBegin(GL_QUADS);
    glVertex2d(90,57);
    glVertex2d(91,57);
    glVertex2d(91,63);
    glVertex2d(90,63);
    glEnd();
    glColor3ub(43,165,12);
    glBegin(GL_POLYGON);
    glVertex2d(88,63);
    glVertex2d(90.5,66);
    glVertex2d(93,63);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(88,64);
    glVertex2d(90.5,67);
    glVertex2d(93,64);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(88,65);
    glVertex2d(90.5,69);
    glVertex2d(93,65);
    glEnd();
    //
    glColor3ub(122,10,10);
    glBegin(GL_QUADS);
    glVertex2d(94,57);
    glVertex2d(95,57);
    glVertex2d(95,63);
    glVertex2d(94,63);
    glEnd();
    glColor3ub(43,165,12);
    glBegin(GL_POLYGON);
    glVertex2d(92,63);
    glVertex2d(94.5,66);
    glVertex2d(97,63);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(92,64);
    glVertex2d(94.5,67);
    glVertex2d(97,64);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(92,65);
    glVertex2d(94.5,69);
    glVertex2d(97,65);
    glEnd();
    //
    glColor3ub(122,10,10);
    glBegin(GL_QUADS);
    glVertex2d(98,57);
    glVertex2d(99,57);
    glVertex2d(99,63);
    glVertex2d(98,63);
    glEnd();
    glColor3ub(43,165,12);
    glBegin(GL_POLYGON);
    glVertex2d(96,63);
    glVertex2d(98.5,66);
    glVertex2d(101,63);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(96,64);
    glVertex2d(98.5,67);
    glVertex2d(101,64);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(96,65);
    glVertex2d(98.5,69);
    glVertex2d(101,65);
    glEnd();

}
void Hill()
{
        glColor3ub(255,255,250);
    glBegin(GL_POLYGON);
    glVertex2d(15,55);
    glVertex2d(18,65);
    glVertex2d(21,67);
    glVertex2d(30,77);
    glVertex2d(33,75);
    glVertex2d(40,83);
    glVertex2d(45,75);
    glVertex2d(50,65);
    glVertex2d(55,55);
    glEnd();
    glColor3ub(239,239,239);
    glBegin(GL_POLYGON);
    glVertex2d(15,55);
    glVertex2d(18,65);
    glVertex2d(24,67);
    glVertex2d(30,77);
    glVertex2d(33,75);
    glVertex2d(40,83);
    glVertex2d(40,75);
    glVertex2d(32,70);
    glVertex2d(33,67);
    glVertex2d(25,55);
    glEnd();

    glColor3ub(255,255,250);
    glBegin(GL_POLYGON);
    glVertex2d(0,55);
    glVertex2d(3,65);
    glVertex2d(6,67);
    glVertex2d(15,77);
    glVertex2d(18,75);
    glVertex2d(25,83);
    glVertex2d(30,75);
    glVertex2d(35,65);
    glVertex2d(40,55);
    glEnd();
    glColor3ub(239,239,239);
    glBegin(GL_POLYGON);
    glVertex2d(0,55);
    glVertex2d(3,65);
    glVertex2d(6,67);
    glVertex2d(15,77);
    glVertex2d(18,75);
    glVertex2d(25,83);
    glVertex2d(25,75);
    glVertex2d(17,70);
    glVertex2d(18,67);
    glVertex2d(10,55);
    glEnd();



        glColor3ub(255,255,250);
    glBegin(GL_POLYGON);
    glVertex2d(35,55);
    glVertex2d(38,65);
    glVertex2d(41,67);
    glVertex2d(50,77);
    glVertex2d(53,75);
    glVertex2d(60,83);
    glVertex2d(65,75);
    glVertex2d(70,65);
    glVertex2d(75,55);
    glEnd();
    glColor3ub(239,239,239);
    glBegin(GL_POLYGON);
    glVertex2d(35,55);
    glVertex2d(38,65);
    glVertex2d(41,67);
    glVertex2d(50,77);
    glVertex2d(53,75);
    glVertex2d(60,83);
    glVertex2d(60,75);
    glVertex2d(52,70);
    glVertex2d(53,67);
    glVertex2d(50,55);
    glEnd();

    glColor3ub(255,255,250);
    glBegin(GL_POLYGON);
    glVertex2d(65,55);
    glVertex2d(68,65);
    glVertex2d(71,67);
    glVertex2d(80,77);
    glVertex2d(83,75);
    glVertex2d(90,83);
    glVertex2d(95,75);
    glVertex2d(100,65);
    glVertex2d(105,55);
    glEnd();
    glColor3ub(239,239,239);
    glBegin(GL_POLYGON);
    glVertex2d(65,55);
    glVertex2d(68,65);
    glVertex2d(71,67);
    glVertex2d(80,77);
    glVertex2d(83,75);
    glVertex2d(90,83);
    glVertex2d(90,75);
    glVertex2d(82,70);
    glVertex2d(83,67);
    glVertex2d(80,55);
    glEnd();

}
void waterMove()
{
 bm=bm+3;
if(bm>+3.1){
    bm=0;
    glutPostRedisplay();
    }
}
void SunMove(){
cr=cr+0.40;
if(cr>50)
    cr=3;
    glutPostRedisplay();
}
void Sun(){
glColor3ub(249, 252, 75);
    circle(8,11,45,60);


}
void River()
{
    glColor3ub(255,255,255);
    circle(1,1,2,42);
    circle(1,1,2,36);
    circle(1,1,2,30);
    circle(1,1,2,24);
    circle(1,1,2,18);

    circle(1,1,-1,42);
    circle(1,1,-1,36);
    circle(1,1,-1,30);
    circle(1,1,-1,24);
    circle(1,1,-1,18);

    circle(1,1,1,39);
    circle(1,1,1,33);
    circle(1,1,1,27);
    circle(1,1,1,21);

    circle(1,1,4,39);
    circle(1,1,4,33);
    circle(1,1,4,27);
    circle(1,1,4,21);

    circle(1,1,7,42);
    circle(1,1,7,36);
    circle(1,1,7,30);
    circle(1,1,7,24);
    circle(1,1,7,18);

    circle(1,1,10,39);
    circle(1,1,10,33);
    circle(1,1,10,27);
    circle(1,1,10,21);

    circle(1,1,13,42);
    circle(1,1,13,36);
    circle(1,1,13,30);
    circle(1,1,13,24);
    circle(1,1,13,18);

    circle(1,1,16,43);
    circle(1,1,16,39);
    circle(1,1,16,33);
    circle(1,1,16,27);
    circle(1,1,16,21);
    circle(1,1,16,18);

    circle(1,1,19,42);
    circle(1,1,19,36);
    circle(1,1,19,30);
    circle(1,1,19,24);
    circle(1,1,19,18);

    circle(1,1,22,43);
    circle(1,1,22,39);
    circle(1,1,22,33);
    circle(1,1,22,27);
    circle(1,1,22,21);
    circle(1,1,22,16);

    circle(1,1,25,42);
    circle(1,1,25,36);
    circle(1,1,25,30);
    circle(1,1,25,24);
    circle(1,1,25,18);
    circle(1,1,25,14);

    circle(1,1,28,43);
    circle(1,1,28,39);
    circle(1,1,28,33);
    circle(1,1,28,27);
    circle(1,1,28,21);
    circle(1,1,28,16);

    circle(1,1,31,42);
    circle(1,1,31,36);
    circle(1,1,31,30);
    circle(1,1,31,24);
    circle(1,1,31,18);
    circle(1,1,31,14);

    circle(1,1,34,43);
    circle(1,1,34,39);
    circle(1,1,34,33);
    circle(1,1,34,27);
    circle(1,1,34,21);
    circle(1,1,34,16);

    circle(1,1,37,42);
    circle(1,1,37,36);
    circle(1,1,37,30);
    circle(1,1,37,24);
    circle(1,1,37,18);
    circle(1,1,37,14);

    circle(1,1,40,44);
    circle(1,1,40,39);
    circle(1,1,40,33);
    circle(1,1,40,27);
    circle(1,1,40,21);
    circle(1,1,40,16);

    circle(1,1,43,42);
    circle(1,1,43,36);
    circle(1,1,43,30);
    circle(1,1,43,24);
    circle(1,1,43,18);
    circle(1,1,43,13);


    circle(1,1,46,39);
    circle(1,1,46,33);
    circle(1,1,46,27);
    circle(1,1,46,21);
    circle(1,1,46,16);
    circle(1,1,46,12);

    circle(1,1,49,42);
    circle(1,1,49,36);
    circle(1,1,49,30);
    circle(1,1,49,24);
    circle(1,1,49,18);
    circle(1,1,49,13);

    circle(1,1,52,39);
    circle(1,1,52,33);
    circle(1,1,52,27);
    circle(1,1,52,21);
    circle(1,1,52,16);
    circle(1,1,52,12);

    circle(1,1,55,42);
    circle(1,1,55,36);
    circle(1,1,55,30);
    circle(1,1,55,24);
    circle(1,1,55,18);
    circle(1,1,55,13);

    circle(1,1,58,39);
    circle(1,1,58,33);
    circle(1,1,58,27);
    circle(1,1,58,21);
    circle(1,1,58,16);
    circle(1,1,58,12);

    circle(1,1,61,42);
    circle(1,1,61,36);
    circle(1,1,61,30);
    circle(1,1,61,24);
    circle(1,1,61,18);
    circle(1,1,61,13);

    circle(1,1,64,39);
    circle(1,1,64,33);
    circle(1,1,64,27);
    circle(1,1,64,21);
    circle(1,1,64,16);
    circle(1,1,64,10);

    circle(1,1,67,42);
    circle(1,1,67,36);
    circle(1,1,67,30);
    circle(1,1,67,24);
    circle(1,1,67,18);
    circle(1,1,67,12);
    circle(1,1,67,6);

    circle(1,1,70,39);
    circle(1,1,70,33);
    circle(1,1,70,27);
    circle(1,1,70,21);
    circle(1,1,70,16);
    circle(1,1,70,10);

    circle(1,1,73,42);
    circle(1,1,73,36);
    circle(1,1,73,30);
    circle(1,1,73,24);
    circle(1,1,73,18);
    circle(1,1,73,12);
    circle(1,1,73,6);

    circle(1,1,76,39);
    circle(1,1,76,33);
    circle(1,1,76,27);
    circle(1,1,76,21);
    circle(1,1,76,16);
    circle(1,1,76,10);

    circle(1,1,79,42);
    circle(1,1,79,36);
    circle(1,1,79,30);
    circle(1,1,79,24);
    circle(1,1,79,18);
    circle(1,1,79,12);
    circle(1,1,79,6);

    circle(1,1,82,39);
    circle(1,1,82,33);
    circle(1,1,82,27);
    circle(1,1,82,21);
    circle(1,1,82,16);
    circle(1,1,82,10);
    circle(1,1,82,4);

    circle(1,1,85,42);
    circle(1,1,85,36);
    circle(1,1,85,30);
    circle(1,1,85,24);
    circle(1,1,85,18);
    circle(1,1,85,12);
    circle(1,1,85,6);

    circle(1,1,88,39);
    circle(1,1,88,33);
    circle(1,1,88,27);
    circle(1,1,88,21);
    circle(1,1,88,16);
    circle(1,1,88,10);
    circle(1,1,88,4);

    circle(1,1,91,42);
    circle(1,1,91,36);
    circle(1,1,91,30);
    circle(1,1,91,24);
    circle(1,1,91,18);
    circle(1,1,91,12);
    circle(1,1,91,6);

    circle(1,1,94,39);
    circle(1,1,94,33);
    circle(1,1,94,27);
    circle(1,1,94,21);
    circle(1,1,94,16);
    circle(1,1,94,10);
    circle(1,1,94,4);

    circle(1,1,97,42);
    circle(1,1,97,36);
    circle(1,1,97,30);
    circle(1,1,97,24);
    circle(1,1,97,18);
    circle(1,1,97,12);
    circle(1,1,97,6);
    circle(1,1,97,1);

    circle(1,1,100,39);
    circle(1,1,100,33);
    circle(1,1,100,27);
    circle(1,1,100,21);
    circle(1,1,100,16);
    circle(1,1,100,10);
    circle(1,1,100,4);

}

void Field()
{
    glColor3ub(77,255,40);
    glBegin(GL_POLYGON);
    glVertex2d(0,55);
    glVertex2d(55,60);
    glVertex2d(100,57);
    glVertex2d(100,0);
    glVertex2d(0,0);
    glEnd();
    glColor3ub(25,55,255);
    glBegin(GL_POLYGON);
    glVertex2d(0,0);
    glVertex2d(0,44);
    glVertex2d(35,44);
    glVertex2d(41,50);
    glVertex2d(47,44);
    glVertex2d(67,44);
    glVertex2d(71,47);
    glVertex2d(75,44);
    glVertex2d(100,45);
    glVertex2d(100,0);
    glEnd();

   glColor3ub(77,255,40);
    glBegin(GL_POLYGON);
    glVertex2d(0,0);
    glVertex2d(0,15);
    glVertex2d(40,7);
    glVertex2d(80,3);
    glVertex2d(90,1);
    glVertex2d(91,0);
    glEnd();
    circle(16,7,30,6);
    circle(16,7,10,9);
    circle(16,7,50,3);
}
void Tree1()
{
    glColor3ub(158,33,33);
    glBegin(GL_QUADS);
    glVertex2d(9.5,10);
    glVertex2d(12.5,10);
    glVertex2d(12.5,20);
    glVertex2d(9.5,20);
    glEnd();
    glColor3ub(31,158,39);
    glBegin(GL_POLYGON);
    glVertex2d(4,20);
    glVertex2d(18,20);
    glVertex2d(11,30);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(4,23);
    glVertex2d(18,23);
    glVertex2d(11,30);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(4,25);
    glVertex2d(18,25);
    glVertex2d(11,32);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(5,28);
    glVertex2d(17,28);
    glVertex2d(11,33);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(5,30);
    glVertex2d(17,30);
    glVertex2d(11,36);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(5,32);
    glVertex2d(17,32);
    glVertex2d(11,37);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(6,34);
    glVertex2d(16,34);
    glVertex2d(11,39);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(7,36);
    glVertex2d(15,36);
    glVertex2d(11,43);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(7,38);
    glVertex2d(15,38);
    glVertex2d(11,45);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(8,40);
    glVertex2d(14,40);
    glVertex2d(11,48);
    glEnd();
    glColor3ub(0,172,1);
     circle(2,2,8,8);
     circle(2,2,11,8);
     circle(2,2,14,8);

     circle(2,2,10,10);
     circle(2,2,12,10);
    glColor3ub(77,255,40);

}
void hideGrace()
{
    glColor3ub(77,255,40);
    glBegin(GL_POLYGON);
    glVertex2d(6,8);
    glVertex2d(30,8);
    glVertex2d(30,0);
    glVertex2d(6,0);
    glEnd();
}
void Tree2()
{
    glColor3ub(158,33,33);
    glBegin(GL_QUADS);
    glVertex2d(23.5,10);
    glVertex2d(26.5,10);
    glVertex2d(26.5,20);
    glVertex2d(23.5,20);
    glEnd();
     glColor3ub(0,172,1);
     circle(2,2,22,8);
     circle(2,2,25,8);
     circle(2,2,28,8);

     circle(2,2,24,10);
     circle(2,2,26,10);


    glColor3ub(31,158,39);
    glBegin(GL_POLYGON);
    glVertex2d(18,20);
    glVertex2d(32,20);
    glVertex2d(25,30);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(18,23);
    glVertex2d(32,23);
    glVertex2d(25,30);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(18,25);
    glVertex2d(32,25);
    glVertex2d(25,32);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(19,28);
    glVertex2d(31,28);
    glVertex2d(25,33);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(19,30);
    glVertex2d(31,30);
    glVertex2d(25,36);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(19,32);
    glVertex2d(31,32);
    glVertex2d(25,37);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(20,34);
    glVertex2d(30,34);
    glVertex2d(25,39);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(21,36);
    glVertex2d(29,36);
    glVertex2d(25,43);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(21,38);
    glVertex2d(29,38);
    glVertex2d(25,45);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(22,40);
    glVertex2d(28,40);
    glVertex2d(25,48);
    glEnd();
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    delay();
    Sky();

    SunMove();
    for(int i=0;i<1;i++){
     glPushMatrix();
     glTranslatef(0,cr+(8*i),0);
     Sun();
     glPopMatrix();
    }

    yellow_bird_fly();
   for(int i=0; i<1; i++)
   {
       glPushMatrix();
       glTranslatef(yx+i,0,0);
       yellow_bird();
       glPopMatrix();
   }
    Hill();
    Field();
    waterMove();
    for(int i=0;i<1;i++){
    glPushMatrix();
    glTranslatef(bm,0+(8*i),0);
    River();
    glPopMatrix();
    }
    HillTree();

    Tree1();
    Tree2();

    hideGrace();
	glFlush();
}

void init(void)
{
	glClearColor (0, 0, 0, 0);
	glOrtho(0, 100.0, 0, 100.0, 0, 100.0);
}



int main()
{
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (800, 600);
	glutInitWindowPosition (200, 0);
	glutCreateWindow ("design by ");
	init();
	glutDisplayFunc(display);
	PlaySound("2.wav", NULL, SND_ASYNC|SND_FILENAME);
	glutMainLoop();
	return 0;
}

