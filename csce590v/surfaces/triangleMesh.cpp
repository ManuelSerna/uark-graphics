//********************************
// Display simple uniform triangle mesh (hardcoded)
/*
  Compile:
  
    $ g++ -Wall triangleMesh.cpp -lGL -lGLU -lglut

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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Global constants
// Drawing window x, y, z ranges
#define MIN_X_VIEW -80
#define MAX_X_VIEW 80
#define MIN_Y_VIEW -80
#define MAX_Y_VIEW 80
#define MIN_Z_VIEW -80
#define MAX_Z_VIEW 80

// OpenGL window coordinates
#define X_SCREEN 800
#define Y_SCREEN 800
#define Z_SCREEN 800

// Sleep time
#define SLEEP_TIME 2

// Other global constants & variables here

using namespace std;

bool solid = false;// draw mesh as polygons (T) or only lines (F)

// Square surface created by triangle mesh
const int N = 16;// number of vertices
const int M = 66;// number of edges (33 directed, 66 undirected)
const int F = 18;// number of faces/triangles

// Vertex array V: each index contains a 3D point.
float V[N][3] = {
    {-20, 40, -30},
    {-20, 20, -14},
    {-20, 0, 0},
    {-20, -20, 0},
    
    {0, 40, -16},
    {0, 20, 0},
    {0, 0, 0},
    {0, -20, 6},
    
    {20, 40, -10},
    {20, 20, 0},
    {20, 0, 6},
    {20, -20, 16},
    
    {40, 40, -4},
    {40, 20, 4},
    {40, 0, 10},
    {40, -20, -4}
};

// Edges array E: each index refers to corresponding point in V. 
//  Assume undirected edges (i.e., edges (i,j) and (j,i) both exist if one is in E)
int E[M][2] = {
    {0,1},// 0
    {1,0},
    {1,2},
    {2,1},
    {2,3},
    {3,2},
    
    {4,5},// 6
    {5,4},
    {5,6},
    {6,5},
    {6,7},
    {7,6},
    
    {8,9},// 12
    {9,8},
    {9,10},
    {10,9},
    {10,11},
    {11,10},
    
    {12,13},// 18
    {13,12},
    {13,14},
    {14,13},
    {14,15},
    {15,14},
    
    {0,4},// 24
    {4,0},
    {4,8},
    {8,4},
    {8,12},
    {12,8},
    
    {1,5},// 30
    {5,1},
    {5,9},
    {9,5},
    {9,13},
    {13,9},
    
    {2,6},// 36
    {6,2},
    {6,10},
    {10,6},
    {10,14},
    {14,10},
    
    {3,7},// 42
    {7,3},
    {7,11},
    {11,7},
    {11,15},
    {15,11},
    
    {1,4},// 48
    {4,1},
    {2,5},
    {5,2},
    {3,6},
    {6,3},
    
    {5,8},// 54
    {8,5},
    {6,9},
    {9,6},
    {7,10},
    {10,7},
    
    {9,12},// 60
    {12,9},
    {10,13},
    {13,10},
    {11,14},
    {14,11}
};

// Triangle face array T: each index refers to an array of three edges, 
//  which refer to indices of corresponding edges in E.
int T[F][3] = {
    {0, 48, 25},// triangles read in counter-clockwise direction
    {30, 7, 49},
    {2, 50, 31},
    
    {51, 36, 9},
    {4, 52, 37},
    {53, 42, 11},
    
    {27, 6, 54},
    {32, 13, 27},
    {8, 56, 33},
    
    {38, 15, 57},
    {10, 58, 39},
    {44, 17, 59},
    
    {12, 60, 29},
    {34, 19, 61},
    {14, 62, 35},
    
    {40, 21, 63},
    {16, 64, 41},
    {46, 23, 65}
};

// Angle global variables
float xAngle = 15.0;
float yAngle = 0.0;
float zAngle = 15.0;



//================================
// User prompt
//================================
void prompt()
{
    cout << "Keyboard Prompt\n";
    cout << "\tw: wireframe of mesh.\n";
    cout << "\ts: solid mesh surface.\n";
    cout << endl;
    cout << "\tx: decrease x-angle by 5 deg.\n";
    cout << "\tX: increase x-angle by 5 deg.\n";
    cout << "\ty: decrease y-angle by 5 deg.\n";
    cout << "\tY: increase y-angle by 5 deg.\n";
    cout << "\tz: decrease z-angle by 5 deg.\n";
    cout << "\tZ: increase z-angle by 5 deg.\n";
}

//================================
// Draw mesh, given vertex, edge, and face arrays
//================================
void drawMesh(float V[N][3], int E[M][2], int T[F][3], bool solid)
{    
    if (!solid)
    {
        glColor3f(1.0, 1.0, 1.0);
    }
    
    // Iterate over triangle array
    for (int t=0; t<F; t++)
    {
        // "Fancy" coloring of triangles
        if (solid)
        {
            glBegin(GL_POLYGON);
            float intensity = ((t+10)% F) / float(F);// grayscale intensity
            
            if (intensity < 0.4) { intensity += 0.25; }
            else if (intensity > 0.85) { intensity -= 0.2; }
            
            glColor3f(intensity,intensity,intensity);
        }
        else { glBegin(GL_LINE_STRIP); }
        
        // Iterate through triangle t's 3 edges
        for (int i=0; i<3; i++)
        {
            // For each edge, get end vertices
            int edgeIndex = T[t][i];
            
            // i. Get points for first vertex
            int j = E[edgeIndex][0];
            float x = V[j][0];
            float y = V[j][1];
            float z = V[j][2];
            
            glVertex3f(x, y, z);
            
            // ii. Get points for second vertex
            if (!solid)
            {
                j = E[edgeIndex][1];
                x = V[j][0];
                y = V[j][1];
                z = V[j][2];
                
                glVertex3f(x, y, z);
            }
        }
        
        glEnd();
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
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Update rotation
    glRotatef(xAngle, 1.0, 0.0, 0.0);
    glRotatef(yAngle, 0.0, 1.0, 0.0);
    glRotatef(zAngle, 0.0, 0.0, 1.0);

    // Display mesh
    drawMesh(V, E, T, solid);
    
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
    // Update mesh
    if ((key == 's') || (key == 'S'))
    {
        solid = true;
    }
    else if ((key == 'w') || (key == 'W'))
    {
        solid = false;
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
    srand(time(0));// use current time as seed
    
    // OpenGL setup
    glutInit(&argc, argv);
    glutInitWindowSize(X_SCREEN, Y_SCREEN);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Simple Triangle Mesh");

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
