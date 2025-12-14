#include <GL/glut.h>
#include <iostream>
#include <math.h>

using namespace std;

// Global variables for cube coordinates
float X1, Y1, Z1;
float X2, Y2, Z2;

// Global variables for transformations
float transX = 0, transY = 0, transZ = 0;
float angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;
float scaleX = 1.0f, scaleY = 1.0f, scaleZ = 1.0f;

// Transformation step values
float stepX = 5, stepY = 5, stepZ = 5;
float Tx = 0.5f, Ty = 0.5f, Tz = 0.5f;
float Sx = 0.1f, Sy = 0.1f, Sz = 0.1f;

// ===== Function to draw a Cube =====
void drawCubeFromPoints(float x1, float y1, float z1, float x2, float y2, float z2)
{
    glBegin(GL_QUADS);
    
    // Front face (Red)
    glColor3f(1, 0, 0);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);
    
    // Back face (Green)
    glColor3f(0, 1, 0);
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y2, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y1, z2);
    
    // Left face (Blue)
    glColor3f(0, 0, 1);
    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y2, z2);
    glVertex3f(x1, y2, z1);
    
    // Right face (Yellow)
    glColor3f(1, 1, 0);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y2, z1);
    
    // Top face (Cyan)
    glColor3f(0, 1, 1);
    glVertex3f(x1, y2, z1);
    glVertex3f(x1, y2, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y2, z1);
    
    // Bottom face (Magenta)
    glColor3f(1, 0, 1);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
    glVertex3f(x1, y1, z2);
    
    glEnd();
}

// ===== Function to draw a Pyramid =====
void drawPyramid(float x1, float y1, float z1, float x2, float y2, float z2)
{
    float centerX = (x1 + x2) / 2.0f;
    float centerY = y2;
    float centerZ = (z1 + z2) / 2.0f;
    
    glBegin(GL_TRIANGLES);
    
    // Front face
    glColor3f(1, 0.5, 0);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(centerX, centerY, centerZ);
    
    // Right face
    glColor3f(1, 0, 1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
    glVertex3f(centerX, centerY, centerZ);
    
    // Back face
    glColor3f(0, 1, 1);
    glVertex3f(x2, y1, z2);
    glVertex3f(x1, y1, z2);
    glVertex3f(centerX, centerY, centerZ);
    
    // Left face
    glColor3f(0.5, 1, 0);
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y1, z1);
    glVertex3f(centerX, centerY, centerZ);
    
    // Base
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
    
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z2);
    glVertex3f(x1, y1, z2);
    
    glEnd();
}

// ===== Function to draw a Tetrahedron =====
void drawTetrahedron(float size)
{
    glBegin(GL_TRIANGLES);
    
    // Face 1
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(size, 0, 0);
    glVertex3f(size/2, size, 0);
    
    // Face 2
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(size, 0, 0);
    glVertex3f(size/2, size/2, size);
    
    // Face 3
    glColor3f(0, 0, 1);
    glVertex3f(size, 0, 0);
    glVertex3f(size/2, size, 0);
    glVertex3f(size/2, size/2, size);
    
    // Face 4
    glColor3f(1, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(size/2, size, 0);
    glVertex3f(size/2, size/2, size);
    
    glEnd();
}

// ===== Function to draw a Sphere =====
void drawSphere(float radius, int slices, int stacks)
{
    for(int i = 0; i < stacks; i++)
    {
        float lat0 = M_PI * (-0.5 + (float)i / stacks);
        float lat1 = M_PI * (-0.5 + (float)(i+1) / stacks);
        
        glBegin(GL_QUAD_STRIP);
        
        for(int j = 0; j <= slices; j++)
        {
            float lng = 2 * M_PI * (float)j / slices;
            
            float x0 = cos(lat0) * cos(lng);
            float y0 = sin(lat0);
            float z0 = cos(lat0) * sin(lng);
            
            float x1 = cos(lat1) * cos(lng);
            float y1 = sin(lat1);
            float z1 = cos(lat1) * sin(lng);
            
            glColor3f(0.2f + (i * 0.7f / stacks), 0.3f, 0.9f - (i * 0.5f / stacks));
            glVertex3f(x0 * radius, y0 * radius, z0 * radius);
            glVertex3f(x1 * radius, y1 * radius, z1 * radius);
        }
        
        glEnd();
    }
}

// ===== Display Function =====
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    gluLookAt(20, 20, 30,
              0, 0, 0,
              0, 1, 0);
    
    // Apply transformations
    glTranslatef(transX, transY, transZ);
    glRotatef(angleX, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);
    glRotatef(angleZ, 0, 0, 1);
    
    // ===== Draw Cube =====
    glPushMatrix();
    glScalef(scaleX, scaleY, scaleZ);
    drawCubeFromPoints(X1, Y1, Z1, X2, Y2, Z2);
    glPopMatrix();
    
    // ===== Draw Pyramid =====
    glPushMatrix();
    glTranslatef(8, 0, 0);
    glScalef(scaleX, scaleY, scaleZ);
    drawPyramid(X1, Y1, Z1, X2, Y2, Z2);
    glPopMatrix();
    
    // ===== Draw Tetrahedron =====
    glPushMatrix();
    glTranslatef(-8, 0, 0);
    glScalef(scaleX, scaleY, scaleZ);
    drawTetrahedron(3.0f);
    glPopMatrix();
    
    // ===== Draw Sphere =====
    glPushMatrix();
    glTranslatef(0, 0, 8);
    drawSphere(2.0f, 20, 20);
    glPopMatrix();
    
    glutSwapBuffers();
}

// ===== Keyboard Function =====
void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        // Rotation controls
        case 'X': angleX += stepX; break;
        case 'x': angleX -= stepX; break;
        case 'Y': angleY += stepY; break;
        case 'y': angleY -= stepY; break;
        case 'Z': angleZ += stepZ; break;
        case 'z': angleZ -= stepZ; break;
        
        // Translation controls
        case 'w': transY += Ty; break;
        case 's': transY -= Ty; break;
        case 'd': transX += Tx; break;
        case 'a': transX -= Tx; break;
        case 'q': transZ += Tz; break;
        case 'e': transZ -= Tz; break;
        
        // Scaling controls
        case '+':
            scaleX += Sx;
            scaleY += Sy;
            scaleZ += Sz;
            break;
        case '-':
            scaleX -= Sx;
            scaleY -= Sy;
            scaleZ -= Sz;
            if(scaleX < 0.1f) scaleX = 0.1f;
            if(scaleY < 0.1f) scaleY = 0.1f;
            if(scaleZ < 0.1f) scaleZ = 0.1f;
            break;
        
        // Reset
        case 'r':
            transX = 0; transY = 0; transZ = 0;
            angleX = 0; angleY = 0; angleZ = 0;
            scaleX = 1.0f; scaleY = 1.0f; scaleZ = 1.0f;
            break;
        
        case 27: exit(0); // ESC to exit
    }
    
    glutPostRedisplay();
}

// ===== Reshape Function =====
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)w / (float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// ===== Initialization Function =====
void init()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0, 1.0, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
}

// ===== Main Function =====
int main(int argc, char** argv)
{
    cout << "========================================\n";
    cout << "     3D Objects with Transformations\n";
    cout << "========================================\n\n";
    
    cout << "Enter first point (x1 y1 z1): ";
    cin >> X1 >> Y1 >> Z1;
    
    cout << "Enter second point (x2 y2 z2): ";
    cin >> X2 >> Y2 >> Z2;
    
    cout << "\n========== CONTROLS ==========\n";
    cout << "Rotation:    X/x, Y/y, Z/z\n";
    cout << "Translation: W/A/S/D/Q/E\n";
    cout << "Scale:       +/-\n";
    cout << "Reset:       R\n";
    cout << "Exit:        ESC\n";
    cout << "==============================\n\n";
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Objects - Cube, Pyramid, Tetrahedron, Sphere");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    
    return 0;
}