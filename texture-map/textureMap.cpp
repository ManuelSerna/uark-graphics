//********************************
// Computer Graphics Project 5: Texture Mapping
// Author: Manuel Serna-Aguilera
// Credit: libim library, image.cpp, and shading.cpp created by Dr. John Gauch
//********************************

/*
Tasks: (look at project prompt)

DONE 1: Read images with Dr. Gauch's img processing code
DONE 2: Store selected image data in 1D texture array (unsigned byte)

TODO 3: Create data structure that represents the falling cubes
    - Keep track of:
        cube position (pX, pY, pZ)
        cube velocity (vX, vY, vZ)
        cube rotation angles (angleX, angleY, angleZ)
        cube radius r (of the sphere that encapsulates the cube)
        openGL texture array for the cube
        
    - the init() fuction should initialize a global data structure containing information for the N cubes

TODO 4: loop over the N cubes in the scene and display the falling cubes at the correct location and orientation

TODO 5: simulate "raining cats and dogs"
    - to update cube locations, either define an idle or timer callback that loops over the N cubes (update pos using vel info, and increment angles by a small constant amount)

*/

// Required libs for random number generation
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include "libim/im_color.h"
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

// Image dimensions
#define XDIM 512
#define YDIM 512
//#define ZDIM 500

// Surface rotation angle variables
float xAngle = 5.0;
float yAngle = 5.0;
float zAngle = 5.0;

using namespace std;



//================================
// Read image/texture jpg file
//================================
void initTexture(char *name, unsigned char *&texture)
{
    im_color image;
    image.ReadJpg(name);
    
    // Use malloc from stdlib to allocate (XDIM*YDIM*3) bytes of storage (malloc returns a pointer)
    texture = (unsigned char *)malloc((unsigned int)(XDIM*YDIM*3));
    
    // Every three indices stores RGB values for one pixel
    int i = 0;
    for (int y = 0; y < YDIM; y++)
    {
        for (int x = 0; x < XDIM; x++)
        {
            texture[i++] = (unsigned char)(image.R.Data2D[y][x]);
            texture[i++] = (unsigned char)(image.G.Data2D[y][x]);
            texture[i++] = (unsigned char)(image.B.Data2D[y][x]);
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
    
    string num;
    string file;
    
    // Initialize textures
    unsigned char *catTexture;
    unsigned char *dogTexture;
    
    string directory = "cats_dogs/";
    
    // Get cat file
    num = to_string(rand() % 10);// get random file #
    file = directory + "cat" + num + ".jpg";// set file directory
    char catFile[file.size()+1];// convert string to char [] for appropriate parameter data type
    strcpy(catFile, file.c_str());
    initTexture((char *)catFile, catTexture);
    
    // Get dog file
    num = to_string(rand() % 10);
    file = directory + "dog" + num + ".jpg";
    char dogFile[file.size()+1];
    strcpy(dogFile, file.c_str());
    initTexture((char *)dogFile, dogTexture);
    
    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, XDIM, YDIM, 0, GL_RGB, GL_UNSIGNED_BYTE, catTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, XDIM, YDIM, 0, GL_RGB, GL_UNSIGNED_BYTE, dogTexture);
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
