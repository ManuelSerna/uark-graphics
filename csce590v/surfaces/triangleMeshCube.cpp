//********************************
// Display simple uniform triangle mesh for a cube using just vertices and faces (defined by vertices)
/*
  Compile:
  
    $ g++ -Wall triangleMeshCube.cpp -lGL -lGLU -lglut

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
const int N = 8;// number of vertices
const int M = -1;// number of edges
const int F = 12;// number of triangle faces

// Vertex array V
float V[N][3] = {
    {-40, -40, -40},
    {40, -40, -40},
    {40, 40, -40},
    {-40, 40, -40},
    {-40, -40, 40},
    {40, -40, 40},
    {40, 40, 40},
    {-40, 40, 40}
};

// Edge array E


// Face array
int Square[F][3] = {
    {0, 1, 2}, {0, 3, 2},// front face
    {2, 1, 6}, {6, 1, 5},// right face
    {6, 5, 7}, {7, 5, 4},// back face
    {7, 4, 0}, {3, 0, 7},// left face
    {2, 3, 6}, {6, 3, 7},// top face
    {1, 0, 5}, {5, 0, 4}// bottom face
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
// Draw mesh
//================================
void drawMesh(float vertices[N][3], int triangles[F][3], bool solid)
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
        else { glBegin(GL_LINE_LOOP); }
        
        // Iterate through triangle t's 3 vertices
        for (int v=0; v<3; v++)
        {
            // For each edge, get end vertices
            int vertexIndex = triangles[t][v];
            
            // i. Get points for first vertex
            float x = vertices[vertexIndex][0];
            float y = vertices[vertexIndex][1];
            float z = vertices[vertexIndex][2];
            
            glVertex3f(x, y, z);
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
    drawMesh(V, Square, solid);
    
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
    glutCreateWindow("Triangle Mesh: Cube");

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
