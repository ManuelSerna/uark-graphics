//********************************
// Computer Graphics Project 5: Texture Mapping
// Author: Manuel Serna-Aguilera
// Credit: libim library, image.cpp, and shading.cpp created by Dr. John Gauch
//********************************

/*
Tasks: (look at project prompt)

DONE 1: Read images with Dr. Gauch's img processing code
DONE 2: Store selected image data in 1D texture array (unsigned byte)

DONE 3: Create data structure that represents the falling cubes
    - Keep track of:
        cube position (pX, pY, pZ)
        cube velocity (vX, vY, vZ)
        cube rotation angles (angleX, angleY, angleZ)
        cube radius r (of the sphere that encapsulates the cube)
        openGL texture array for the cube
        
    - DONE: the init() fuction should initialize a global data structure containing information for the N cubes

TODO 4: loop over the N cubes in the scene and display the falling cubes at the correct location and orientation

TODO 5: simulate "raining cats and dogs"
    - to update cube locations, either define an idle or timer callback that loops over the N cubes (update pos using vel info, and increment angles by a small constant amount)

*/

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "cubeTexture.h"
#include "libim/im_color.h"
#include <GL/glut.h>

// Create cube texture objects (10 cats and 10 dogs)
const int COUNT = 20;
vector<cubeTexture> cubes;

// Surface rotation angle variables
float xAngle = 25.0;
float yAngle = 25.0;
float zAngle = 25.0;

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
    
    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    
    // Initialize all cube textures
    string name = "cat";
    
    // insert cats
    for (int i = 0; i < 9; i++)
    {
        cubes.push_back(cubeTexture(name, to_string(i)));
    }
    
    // insert dogs
    name = "dog";
    for (int j = 0; j < 9; j++)
    {
        cubes.push_back(cubeTexture(name, to_string(j)));
    }
    
    // Initialize textures
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, XDIM, YDIM, 0, GL_RGB, GL_UNSIGNED_BYTE, cube1.texture);
    for (auto i = cubes.begin(); i != cubes.end(); i++)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, XDIM, YDIM, 0, GL_RGB, GL_UNSIGNED_BYTE, (*i).texture);
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
    
    // TODO: update below for all texture cube objects
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
    // Initialize random number generation
    srand (time(NULL));
    
    // OpenGL setup
    glutInit(&argc, argv);
    glutInitWindowSize(X_SCREEN, Y_SCREEN);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Texture Mapping");
    
    init();

    glutMainLoop();
    
    return 0;
}
