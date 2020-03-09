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
#define MIN_X_VIEW -25
#define MAX_X_VIEW 25
#define MIN_Y_VIEW -25
#define MAX_Y_VIEW 25
#define MIN_Z_VIEW -10 // TODO: adjust z-boundaries alongside z-scaling to not have the penny be so thick
#define MAX_Z_VIEW 10

// OpenGL window coordinates
#define X_SCREEN 500
#define Y_SCREEN 500

// Image dimensions
#define XDIM 500
#define YDIM 500



// Image arrays
int image[YDIM][XDIM][3];
int depth[YDIM][XDIM];

// Surface angle variables
float xAngle = 5.0;
float yAngle = 5.0;
float zAngle = 5.0;

using namespace std;

// OPTIONAL TODO: load penny in correct orientation(?), right now it is being shown upside down
// DONE 2: store depth data in a polygon mesh
//  - NOTE: scale depth values range: [0...255], image size: [0...499, 0...499]
//  - DONE 2.1: scale depth values into an appropriate range
// DONE 3: display the model surface.
// DONE 4: read the color image and store the color info
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
    
    // Calculate scale factor for depth (for z-axis)
    // TODO: adjust z-scaling so penny does not appear thick
    float zScale = (MAX_Z_VIEW - MIN_Z_VIEW)/float(X_SCREEN);
    
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
            depth[y][x] = MIN_Z_VIEW + stof(input) * zScale;
            
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
	
	// Calculate scale factors
	float xScale = (MAX_X_VIEW - MIN_X_VIEW)/(float)X_SCREEN;
	float yScale = (MAX_Y_VIEW - MIN_Y_VIEW)/(float)Y_SCREEN;
	
	for (int x = 0; x < XDIM-1; x++)
	{
	    for (int y = 0; y < YDIM-1; y++)
	    {
        	float tx = MIN_X_VIEW + x * xScale;
        	float ty = MIN_Y_VIEW + y * yScale;
	        
	        glBegin(GL_LINE_LOOP);
	        glColor3f(1.0, 0.0, 0.0);
	        glVertex3f(tx, ty, (float)(depth[y][x]));
	        glVertex3f(tx, ty, (float)(depth[y][x+1]));
	        glVertex3f(tx, ty, (float)(depth[y+1][x+1]));
	        glVertex3f(tx, ty, (float)(depth[y+1][x]));
	        glEnd();
	    }
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
    
    // Redraw everything
    glutPostRedisplay();
}



//================================
// Main
//================================
int main(int argc, char *argv[])
{
    readDepthData("penny-depth.txt");
	readImageData("penny-image.txt");
    
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
