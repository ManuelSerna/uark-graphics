//********************************
// Template OpenGL Program
/*
  Compile:
  
    $ g++ -Wall example.cpp -lGL -lGLU -lglut

  Execute as any other cpp program.
*/
//********************************

// Includes
#ifdef MAC
#include <GLUT/glut.h> // on Mac
#else
#include <GL/glut.h> // on Linux
#endif

// Global constants
// Drawing window x, y, z ranges
//  TODO change
#define MIN_X_VIEW -99
#define MAX_X_VIEW 99
#define MIN_Y_VIEW -99
#define MAX_Y_VIEW 99
#define MIN_Z_VIEW -99
#define MAX_Z_VIEW 99

// OpenGL window coordinates
//  TODO change
#define X_SCREEN 500
#define Y_SCREEN 500
#define Z_SCREEN 500

// Sleep time
//  TODO change
#define SLEEP_TIME 2

// Other global constants & variables here

using namespace std;


//================================
// Init callback
//================================
void init()
{
    // Initialize view
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);// TODO change
    glMatrixMode(GL_PROJECTION);// TODO change
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// TODO change
    glMatrixMode(GL_MODELVIEW);// TODO change
    glLoadIdentity();

    // Update rotation
    //glRotatef(xAngle, 1.0, 0.0, 0.0);
    //glRotatef(yAngle, 0.0, 1.0, 0.0);
    //glRotatef(zAngle, 0.0, 0.0, 1.0);

    // Calculate scale factors
    float xScale = (MAX_X_VIEW - MIN_X_VIEW)/float(X_SCREEN);
    float yScale = (MAX_Y_VIEW - MIN_Y_VIEW)/float(Y_SCREEN);
    float zScale = (MAX_Z_VIEW - MIN_Z_VIEW)/float(Z_SCREEN);

    // TODO Display functions here
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
    // If using keyboard functionality, good idea to include keyboard
    //  prompt before calling any OpenGL functions
    //...
    
    // Redraw everything
    //glutPostRedisplay();
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
    // OpenGL setup
    glutInit(&argc, argv);
    glutInitWindowSize(X_SCREEN, Y_SCREEN);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Some OpenGL Program");

    // OpenGL callbacks
    glutDisplayFunc(display);
    //glutIdleFunc(idle);
    //glutKeyboardFunc(keyboard);
    //glutMouseFunc(mouse);
    //glutMotionFunc(motion);
    //glutTimerFunc(SLEEP_TIME, timer, 0);

    init();
    
    // Run OpenGL program
    glutMainLoop();

    return 0;
}
