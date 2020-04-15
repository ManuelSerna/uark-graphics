//********************************
// Cube Texture Class Header Implementation
//********************************

#include "cubeTexture.h"



//================================
// Read a(n) image/texture jpg file
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
    // Initialize random number generation
    srand (time(NULL));
    
    // num = to_string(rand() % 10);
    float xScale = (MAX_X_VIEW - MIN_X_VIEW)/(float)X_SCREEN;
    float yScale = (MAX_Y_VIEW - MIN_Y_VIEW)/(float)Y_SCREEN;
    float zScale = (MAX_Z_VIEW - MIN_Z_VIEW)/(float)Z_SCREEN;
    
    // Set random position
    xPos = MIN_X_VIEW + (rand() % X_SCREEN) * xScale;
    yPos = MIN_Y_VIEW + (rand() % Y_SCREEN) * yScale;;
    zPos = MIN_Z_VIEW + (rand() % Z_SCREEN) * zScale;;
    
    // Set random velocities
    vX = float(rand() % 99);
    vY = float(rand() % 99);
    vZ = float(rand() % 99);
    
    // Set random cube angles
    angleX = float(rand() % 359);
    angleY = float(rand() % 359);
    angleZ = float(rand() % 359);
    
    // Set random cube radius
    r = float(rand() % 42) + 8.0;
    
    // 1D texture array of usigned bytes
    string file = "cats_dogs/" + name + num + ".jpg";// full file name
    char fileName[file.size()+1];
    strcpy(fileName, file.c_str());
    initTexture((char *)fileName, texture);// initialize texture unsigned byte array for this cube object
}

//================================
// Destructor
//================================
cubeTexture::~cubeTexture()
{
}
