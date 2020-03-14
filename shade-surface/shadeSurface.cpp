//********************************
// Computer Graphics Project 4: Phong Shading
// Author: Manuel Serna-Aguilera
// Credit: libim and jpeg library, image.cpp, and shading.cpp created by Dr. John Gauch
//********************************

#include <bits/stdc++.h> // for tokenizing strings
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <string>

#include "shading.cpp"

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

// Image dimensions
#define XDIM 500
#define YDIM 500
#define ZDIM 500

// Image arrays
int image[YDIM][XDIM][3];// store color
int depth[YDIM][XDIM];// store depth

// Surface normal arrays for x, y, and z axes
float normX[YDIM][XDIM];
float normY[YDIM][XDIM];
float normZ[YDIM][XDIM];

// Surface rotation angle variables
float xAngle = 5.0;
float yAngle = 5.0;
float zAngle = 5.0;

// User choice for display
char choice = '1';// default choice is wireframe

using namespace std;

// DONE 1: read jpeg files with Dr. Gauch's img processing code
// DONE 2: store depth data in a polygon mesh
//  - NOTE: scale depth values range: [0...255], image size: [0...499, 0...499]
//  - DONE 2.1: scale depth values into an appropriate range
// DONE 3: display the model surface.
// DONE 4: read the color image and store the color info
// intermediate DONE: correct surface storage and output, right now, I have the penny being mirrored when rendered
// DONE 5: with the color info saved, we can color the polygons on the penny surface with the color data (see project prompt for more info)
// DONE 6: display the image using phong shading (create a third callback for this)
// DONE 7: extend keyboard callback so user can switch between polygon mesh and shaded penny



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
    float maxZ = 29.9;// max z range for penny
    float zScale = (maxZ - minZ)/((MAX_Z_VIEW-MIN_Z_VIEW)/2.0);
    
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
    
    // Calculate scale factors
    float xScale = (MAX_X_VIEW - MIN_X_VIEW)/float(X_SCREEN);
    float yScale = (MAX_Y_VIEW - MIN_Y_VIEW)/float(Y_SCREEN);
    
    // Calculate surface normal vectors at each point
    for (int y = 0; y < YDIM-1; y++)
    {
        for (int x = 0; x < XDIM-1; x++)
        {
            // Calculate basis vectors v1 and v2 for surface patch
            // First point for basis vectors
            float tx1 = MIN_X_VIEW + x * xScale;
            float ty1 = MIN_Y_VIEW + y * yScale;
            float z1 = (float)(depth[y][x]);
            
            // Calculate v1
            // Endpoint for first vector v1 = [v1x,v1y,v1z]
            float tx2 = MIN_X_VIEW + (x+1) * xScale;
            float ty2 = ty1;
            float z2 = (float)(depth[y+1][x]);
            float v1x = tx2 - tx1;
            float v1y = ty2 - ty1;
            float v1z = z2 - z1;
            
            // Endpoint for second vector v2 = [v2x,v2y,v2z]
            float tx4 = tx1;
            float ty4 = MIN_Y_VIEW + (y+1) * yScale;
            float z4 = (float)(depth[y][x+1]);
            float v2x = tx4 - tx1;
            float v2y = ty4 - ty1;
            float v2z = z4 - z1;
            
            // Use cross product to get normal x,y,z components
            normX[y][x] = v1y*v2z - v1z*v2y;
            normY[y][x] = v1x*v2z - v1z*v2x;
            normZ[y][x] = v1x*v2y - v1y*v2x;
        }
    }
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
        MIN_X_VIEW*3/2, MAX_X_VIEW*3/2, 
        MIN_Y_VIEW*3/2, MAX_Y_VIEW*3/2, 
        MIN_Z_VIEW*3/2, MAX_Z_VIEW*3/2
    );
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    
    // Phong Shading setup
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
}



//================================
// Display surface only
//================================
void displaySurface(float xScale, float yScale)
{
    int step = 6;
    
    glColor3f(1.0, 0.0, 0.0);
    
    for (int y = 0; y < YDIM-1; y++)
    {
        for (int x = 0; x < XDIM-1; x++)
        {
            if (x % step == 0)
            {
                // Get 3D patch for surface
                float tx1 = MIN_X_VIEW + x * xScale;
                float ty1 = MIN_Y_VIEW + y * yScale;
                float z1 = (float)(depth[y][x]);

                float tx2 = MIN_X_VIEW + (x+1) * xScale;
                float ty2 = ty1;
                float z2 = (float)(depth[y+1][x]);

                float tx3 = tx2;
                float ty3 = MIN_Y_VIEW + (y+1) * yScale;
                float z3 = (float)(depth[y+1][x+1]);

                float tx4 = MIN_X_VIEW + x * xScale;
                float ty4 = ty3;
                float z4 = (float)(depth[y][x+1]);
                
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
// Display surface with color
//================================
void displayColor(float xScale, float yScale)
{
    for (int y = 0; y < YDIM-1; y++)
    {
        for (int x = 0; x < XDIM-1; x++)
        {
            // Define color
            float r = (image[y][x][0] + image[y][x+1][0] + image[y+1][x+1][0] + image[y+1][x][0])/(4.0*255.0);
            float g = (image[y][x][1] + image[y][x+1][1] + image[y+1][x+1][1] + image[y+1][x][1])/(4.0*255.0);
            float b = (image[y][x][2] + image[y][x+1][2] + image[y+1][x+1][2] + image[y+1][x][2])/(4.0*255.0);
            
            glColor3f(r, g, b);
            
            // Get 3D points for 3D polygon
            float tx1 = MIN_X_VIEW + x * xScale;
            float ty1 = MIN_Y_VIEW + y * yScale;
            float z1 = (float)(depth[y][x]);

            float tx2 = MIN_X_VIEW + (x+1) * xScale;
            float ty2 = ty1;
            float z2 = (float)(depth[y+1][x]);

            float tx3 = tx2;
            float ty3 = MIN_Y_VIEW + (y+1) * yScale;
            float z3 = (float)(depth[y+1][x+1]);

            float tx4 = MIN_X_VIEW + x * xScale;
            float ty4 = ty3;
            float z4 = (float)(depth[y][x+1]);
            
            // Draw polygon patch
            glBegin(GL_POLYGON);
            
            glVertex3f(ty1, tx1, z1);
            glVertex3f(ty2, tx2, z2);
            glVertex3f(ty3, tx3, z3);
            glVertex3f(ty4, tx4, z4);
            
            glEnd();
        }
    }
}

//================================
// Display surface with Phong shading
//================================
void displayPhong(float xScale, float yScale)
{    
    for (int y = 0; y < YDIM-1; y++)
    {
        for (int x = 0; x < XDIM-1; x++)
        {
            // Get 3D points for 3D polygon
            float tx1 = MIN_X_VIEW + x * xScale;
            float ty1 = MIN_Y_VIEW + y * yScale;
            float z1 = (float)(depth[y][x]);

            float tx2 = MIN_X_VIEW + (x+1) * xScale;
            float ty2 = ty1;
            float z2 = (float)(depth[y+1][x]);

            float tx3 = tx2;
            float ty3 = MIN_Y_VIEW + (y+1) * yScale;
            float z3 = (float)(depth[y+1][x+1]);

            float tx4 = MIN_X_VIEW + x * xScale;
            float ty4 = ty3;
            float z4 = (float)(depth[y][x+1]);
            
            // Draw normals and polygon patch
            glBegin(GL_POLYGON);
            glNormal3f(normX[y][x], normY[y][x], normZ[y][x]);
            glVertex3f(ty1, tx1, z1);
            glNormal3f(normX[y+1][x], normY[y+1][x], normZ[y+1][x]);
            glVertex3f(ty2, tx2, z2);
            glNormal3f(normX[y+1][x+1], normY[y+1][x+1], normZ[y+1][x+1]);
            glVertex3f(ty3, tx3, z3);
            glNormal3f(normX[y][x+1], normY[y][x+1], normZ[y][x+1]);
            glVertex3f(ty4, tx4, z4);
            
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

    // Display object according to user choice
    if (choice == '1')
    {
        glDisable(GL_LIGHTING);
        displaySurface(xScale, yScale);
    }
    else if (choice == '2')
    {
        glDisable(GL_LIGHTING);
        displayColor(xScale, yScale);
    }
    else
    {
        // Initialize material properties for Phong shading (lighting re-enabled in keyboard callback so as to not keep calling it in the display)
        init_material(Ka, Kd, Ks, 100 * Kp, 0.8, 0.6, 0.4);
        displayPhong(xScale, yScale);
    }
    
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
    
    // Toggle between displays via user interface (on cmd)
    if (key == '1')
    {
        // Display wireframe of penny
        cout << "  Displaying wire-frame of object.\n";
        choice = key;
    }
    else if (key == '2')
    {
        // Display colored penny
        cout << "  Displaying colored object.\n";
        choice = key;
    }
    else if (key == '3')
    {
        // Display with Phong shading
        cout << "  Displaying object with Phong shading.\n";
        choice = key;
        
        // Re-enable lighting
        init_light(GL_LIGHT0, 0, 1, 1, 0.5, 0.5, 0.5);
        init_light(GL_LIGHT1, 0, 0, 1, 0.5, 0.5, 0.5);
        init_light(GL_LIGHT2, 0, 1, 0, 0.5, 0.5, 0.5);
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

