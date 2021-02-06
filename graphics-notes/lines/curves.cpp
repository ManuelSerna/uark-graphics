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
    { 1.0,   0.0,   0.0,  0.0},
    {-3.0,   3.0,   0.0,  0.0},
    { 3.0,  -6.0,   3.0,  0.0},
    {-1.0,   3.0,  -3.0,  1.0} 
};

// Array of points
float X[100];
float Y[100];
int numPts = -1;



using namespace std;

//================================
// Draw circle
// Input: radius of circle
//================================
void drawCircle(float radius, float centerX, float centerY)
{
    glBegin(GL_POLYGON);
    
    for (int t = 0; t < 360.0; t++)
    {
        float radians = M_PI * t / 180.0;
        float x = radius * cos(radians);
        float y = radius * sin(radians);
        
        glVertex2f(x+centerX, y+centerY);
    }
    
    glEnd();
}

//================================
// Draw Bezier curve from points (X[i], Y[i])
//================================
void drawBezier(int start, int count)
{
    // Control points to draw one segment of curve
    float controlX[4] = {0.0, 0.0, 0.0, 0.0};
    float controlY[4] = {0.0, 0.0, 0.0, 0.0};
    
    // Multiply coordinates with Bezier basis
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            controlX[i] += BezierMatrix[i][j]*X[j+start];
            controlY[i] += BezierMatrix[i][j]*Y[j+start];
        }
    }
    
    // Draw Bezier curve
    glBegin(GL_LINE_STRIP);
    float step = 1.0/count;
    
    for(float t=0.0; t<=1.0; t+=step)
    {
        // NOTE: can factor out t's to simplify computations
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
    /*glRotatef(xAngle, 1.0, 0.0, 0.0);
    glRotatef(yAngle, 0.0, 1.0, 0.0);
    glRotatef(zAngle, 0.0, 0.0, 1.0);*/
    
    // Display
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINE_STRIP);
    
    for(int i=0; i<=numPts; i++)
    {
        glVertex2f(X[i], Y[i]);
    }
    
    glEnd();
    
    for(int i=0; i<=numPts-3; i+=3)
    {
        glColor3f(1.0, 0.0, 0.0);
        glLineWidth(2);
        drawBezier(i, 100);
    }//*/
    
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
    // Calculate scale factors
    float xScale = (MAX_X_VIEW - MIN_X_VIEW)/(float)X_SCREEN;
    float yScale = (-MAX_Y_VIEW + MIN_Y_VIEW)/(float)Y_SCREEN;

    if (state == GLUT_DOWN)
    {
        numPts++;
        
        // Calculate transformed x and y coords: tx and ty
        X[numPts] = MIN_X_VIEW + x * xScale;
        Y[numPts] = MAX_Y_VIEW + y * yScale;
        glutPostRedisplay();
    }
}

//================================
// Motion callback
//================================
void motion(int x, int y)
{
    // Calculate scale factors
    float xScale = (MAX_X_VIEW - MIN_X_VIEW)/(float)X_SCREEN;
    float yScale = (-MAX_Y_VIEW + MIN_Y_VIEW)/(float)Y_SCREEN;

    // Handle mouse motion
    X[numPts] = MIN_X_VIEW + x * xScale;
    Y[numPts] = MAX_Y_VIEW + y * yScale;

    // Redraw everything
    glutPostRedisplay();
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

    // OpenGL callbacks
    glutDisplayFunc(display);
    //glutIdleFunc(idle);
    //glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    //glutTimerFunc(SLEEP_TIME, timer, 0);

    init();
    
    // Run OpenGL program
    glutMainLoop();

    return 0;
}
