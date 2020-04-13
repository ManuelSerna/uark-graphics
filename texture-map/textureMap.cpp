//********************************
// Computer Graphics Project 5: Texture Mapping
// Author: Manuel Serna-Aguilera
// Credit: libim library, image.cpp, and shading.cpp created by Dr. John Gauch
//********************************

/*
TODO 1: Read images with Dr. Gauch's img processing code
(...)
*/



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
// Read image file (jpeg)
// Input: name of image file (directory included)
// Return: 3D array to hold color intensities for RGB channels
//================================
void readImage(string imageName, int data[YDIM][XDIM][3])
{
    // Read imamge file
    im_color image;
    //cout << "input file = " << imageName << endl;
    image.ReadJpg(imageName);
    
    // Get image dimensions
    int xdim = image.R.Xdim;
    int ydim = image.R.Ydim;
    //cout << "xdim = " << xdim << endl;
    //cout << "ydim = " << ydim << endl;
    
    // Save color values
    for (int y = 0; y < YDIM; y++)
    {
        for (int x = 0; x < XDIM; x++)
        {
            data[y][x][0] = image.R.Data2D[y][x];
            data[y][x][1] = image.G.Data2D[y][x];
            data[y][x][2] = image.B.Data2D[y][x];
        }
    }
}



//================================
// Read values from color (RGB) file
//================================
/*
void readImageData(string inputFile, image[XDIM][YDIM][3])
{
    // Counters for array
    int x = 0;
    int y = 0;
    
    string line;
    
    ifstream data;
    data.open(inputFile);
    
    // Check if file read goes wrong
    if(!data)
    {
        cout << "Error: could not read file. Bailing.";
        return;
    }
    
    // Read RGB image file
    // We are expecting, for each line, three values for the RGB components
    if(data.is_open())
    {
        while(getline(data, line))
        {
            // Extract tokens from each line
            vector <string> tokens;
            stringstream check1(line);// stringstream obj
            string intermediate;
        
            // Tokenize line, split along space " "
            while(getline(check1, intermediate, ' '))
            {
                tokens.push_back(intermediate);
            }
            
            // Populate color array
            image[y][x][0] = stof(tokens[0]);// r
            image[y][x][1] = stof(tokens[1]);// g
            image[y][x][2] = stof(tokens[2]);// b
            
            // Read image left->right, top-down
            x++;

            if (x >= XDIM)
            {
                x = 0;
                y++;
            }
        }
    }
    
    data.close();
}
*/



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
    
    int data1[YDIM][XDIM][3];
    readImage("cats_dogs/cat0.jpg", data1);

    glutMainLoop();
    
    return 0;
}
