//********************************
// Cube Texture Class Header Implementation
//********************************

#include "cubeTexture.h"



//================================
// Read some image/texture jpg file
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
// Return -1 or 1 for random direction
//================================
int getDirection()
{
    int num = (rand() % 2);
    if (num == 0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}



//================================
// Constructor
// - initialize all values to fit in OpenGL window
/*
Parameters:
    - name: file name ("cat" or "dog" for this project)
    - num: file index (0-9 for this project)
*/
//================================
cubeTexture::cubeTexture(string name, string num)
{
    float xScale = (MAX_X_VIEW - MIN_X_VIEW)/(float)X_SCREEN;
    //float yScale = (MAX_Y_VIEW - MIN_Y_VIEW)/(float)Y_SCREEN;
    //float zScale = (MAX_Z_VIEW - MIN_Z_VIEW)/(float)Z_SCREEN;
    
    // Set random position
    xPos = float(MIN_X_VIEW + (rand() % X_SCREEN) * xScale);
    //yPos = float(MIN_Y_VIEW + (rand() % Y_SCREEN) * yScale);// start near the top of screen in y-direction
    int maxDrop = 10.0;// max distance from top of drawing window (MAX_Y_VIEW)
    yPos = float(rand() % maxDrop)*-1 + MAX_Y_VIEW;
    //zPos = float(MIN_Z_VIEW + 1 * zScale);
    zPos=0.0;
    
    // Set random velocities
    int maxVelocity = 5;
    vX = float(rand() % maxVelocity) * getDirection();
    vY = -1 * float(rand() % maxVelocity) - 1;
    vZ = float(rand() % maxVelocity) * getDirection();
    
    // Set random cube angles
    int maxAngle = 180;
    angleX = float(rand() % maxAngle);
    angleY = float(rand() % maxAngle);
    angleZ = float(rand() % maxAngle);
    
    // Set random cube radius
    int maxRadius = 20;
    r = float(rand() % maxRadius) + 10.0;
    
    // 1D texture array of usigned bytes
    file = "cats_dogs/" + name + num + ".jpg";// full file name
    //cout << "file name: " << file << endl;
    char fileName[file.size()+1];
    strcpy(fileName, file.c_str());
    initTexture((char *)fileName, texture);// initialize texture unsigned byte array for this cube object
    
    //cout << "coords for" << file << ": " << "(" << xPos << "," << yPos << "," << zPos << ")" << endl;
    //cout << "velocities " << file << ": " << "(" << vX << "," << vY << "," << vZ << ")" << endl;
    //cout << "angles (x, y ,z): " << "(" << angleX << "," << angleY << "," << angleZ << ")" << endl;
}

//================================
// Destructor
//================================
cubeTexture::~cubeTexture()
{
}

//================================
// Reset cube position
//================================
void cubeTexture::reset()
{    
    // Reset position
    float xScale = (MAX_X_VIEW - MIN_X_VIEW)/(float)X_SCREEN;
    int maxDrop = 20;
    
    xPos = float(MIN_X_VIEW + (rand() % X_SCREEN) * xScale);
    yPos = float(rand() % maxDrop)*-1 + MAX_Y_VIEW;
    
    // Reset velocities
    int maxVelocity = 10;
    vX = float(rand() % maxVelocity) * getDirection() * 0.25;
    vY = -1 * float(rand() % maxVelocity) - 1;
    vZ = float(rand() % maxVelocity) * getDirection();
    
    // Set random cube angles
    int maxAngle = 180;
    angleX = float(rand() % maxAngle);
    angleY = float(rand() % maxAngle);
    angleZ = float(rand() % maxAngle);
}
