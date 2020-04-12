//********************************
// Computer Graphics Project 5: Texture Mapping
// Author: Manuel Serna-Aguilera
// Credit: libim library, image.cpp, and shading.cpp created by Dr. John Gauch
//********************************

#include <iostream>
#include <GL/glut.h>

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

// Surface rotation angle variables
float xAngle = 5.0;
float yAngle = 5.0;
float zAngle = 5.0;

using namespace std;



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
    
    glFlush();
}



//================================
// Keyboard callback
//================================
void keyboard(unsigned char key, int x, int y)
{
    // todo
}




//================================
// Main
//================================
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(X_SCREEN, Y_SCREEN);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Texture Mapping");
    
    init();

    glutMainLoop();
    
    return 0;
}
