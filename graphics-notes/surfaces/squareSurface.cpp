//********************************
// Create surface
//********************************

#include <bits/stdc++.h> // for tokenizing strings
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>

// Global constants
// Drawing window x, y, z ranges
#define MIN_X_VIEW -199
#define MAX_X_VIEW 199
#define MIN_Y_VIEW -199
#define MAX_Y_VIEW 199
#define MIN_Z_VIEW -199
#define MAX_Z_VIEW 199

// OpenGL window coordinates
#define X_SCREEN 500
#define Y_SCREEN 500

// Surface rotation angle variables
float xAngle = 0.0;
float yAngle = 0.0;
float zAngle = 0.0;

// Surface array
const int N = 150;
float surface[N][N];

using namespace std;



//================================
// Display user prompt
//================================
void displayPrompt()
{
    // Keyboard prompt
    cout << "Keyboard Prompt\n";
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
// Zero-init NxN array
//================================
void initN2Array(float array[N][N])
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            array[i][j] = 0.0;
        }
    }
}

//================================
// Randomly-initialize values in NxN array
// Input:
//	array: (NxN) array to initialize
//  maxHeight: max value of elements in array
//================================
void initRandN2Array(float array[N][N], int maxHeight)
{
	srand(time(0));

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			array[i][j] = float(rand() % maxHeight);
		}
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
// Display surface only
//================================
void displaySurface(float xScale, float yScale)
{
    int step = 10;
    
    glColor3f(1.0, 0.0, 0.0);
    
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            if (x % step == 0)
            {
                // Get 3D patch for surface
                float tx1 = 0.0*MIN_X_VIEW + x * xScale;
                float ty1 = 0.0*MIN_Y_VIEW + y * yScale;
                float z1 = (float)(surface[y][x]);

                float tx2 = 0.0*MIN_X_VIEW + (x+1) * xScale;
                float ty2 = ty1;
                float z2 = (float)(surface[y+1][x]);

                float tx3 = tx2;
                float ty3 = 0.0*MIN_Y_VIEW + (y+1) * yScale;
                float z3 = (float)(surface[y+1][x+1]);

                float tx4 = 0.0*MIN_X_VIEW + x * xScale;
                float ty4 = ty3;
                float z4 = (float)(surface[y][x+1]);
                
                glBegin(GL_LINE_LOOP);
                glVertex3f(ty1, tx1, z1);
                glVertex3f(ty2, tx2, z2);
                glVertex3f(ty3, tx3, z3);
                glVertex3f(ty4, tx4, z4);
                glEnd();
            }
        }
    }
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
    displaySurface(xScale, yScale);
    glFlush();
}

//================================
// Keyboard callback
//================================
void keyboard(unsigned char key, int x, int y)
{
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
// Main
//================================
int main(int argc, char *argv[])
{
    displayPrompt();
    //initN2Array(surface);
	initRandN2Array(surface, 25);
    
    glutInit(&argc, argv);
    glutInitWindowSize(X_SCREEN, Y_SCREEN);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Display 3D Surface");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    init();

    glutMainLoop();

    return 0;
}
