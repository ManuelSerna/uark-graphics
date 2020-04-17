//********************************
// Cube Texture Class Header
//********************************

#include <iostream>

// Headers needed for random num generation
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <string>

#include "libim/im_color.h"// read jpg images

// Drawing window x, y, z ranges
#define MIN_X_VIEW -99
#define MAX_X_VIEW 99
#define MIN_Y_VIEW -99
#define MAX_Y_VIEW 99
#define MIN_Z_VIEW -99
#define MAX_Z_VIEW 99

// Image dimensions
#define XDIM 512
#define YDIM 512
#define ZDIM 512

// OpenGL window coordinates
#define X_SCREEN 500
#define Y_SCREEN 500
#define Z_SCREEN 500

using namespace std;

class cubeTexture
{
public:
    cubeTexture(string, string);
    ~cubeTexture();
    void reset();
    
    // Public attributes
    string file;// 
    
    float xPos;// positions
    float yPos;
    float zPos;
    
    float vX;// velocities
    float vY;
    float vZ;
    
    float angleX;// cube angles
    float angleY;
    float angleZ;
    
    float r;// cube radius
    
    unsigned char *texture;// 1D texture array of usigned bytes
    
private:
    // nothing here
};
