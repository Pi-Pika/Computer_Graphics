#include <GL/glut.h>
#include <math.h>
#include <vector>

const float PI = 3.14159265359;

void drawRectangle(float x, float y, float w, float h) {
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void drawCircle(float cx, float cy, float r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * PI / 180;
        glVertex2f(cx + r * cos(theta), cy + r * sin(theta));
    }
    glEnd();
}

void drawWheel(float x, float y, float r) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(0.6, 0.6, 0.6);
    drawCircle(0, 0, r);
    glColor3f(0.8, 0, 0);
    drawCircle(0, 0, r * 0.6);
    glPopMatrix();
}

void drawCloud(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(0.85, 0.85, 0.85);
    drawCircle(0, 0, 0.05);
    drawCircle(0.06, 0.01, 0.06);
    drawCircle(0.12, 0, 0.05);
    drawCircle(0.06, 0.04, 0.05);
    glPopMatrix();
}

void drawCustomSun(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(1, 1, 0);
    drawCircle(0, 0, 0.08);

    glLineWidth(3.0);
    glBegin(GL_LINES);
    for (int i = 0; i < 8; i++) {
        float theta = i * (2 * PI / 8);
        float r_inner = 0.1;
        float r_outer = 0.18;
        glVertex2f(r_inner * cos(theta), r_inner * sin(theta));
        glVertex2f(r_outer * cos(theta), r_outer * sin(theta));
    }
    glEnd();
    glLineWidth(1.0);
    glPopMatrix();
}

void drawPineTree(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(0.4, 0.25, 0.1);
    drawRectangle(-0.02, -0.2, 0.04, 0.2);
    glColor3f(0.1, 0.6, 0.1);
    drawTriangle(-0.12, -0.05, 0.12, -0.05, 0, 0.15);
    drawTriangle(-0.1, 0.1, 0.1, 0.1, 0, 0.3);
    drawTriangle(-0.08, 0.25, 0.08, 0.25, 0, 0.4);
    glPopMatrix();
}

void drawAppleTree(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(0.4, 0.25, 0.1);
    drawRectangle(-0.03, -0.2, 0.06, 0.3);
    glColor3f(0.1, 0.7, 0.1);
    drawCircle(0, 0.2, 0.18);
    glColor3f(0.9, 0, 0);
    drawCircle(-0.08, 0.15, 0.02);
    drawCircle(0.05, 0.12, 0.02);
    drawCircle(-0.02, 0.25, 0.02);
    drawCircle(0.1, 0.22, 0.02);
    drawCircle(-0.06, 0.3, 0.02);
    glPopMatrix();
}

void drawEngineBody(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);

    glColor3f(0.1, 0.1, 0.7);
    drawRectangle(0, 0, 0.45, 0.25);

    glColor3f(0.8, 0, 0);
    drawRectangle(0.25, 0.25, 0.2, 0.2);
    drawRectangle(0.23, 0.45, 0.24, 0.03);

    glColor3f(0.5, 0.8, 1.0);
    drawRectangle(0.28, 0.28, 0.14, 0.14);

    glColor3f(0.8, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(0.05, 0.25);
    glVertex2f(0.15, 0.25);
    glVertex2f(0.18, 0.45);
    glVertex2f(0.02, 0.45);
    glEnd();

    glColor3f(0.8, 0, 0);
    drawTriangle(0, 0, 0, 0.15, -0.1, 0);

    glColor3f(1, 1, 0);
    drawCircle(0, 0.18, 0.04);

    glPopMatrix();
}

void drawWagonBody(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);

    glColor3f(0.1, 0.1, 0.7);
    drawRectangle(0.05, 0, 0.3, 0.1);

    glColor3f(0.8, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(0, 0.1);
    glVertex2f(0.4, 0.1);
    glVertex2f(0.38, 0.3);
    glVertex2f(0.02, 0.3);
    glEnd();

    glColor3f(1, 1, 0);
    drawTriangle(0.05, 0.3, 0.35, 0.3, 0.2, 0.45);

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.3, 0.7, 1.0);
    drawRectangle(-1, -1, 2, 2);

    glColor3f(0.3, 0.8, 0.3);
    drawCircle(0, -1.3, 1.5);

    drawCustomSun(-0.75, 0.75);
    drawCloud(-0.4, 0.6);
    drawCloud(0.0, 0.7);
    drawCloud(0.4, 0.6);

    drawPineTree(0.4, 0.1);
    drawAppleTree(0.75, 0.05);

    float trainY = -0.25;

    glColor3f(0.6, 0.6, 0.6);
    drawRectangle(-0.1, trainY + 0.05, 0.2, 0.02);

    drawEngineBody(-0.55, trainY);
    drawWheel(-0.45, trainY, 0.08);
    drawWheel(-0.2, trainY, 0.08);

    drawWagonBody(0.1, trainY);
    drawWheel(0.2, trainY - 0.02, 0.06);
    drawWheel(0.4, trainY - 0.02, 0.06);

    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Train Scenery");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
