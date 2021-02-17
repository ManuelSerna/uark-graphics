//********************************
// Subdivision Curves program
/*
  Compile:
  
    $ g++ -Wall example.cpp -lGL -lGLU -lglut

  Execute as any other cpp program.
*/
// Manuel Serna-Aguilera
//********************************

// Includes
#ifdef MAC
#include <GLUT/glut.h> // on Mac
#else
#include <GL/glut.h> // on Linux
#endif
#include <iostream>
#include <vector>

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
#define Z_SCREEN 100

// Sleep time
#define SLEEP_TIME 2

using namespace std;


// Global constants & variables
int divisions = 0;
const int MAX_DIVISIONS = 4;

// Rectangle
vector<float> X = {-20.0, 20.0,  20.0, -20.0};
vector<float> Y = {-60.0, -60.0, 60.0, 60.0};

// Another rectangle
//vector<float> X = {-90.0, 90.0,  90.0, -90.0};
//vector<float> Y = {-90.0, -90.0, 90.0, 60.0};

// Rhombus
//vector<float> X = {50.0, 0.0,  -50.0, 0.0};
//vector<float> Y = {0.0, -70.0, 0.0,   70.0};

// Pentagon
//vector<float> X = {10.0, 0.0, 35.0, 70.0, 60.0};
//vector<float> Y = {0.0, 30.0, 60.0, 30.0, 0.0};

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
    
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    
    for(int i=0; i<int(X.size()); i++)
    {
        glVertex2f(X[i], Y[i]);
    }
    
    glEnd();
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
    // When subdividing, create new polygon based on current polygon vertices
    if (((key == 'd') || (key == 'D')) && (divisions < MAX_DIVISIONS))
    {
        // Replace current points with new interpolated ones
        int M = int(X.size());
        int N = 2*M;
        float startVX = X[0];// starting vertex, save for when we want to reference
        float startVY = Y[0];
        
        float prevX = X[M-1];// when initially referring to previous vertex, we are actually referring to last vertex in array
        float prevY = Y[M-1];
        
        for(int i=0; i<N; i+=2)
        {
            int j = (i+1) % int(X.size());
            
            // Calculate midpoints for segments that include vertex i
            float eX1 = (X[i] + X[j])/2;
            float eY1 = (Y[i] + Y[j])/2;
            
            // Special case: when at last index, we want to use original first point!
            if(i/2 == M-1)
            {
                eX1 = (X[i] + startVX)/2;
                eY1 = (Y[i] + startVY)/2;
            }
            
            float eX2 = (X[i] + prevX)/2;
            float eY2 = (Y[i] + prevY)/2;
            
            // Calculate new point to replace (X[i], Y[i])
            float wX = 0.5*X[i] + 0.25*(eX1 + eX2);
            float wY = 0.5*Y[i] + 0.25*(eY1 + eY2);
            
            // Update previous points of old polygon
            prevX = X[i];
            prevY = Y[i];
            
            // Insert new points
            X[i] = wX;
            Y[i] = wY;
            X.insert(X.begin()+i+1, eX1);
            Y.insert(Y.begin()+i+1, eY1);
        }

		divisions++;
		cout << divisions << " divisions.\n";
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
    cout << "Press 'd' to subdivide curve.\n\n";
    
    // OpenGL setup
    glutInit(&argc, argv);
    glutInitWindowSize(X_SCREEN, Y_SCREEN);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Subdivision Curve");

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
