//********************************
// Draw curves
//********************************

#include <math.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <fstream>

// Global constants
// Drawing window x, y, z ranges
#define MIN_X_VIEW -99
#define MAX_X_VIEW 99
#define MIN_Y_VIEW -99
#define MAX_Y_VIEW 99
#define MIN_Z_VIEW -99
#define MAX_Z_VIEW 99

// OpenGL window coordinates
#define X_SCREEN 500
#define Y_SCREEN 500

#define SLEEP_TIME 2

// Surface rotation angle variables
float xAngle = 5.0;
float yAngle = 5.0;
float zAngle = 5.0;

// Basis matrices
const float BezierMatrix[4][4] = {
    {1.0, -3.0, 3.0, -1.0},
    {0.0, 3.0, -6.0, 3.0},
    {0.0, 0.0, 3.0, -3.0},
    {0.0, 0.0, 0.0, 1.0}
};

// Test set of points
float testX[4] = {1.0, 4.0, 3.0, 2.0};
float testY[4] = {1.0, 2.0, 4.0, 4.0};

using namespace std;

//================================
// Draw Bezier curve
//================================
void drawBezier()
{
    float controlX[4] = {0.0, 0.0, 0.0, 0.0};
    float controlY[4] = {0.0, 0.0, 0.0, 0.0};
    
    // Multiply coordinates with Bezier basis
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            controlX[i] += BezierMatrix[i][j]*testX[j];
            controlY[i] += BezierMatrix[i][j]*testY[j];
        }
    }
    
    // Draw Bezier curve
    float step = 1.0/20.0;
    glBegin(GL_LINE_STRIP);
    
    for(float t=0.0; t<=1; t+=step)
    {
        float x = controlX[0] + t*controlX[1] + t*t*controlX[2] + t*t*t*controlX[3];
        float y = controlY[0] + t*controlY[1] + t*t*controlY[2] + t*t*t*controlY[3];
        glVertex2f(x, y);
    }
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

    // Calculate scale factors
    float xScale = (MAX_X_VIEW - MIN_X_VIEW)/float(X_SCREEN);
    float yScale = (MAX_Y_VIEW - MIN_Y_VIEW)/float(Y_SCREEN);

    // Display
    // TODO: call line functions here
    drawBezier();
    glFlush();
}

//================================
// Idle callback
//================================
void idle()
{
}

//================================
// Keyboard callback
//================================
void keyboard(unsigned char key, int x, int y)
{
}

//================================
// Mouse callback
//================================

// Coordinates for when mouse button is pressed and then let go
float pressX = 0.0;
float pressY = 0.0;
float relX = 0.0;
float relY = 0.0;

void mouse(int button, int state, int x, int y)
{
}

//================================
// Motion callback
//================================
void motion(int x, int y)
{
}

//================================
// Main
//================================
int main(int argc, char *argv[])
{
    // OpenGL setup
    glutInit(&argc, argv);
    glutInitWindowSize(X_SCREEN, Y_SCREEN);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Display Curve");
    
    init();

    // OpenGL callbacks
    glutDisplayFunc(display);
    //glutIdleFunc(idle);
    //glutKeyboardFunc(keyboard);
    //glutMouseFunc(mouse);
    //glutMotionFunc(motion);
    //glutTimerFunc(SLEEP_TIME, timer, 0);

    // Run OpenGL program
    glutMainLoop();

    return 0;
}
