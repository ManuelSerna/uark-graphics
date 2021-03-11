//********************************
// Render cube
/*
  Compile:
  
    $ g++ -Wall simpleCube.cpp -lGL -lGLU -lglut

  Execute as any other cpp program.
*/
//********************************

// Includes
#ifdef MAC
#include <GLUT/glut.h> // on Mac
#else
#include <GL/glut.h> // on Linux
#endif
#include <iostream>

// Global constants
// Drawing window x, y, z ranges
#define MIN_X_VIEW -99
#define MAX_X_VIEW 99
#define MIN_Y_VIEW -99
#define MAX_Y_VIEW 99
#define MIN_Z_VIEW -99
#define MAX_Z_VIEW 99

// OpenGL window coordinates
#define X_SCREEN 800
#define Y_SCREEN 800
#define Z_SCREEN 800

// Sleep time
#define SLEEP_TIME 2

// Other global constants & variables here

using namespace std;

bool drawSolid = false;

// Surface rotation angles
float xAngle = 5.0;
float yAngle = 5.0;
float zAngle = 5.0;

//================================
// User prompt
//================================
void prompt()
{
    cout << "Keyboard Prompt\n";
    cout << "\tw: display wireframe cube.\n";
    cout << "\tc: display solid cube.\n";
    cout << endl;
    cout << "\tx: decrease x-angle by 5 deg.\n";
    cout << "\tX: increase x-angle by 5 deg.\n";
    cout << "\ty: decrease y-angle by 5 deg.\n";
    cout << "\tY: increase y-angle by 5 deg.\n";
    cout << "\tz: decrease z-angle by 5 deg.\n";
    cout << "\tZ: increase z-angle by 5 deg.\n";
}

//================================
// Draw cube
//================================
void drawCubeWireframe(float centerX, float centerY, float centerZ, float size)
{
    glColor3f(0.0, 1.0, 0.0);
    
    // Define vertices of cube: vertex v={x, y, z}
    float v1[3] = {centerX-size, centerY-size, centerZ+size};
    float v2[3] = {centerX-size, centerY+size, centerZ+size};
    float v3[3] = {centerX+size, centerY+size, centerZ+size};
    float v4[3] = {centerX+size, centerY-size, centerZ+size};
    
    float v5[3] = {centerX-size, centerY-size, centerZ-size};
    float v6[3] = {centerX-size, centerY+size, centerZ-size};
    float v7[3] = {centerX+size, centerY+size, centerZ-size};
    float v8[3] = {centerX+size, centerY-size, centerZ-size};
    
    // Draw six faces
    glBegin(GL_LINE_LOOP);
    glVertex3f(v1[0], v1[1], v1[2]);
    glVertex3f(v2[0], v2[1], v2[2]);
    glVertex3f(v3[0], v3[1], v3[2]);
    glVertex3f(v4[0], v4[1], v4[2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3f(v1[0], v1[1], v1[2]);
    glVertex3f(v2[0], v2[1], v2[2]);
    glVertex3f(v6[0], v6[1], v6[2]);
    glVertex3f(v5[0], v5[1], v5[2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3f(v4[0], v4[1], v4[2]);
    glVertex3f(v3[0], v3[1], v3[2]);
    glVertex3f(v7[0], v7[1], v7[2]);
    glVertex3f(v8[0], v8[1], v8[2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3f(v1[0], v1[1], v1[2]);
    glVertex3f(v5[0], v5[1], v5[2]);
    glVertex3f(v8[0], v8[1], v8[2]);
    glVertex3f(v4[0], v4[1], v4[2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3f(v2[0], v2[1], v2[2]);
    glVertex3f(v6[0], v6[1], v6[2]);
    glVertex3f(v7[0], v7[1], v7[2]);
    glVertex3f(v3[0], v3[1], v3[2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3f(v5[0], v5[1], v5[2]);
    glVertex3f(v6[0], v6[1], v6[2]);
    glVertex3f(v7[0], v7[1], v7[2]);
    glVertex3f(v8[0], v8[1], v8[2]);
    glEnd();
}

void drawCubeSolid(float centerX, float centerY, float centerZ, float size)
{    
    // Define vertices of cube: vertex v={x, y, z}
    float v1[3] = {centerX-size, centerY-size, centerZ+size};
    float v2[3] = {centerX-size, centerY+size, centerZ+size};
    float v3[3] = {centerX+size, centerY+size, centerZ+size};
    float v4[3] = {centerX+size, centerY-size, centerZ+size};
    
    float v5[3] = {centerX-size, centerY-size, centerZ-size};
    float v6[3] = {centerX-size, centerY+size, centerZ-size};
    float v7[3] = {centerX+size, centerY+size, centerZ-size};
    float v8[3] = {centerX+size, centerY-size, centerZ-size};
    
    // Draw six faces
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(v1[0], v1[1], v1[2]);
    glVertex3f(v2[0], v2[1], v2[2]);
    glVertex3f(v3[0], v3[1], v3[2]);
    glVertex3f(v4[0], v4[1], v4[2]);
    glEnd();
    
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(v1[0], v1[1], v1[2]);
    glVertex3f(v2[0], v2[1], v2[2]);
    glVertex3f(v6[0], v6[1], v6[2]);
    glVertex3f(v5[0], v5[1], v5[2]);
    glEnd();
    
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(v4[0], v4[1], v4[2]);
    glVertex3f(v3[0], v3[1], v3[2]);
    glVertex3f(v7[0], v7[1], v7[2]);
    glVertex3f(v8[0], v8[1], v8[2]);
    glEnd();
    
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(v1[0], v1[1], v1[2]);
    glVertex3f(v5[0], v5[1], v5[2]);
    glVertex3f(v8[0], v8[1], v8[2]);
    glVertex3f(v4[0], v4[1], v4[2]);
    glEnd();
    
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(v2[0], v2[1], v2[2]);
    glVertex3f(v6[0], v6[1], v6[2]);
    glVertex3f(v7[0], v7[1], v7[2]);
    glVertex3f(v3[0], v3[1], v3[2]);
    glEnd();
    
    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(v5[0], v5[1], v5[2]);
    glVertex3f(v6[0], v6[1], v6[2]);
    glVertex3f(v7[0], v7[1], v7[2]);
    glVertex3f(v8[0], v8[1], v8[2]);
    glEnd();
}

//================================
// Init callback
//================================
void init()
{
    // Initialize view
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glOrtho(
        MIN_X_VIEW, MAX_X_VIEW, 
        MIN_Y_VIEW, MAX_Y_VIEW, 
        MIN_Z_VIEW, MAX_Z_VIEW
    );
}

//================================
// Display callback
//================================
void display()
{
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Update rotation
    glRotatef(xAngle, 1.0, 0.0, 0.0);
    glRotatef(yAngle, 0.0, 1.0, 0.0);
    glRotatef(zAngle, 0.0, 0.0, 1.0);
    
    // Display cube
    int centerX = 0.0;
    int centerY = 0.0;
    int centerZ = 0.0;
    int cubeSize = 20.0;
    
    if (drawSolid)
    {
        drawCubeSolid(centerX, centerY, centerZ, cubeSize);
    }
    else
    {
        drawCubeWireframe(centerX, centerY, centerZ, cubeSize);
    }
    
    glFlush();
}

//================================
// Idle callback
//================================
void idle()
{
    //...
    
    // Redraw everything
    glutPostRedisplay();
}

//================================
// Keyboard callback
//================================
void keyboard(unsigned char key, int x, int y)
{
    // Update surface type
    if ((key == 'w') || (key == 'W'))
    {
        drawSolid = false;
    }
    else if ((key == 'c') || (key == 'C'))
    {
        drawSolid = true;
    }
    
    // Update angles
    if (key == 'x')
    {
        xAngle -= 5;
    }
    else if (key == 'X')
    {
        xAngle += 5;
    }
    else if (key == 'y')
    {
        yAngle -= 5;
    }
    else if (key == 'Y')
    {
        yAngle += 5;
    }
    else if (key == 'z')
    {
        zAngle -= 5;
    }
    else if (key == 'Z')
    {
        zAngle += 5;
    }
    
    // Redraw everything
    glutPostRedisplay();
}

//================================
// Mouse callback
//================================

// Coordinates for when mouse button is pressed and then let go
float pressX = 0.0;// when mouse button is pressed
float pressY = 0.0;
float relX = 0.0;// when mouse button is released
float relY = 0.0;

void mouse(int button, int state, int x, int y)
{
    // If using mouse functionality, good idea to include mouse prompt
    //  before calling any OpenGL functions
    //...
    
    // Redraw everything
    //glutPostRedisplay();
}

//================================
// Motion callback
//================================
void motion(int x, int y)
{
    //...
    
    // Redraw everything
    //glutPostRedisplay();
}

//================================
// Timer callback
//================================
void timer(int value)
{
    //...
    
    // Redraw everything
    //glutPostRedisplay();
    //glutTimerFunc(SLEEP_TIME, timer, 0);
}

//================================
// Main
//================================
int main(int argc, char *argv[])
{
    prompt();
    
    // OpenGL setup
    glutInit(&argc, argv);
    glutInitWindowSize(X_SCREEN, Y_SCREEN);
    glutInitWindowPosition(200, 200);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Simple 3D Shape");

    // OpenGL callbacks
    glutDisplayFunc(display);
    //glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    //glutMouseFunc(mouse);
    //glutMotionFunc(motion);
    //glutTimerFunc(SLEEP_TIME, timer, 0);

    init();
    
    // Run OpenGL program
    glutMainLoop();

    return 0;
}
