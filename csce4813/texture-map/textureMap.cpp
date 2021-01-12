//********************************
// Computer Graphics Project 5: Texture Mapping
// Author: Manuel Serna-Aguilera
// Credit: original block function, libim library, image.cpp, and shading.cpp created by Dr. John Gauch
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

DONE 4: loop over the N cubes in the scene and display the falling cubes at the correct location and orientation

DONE 5: simulate "raining cats and dogs"
    - to update cube locations, either define an idle or timer callback that loops over the N cubes (update pos using vel info, and increment angles by a small constant amount)
    - reset i) x, y positions, ii) starting angles, and iii) velocities after the yPos are greater than MAX_Y_VIEW+cubeSize+1
*/

// Headers needed for random num generation
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

#include "cubeTexture.h"
#include "libim/im_color.h"
#include <GL/glut.h>

#define SLEEP_TIME 2

vector<cubeTexture> cubes;// vector of cube texture objects
float cubeSize = 16.0;

const int COUNT = 20;
GLenum mode = GL_POLYGON;

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
    
    // Initialize all cube texture objects
    string name = "cat";
    
    // Initialize random number generation
    srand (time(NULL));
    
    // insert cats
    for (int i = 0; i <= 9; i++)
    {
        cubes.push_back(cubeTexture(name, to_string(i)));
        //cout << "\t" << &cubes.back() << endl;
    }
    
    // insert dogs
    name = "dog";
    for (int j = 0; j <= 9; j++)
    {
        cubes.push_back(cubeTexture(name, to_string(j)));
    }
}



//================================
// Draw block
//================================
void block(cubeTexture cube, float size)
{
    float xmin = cube.xPos - size/2.0;
    float xmax = cube.xPos + size/2.0;
    float ymin = cube.yPos - size/2.0;
    float ymax = cube.yPos + size/2.0;
    float zmin = cube.zPos - size/2.0;
    float zmax = cube.zPos + size/2.0;

    // Define 8 vertices
    float ax = xmin, ay = ymin, az = zmax;
    float bx = xmax, by = ymin, bz = zmax;
    float cx = xmax, cy = ymax, cz = zmax;
    float dx = xmin, dy = ymax, dz = zmax;
    float ex = xmin, ey = ymin, ez = zmin;
    float fx = xmax, fy = ymin, fz = zmin;
    float gx = xmax, gy = ymax, gz = zmin;
    float hx = xmin, hy = ymax, hz = zmin;
    
    // Draw 6 faces
    glBegin(GL_POLYGON);  
    glTexCoord2f(0.0, 0.0);
    glVertex3f(ax, ay, az);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(bx, by, bz);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(cx, cy, cz);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(dx, dy, dz);
    glEnd();

    glBegin(GL_POLYGON); 
    glTexCoord2f(0.0, 0.0);
    glVertex3f(bx, by, bz);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(fx, fy, fz);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(gx, gy, gz);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(cx, cy, cz);
    glEnd();

    glBegin(GL_POLYGON); 
    glTexCoord2f(0.0, 0.0);
    glVertex3f(fx, fy, fz);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(ex, ey, ez);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(hx, hy, hz);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(gx, gy, gz);
    glEnd();

    glBegin(GL_POLYGON); 
    glTexCoord2f(0.0, 0.0);
    glVertex3f(ex, ey, ez);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(ax, ay, az);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(dx, dy, dz);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(hx, hy, hz);
    glEnd();

    glBegin(GL_POLYGON);  
    glTexCoord2f(0.0, 0.0);
    glVertex3f(ax, ay, az);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(ex, ey, ez);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(fx, fy, fz);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(bx, by, bz);
    glEnd();

    glBegin(GL_POLYGON);  
    glTexCoord2f(0.0, 0.0);
    glVertex3f(gx, gy, gz);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(cx, cy, cz);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(dx, dy, dz);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(hx, hy, hz);
    glEnd();
}



//================================
// Timer callback
//================================
void timer(int value)
{
    // Update object positions with their respective velocities
    for (auto i = cubes.begin(); i != cubes.end(); i++)
    {
        (*i).xPos += (*i).vX;
        (*i).yPos += (*i).vY;
        
        if ((*i).yPos < -1*float(MAX_Y_VIEW + cubeSize + 1))
        {
            (*i).reset();
        }
    }
    
    // Redraw everything
    glutPostRedisplay();
    glutTimerFunc(SLEEP_TIME, timer, 0);
}



//================================
// Display callback
//================================
void display()
{
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    
    
    // For each cube texture object, update texture and other attributes
    for (auto i = cubes.begin(); i != cubes.end(); i++)
    {
        // Specify texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, XDIM, YDIM, 0, GL_RGB, GL_UNSIGNED_BYTE, (*i).texture);
        
        /*
        Properly draw--translate and rotate--the cube:
            - Move center of mass back to origin
            - Rotate by desired angle
            - Finally, move center of mass back
        Recall: the last transformation applied in code is the one that's applied first
        */
        glLoadIdentity();
        glTranslatef((*i).xPos, (*i).yPos, 0.0);// translate to original location
        (*i).angleX += 2.0;
        (*i).angleY += 4.0;
        (*i).angleZ += 6.0;
        glRotatef((*i).angleX, 1.0, 0.0, 0.0);// rotate
        glRotatef((*i).angleY, 0.0, 1.0, 0.0);
        glRotatef((*i).angleZ, 0.0, 0.0, 1.0);
        glTranslatef(-(*i).xPos, -(*i).yPos, 0.0);// translate to origin
        
        // Finally draw block
        block((*i), cubeSize);
    }
    
    glFlush();
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
    
    // OpenGL functions with callbacks
    glutTimerFunc(SLEEP_TIME, timer, 0);
    glutDisplayFunc(display);

    init();
    glutMainLoop();
    
    return 0;
}
