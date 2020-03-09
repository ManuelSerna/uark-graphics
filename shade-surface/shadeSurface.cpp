//********************************
// Computer Graphics Project 4: Phong Shading
// Author: Manuel Serna-Aguilera
// Credit: libim library and image.cpp created by Dr. John Gauch
//********************************

#include <bits/stdc++.h> // for tokenizing strings
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <string>

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
#define XDIM 500
#define YDIM 500



// Image arrays
int image[YDIM][XDIM][3];
int depth[YDIM][XDIM];

// Surface rotation angle variables
float xAngle = 5.0;
float yAngle = 5.0;
float zAngle = 5.0;

using namespace std;

// DONE 1: read jpeg files with Dr. Gauch's code
// DONE 2: store depth data in a polygon mesh
//  - NOTE: scale depth values range: [0...255], image size: [0...499, 0...499]
//  - DONE 2.1: scale depth values into an appropriate range
// DONE 3: display the model surface.
// DONE 4: read the color image and store the color info
// intermediate TODO: correct surface storage and output, right now, I have the penny being mirrored when rendered
// TODO 5: with the color info saved, we can color the polygons on the penny surface with the color data (see project prompt for more info)
// TODO 6: display the image using phong shading (create a third callback for this)
// TODO 7: extend keyboard callback so user can switch between polygon mesh and shaded penny

//================================
// Read values from depth file
//================================
void readDepthData(string inputFile)
{
    // Counters for array
    int x = 0;
    int y = 0;
    
    // Calculate scale factor for thickness of penny
    float minZ = 0.0;// min z range for penny
    float maxZ = 9.9;// max z range for penny
    float zScale = (maxZ - minZ)/150.0;
    
    // Open depth file
    ifstream data;
    data.open(inputFile);
    
    string input;
    
    // Check if file read goes wrong
    if(!data)
    {
        cout << "Error: could not read file. Bailing.";
        return;
    }
    
    // Read depth file character by character
    // We are expecting a single line with many values in the range [0...255]
    if(data.is_open())
    {
        while(!data.eof())
        {
            data >> input;
            depth[y][x] = minZ + stof(input) * zScale;
            
            y++;

            if (y >= YDIM)
            {
                y = 0;
                x++;
            }
        }
    }
    
    data.close();
}



//================================
// Read values from color (RGB) file
//================================
void readImageData(string inputFile)
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
            
            // Populate color array contents
            image[y][x][0] = stof(tokens[0]);// r
            image[y][x][1] = stof(tokens[1]);// g
            image[y][x][2] = stof(tokens[2]);// b
            
            y++;
            
            if (y >= YDIM)
            {
                y = 0;
                x++;
            }
        }
    }
    
    data.close();
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
        MIN_X_VIEW, 
        MAX_X_VIEW, 
        MIN_Y_VIEW,  
        MAX_Y_VIEW, 
        MIN_Z_VIEW,
        MAX_Z_VIEW
    );
}



//================================
// Display surface only
//================================
void displaySurface(float xScale, float yScale)
{
    for (int x = 0; x < XDIM-1; x++)
    {
        for (int y = 0; y < YDIM-1; y++)
        {            
            glColor3f(1.0, 0.0, 0.0);
            
            // Get 3D point
            float tx = MIN_X_VIEW + x * xScale;
            float ty = MIN_Y_VIEW + y * yScale;
            float z1 = (float)(depth[y][x]);
            float z2 = (float)(depth[y][x+1]);
            float z3 = (float)(depth[y+1][x+1]);
            float z4 = (float)(depth[y+1][x]);
            
            glBegin(GL_LINE_LOOP);
            glVertex3f(tx, ty, z1);
            glVertex3f(tx, ty, z2);
            glVertex3f(tx, ty, z3);
            glVertex3f(tx, ty, z4);
            glEnd();
        }
    }
}

//================================
// Display surface with color
//================================
void displayColor(float xScale, float yScale)
{
    for (int x = 0; x < XDIM-1; x++)
    {
        for (int y = 0; y < YDIM-1; y++)
        {
            // Define color

            float r = (image[x][y][0] + image[x][y+1][0] + image[x+1][y+1][0] + image[x+1][y][0])/(4.0*255.0);
            float g = (image[x][y][1] + image[x][y+1][1] + image[x+1][y+1][1] + image[x+1][y][1])/(4.0*255.0);
            float b = (image[x][y][2] + image[x][y+1][2] + image[x+1][y+1][2] + image[x+1][y][2])/(4.0*255.0);
            
            glColor3f(r, g, b);
            
            // Get 3D points for 3D polygon
            float tx1 = MIN_X_VIEW + x * xScale;
            float ty1 = MIN_Y_VIEW + y * yScale;
            float z1 = (float)(depth[x][y]);
            
            float tx2 = MIN_X_VIEW + (x+1) * xScale;
            float ty2 = ty1;
            float z2 = (float)(depth[x+1][y]);
            
            float tx3 = tx2;
            float ty3 = MIN_Y_VIEW + (y+1) * yScale;
            float z3 = (float)(depth[x+1][y+1]);
            
            float tx4 = MIN_X_VIEW + x * xScale;
            float ty4 = ty3;
            float z4 = (float)(depth[x][y+1]);
            
            // Draw polygon patch
            glBegin(GL_POLYGON);
            
            glVertex3f(tx1, ty1, z1);
            glVertex3f(tx2, ty2, z2);
            glVertex3f(tx3, ty3, z3);
            glVertex3f(tx4, ty4, z4);
            
            glEnd();
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

    // Display object
    //displaySurface(xScale, yScale);
    displayColor(xScale, yScale);
    
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
    cout << "Reading in image data." << endl;
    
    readDepthData("penny-depth.txt");
    readImageData("penny-image.txt");

    cout << "Finished reading image data." << endl;

    glutInit(&argc, argv);
    glutInitWindowSize(X_SCREEN, Y_SCREEN);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Phong Shading");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    init();

    glutMainLoop();

    return 0;
}

