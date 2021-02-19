//********************************
// Bezier Surface OpenGL Program
/*
  Compile:
  
    $ g++ -Wall bezierSurface.cpp -lGL -lGLU -lglut

  Execute as any other cpp program.
*/
//********************************

// Includes
#include <fstream>
#ifdef MAC
#include <GLUT/glut.h> // on Mac
#else
#include <GL/glut.h> // on Linux
#endif
#include <iostream>

// Global constants
// Drawing window x, y, z ranges
#define MIN_X_VIEW -10
#define MAX_X_VIEW 10
#define MIN_Y_VIEW -10
#define MAX_Y_VIEW 10
#define MIN_Z_VIEW -10
#define MAX_Z_VIEW 10

// OpenGL window coordinates
#define X_SCREEN 500
#define Y_SCREEN 500

// Sleep time
#define SLEEP_TIME 2

using namespace std;

// Other global constants & variables here
bool displayBezier = false;

// Bezier basis matrix
float Mb[4][4] = {
    { 1.0,   0.0,   0.0,  0.0},
    {-3.0,   3.0,   0.0,  0.0},
    { 3.0,  -6.0,   3.0,  0.0},
    {-1.0,   3.0,  -3.0,  1.0}
};

// 4x4 patch of a surface, this will serve as our control pts for the Bezier surface
const int M = 16;
const int N = 4;

// X-component, below arrays are equivalent
//float X[M] = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};
///*
float X[N][N] = {
    {0, 1, 2, 3},
    {0, 1, 2, 3},
    {0, 1, 2, 3},
    {0, 1, 2, 3}
};
//*/

// Y-component, below arrays are equivalent
//float Y[M] = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};
///* 
float Y[N][N] = {
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {2, 2, 2, 2},
    {3, 3, 3, 3}
};
//*/

// Z-component, below arrays are equivalent
//*/
//float surface[M] = {0, 0, 0, 0, 0, 2, 2, 1, 0, 2, 2, 1, 0, 0, 0, 0};
float surface[N][N] = {
    {0, 0, 0, 0},
    {0, 2, 2, 1},
    {0, 2, 2, 1},
    {0, 0, 0, 0}
};
//*/

/*
const int N = 10;
float surface[N][N] = {
    {0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 2, 1, 3, 2, 1, 1, 0, 0},
    {0, 1, 3, 3, 6, 4, 4, 3, 1, 0},
    {0, 2, 3, 8, 8, 8, 8, 3, 0, 0},
    {0, 0, 3, 8, 6, 5, 8, 4, 0, 0},
    
    {0, 0, 4, 8, 4, 6, 8, 3, 0, 0},
    {0, 1, 4, 8, 8, 8, 8, 4, 0, 0},
    {1, 2, 5, 3, 3, 4, 3, 4, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
//*/
/*
// Test surface
float surface[N][N] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 4, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
//*/

// Surface rotation angles
float xAngle = 0.0;
float yAngle = 0.0;
float zAngle = 0.0;



//================================
// Display user prompt
//================================
void displayPrompt()
{
    // Keyboard prompt
    cout << "Keyboard Prompt\n";
    cout << "\tw: display wireframe surface.\n";
    cout << "\tb: display Bezier surface patch.\n";
    cout << endl;
    cout << "\tx: decrease x-angle by 5 deg.\n";
    cout << "\tX: increase x-angle by 5 deg.\n";
    cout << "\ty: decrease y-angle by 5 deg.\n";
    cout << "\tY: increase y-angle by 5 deg.\n";
    cout << "\tz: decrease z-angle by 5 deg.\n";
    cout << "\tZ: increase z-angle by 5 deg.\n";
    
    // Mouse prompt
    //cout << "Mouse Prompt\n";
}

//================================
// Draw Wireframe Surface
//================================
void drawWireFrameSurface(float X[N][N], float Y[N][N], float Z[N][N], int step)
{
    // Iterate over (X,Y,Z) 4x4 patch
    for(int i=0; i<N; i++)
    {
        // Draw lines in x-direction
        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 1.0, 0.0);
        
        for(int j=0; j<N; j++)
        {
            float x = X[i][j];
            float y = Y[i][j];
            float z = Z[i][j];
            
            glVertex3f(x, y, z);
        }
        
        glEnd();
        
        // Draw lines in y-direction
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 0.0, 0.0);
        
        for(int j=0; j<N; j++)
        {
            float x = X[j][i];// NOTE: key diff is to reverse i and j indices
            float y = Y[j][i];
            float z = Z[j][i];
            
            glVertex3f(x, y, z);
        }
        
        glEnd();
    }
}

//================================
// Draw Bezier Surface
//  Inputs:
//================================
void drawBezierSurface(float X[N][N], float Y[N][N], float Z[N][N], int count)
{
    glColor3f(0.0, 1.0, 0.0);
    
    // Iterate over every horizontal and vertical line in patch
    for(int i=0; i<N; i++)
    {
        // Draw lines in x-direction
        //for(int j=0; j<N; j++)
        //{
            float Cx[4] = {0, 0, 0, 0};
            float Cy[4] = {0, 0, 0, 0};
            float Cz[4] = {0, 0, 0, 0};
            
            // Calculate individual polynomial
            for(int k=0; k<N; k++)
            {
                for(int l=0; l<N; l++)
                {
                    Cx[k] += Mb[k][l] * X[i][l];
                    Cy[k] += Mb[k][l] * Y[i][l];
                    Cz[k] += Mb[k][l] * Z[i][l];
                }
            }
            
            // Connect control points
            glBegin(GL_LINE_STRIP);
            float step = 1.0 / count;
            //float y = Y[i][j];
            
            for (float t=0; t<=1; t+=step)
            {
                float x = Cx[0] + t*(Cx[1] + t*(Cx[2] + t*Cx[3]));
                float y = Cy[0] + t*(Cy[1] + t*(Cy[2] + t*Cy[3]));
                float z = Cz[0] + t*(Cz[1] + t*(Cz[2] + t*Cz[3]));
                
                //glVertex2f(x, y);
                glVertex3f(x, y, z);
            }
            glEnd();
        //}
    }
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
    /*
     * NOTE: use GL_LINE_STRIP to only draw surface,
     *  and use GL_LINE_LOOP to draw entire object.
    */
    
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Update rotation
    glRotatef(xAngle, 1.0, 0.0, 0.0);
    glRotatef(yAngle, 0.0, 1.0, 0.0);
    glRotatef(zAngle, 0.0, 0.0, 1.0);
    
    // Display surface
    int step = 1;
    int count = 100;
    
    if (displayBezier)
    {
        drawBezierSurface(X, Y, surface, count);
    }
    else
    {
        drawWireFrameSurface(X, Y, surface, step);
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
        displayBezier = false;
    }
    else if ((key == 'b') || (key == 'B'))
    {
        displayBezier = true;
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
    displayPrompt();
    
    // OpenGL setup
    glutInit(&argc, argv);
    glutInitWindowSize(X_SCREEN, Y_SCREEN);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Bezier Surface");

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
