//********************************
// CSCE 4813 Computer Graphics Projeect 1: Charts
// Manuel Serna-Aguilera
//********************************

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

// Global constants, all lower bounds are zero in order for scaling to work
#define MIN_X_VIEW 0
#define MAX_X_VIEW 100
#define MIN_Y_VIEW 0
#define MAX_Y_VIEW 100
#define MIN_Z_VIEW 0
#define MAX_Z_VIEW 1

#define PTS 5

// Global variables
float X[PTS];
float Y[PTS];
float color[3];// hold RGB values
char choice;



//================================
// Normalize color values
//================================
float normalize(float x)
{
	float z = x/255;
	return z;
}



//================================
// Return max value from an array A
//================================
float getMax(float A[])
{
	float max = -INFINITY;
	
	for(int i = 0; i < PTS; i++)
	{
		if(max < A[i])
		{
			max = A[i];
		}
	}
	
	return max;
}



//================================
// Transformation functions
/*
	input range:  [a..b] = [min..max]
	output range: [c..d] = [MIN_VIEW..MAX_VIEW]
	out =         (d - c)(input pt - a)/(b - a) + c
*/
// Input: some x or y component of a point, and upper and lower bounds of array
// Return: adjusted x or y so it can fit in window
//================================
float transformX(float x, float minX, float maxX)
{
	float out = ((MAX_X_VIEW) * (x - minX))/(maxX - minX);
	return out;
}

float transformY(float y, float minY, float maxY)
{	
	float out = ((MAX_Y_VIEW) * (y - minY))/(maxY - minY);
	return out;
}



//================================
// Init function for OpenGL
/*
	Purpose: Aside from OpenGL setup, init() will zero
	initialize the X and Y arrays. It will also read data.txt 
	to read in color values and coordinate info. Finally,
	scale the coordinates for the drawing window (since point
	positions will be the same regardless of chart type).
*/
//================================
void init()
{
	//---------------------------------
	// Set up for OpenGL
	//---------------------------------
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(MIN_X_VIEW, MAX_X_VIEW, 
			MIN_Y_VIEW, MAX_Y_VIEW, 
			MIN_Z_VIEW, MAX_Z_VIEW);// define drawing window
	glEnable(GL_DEPTH_TEST);
	
	// Clear global arrays
	for(int i = 0; i < PTS; i++)
	{
		X[i] = 0.0;
		Y[i] = 0.0;
	}
	
	//---------------------------------
	// Take in raw input from data.txt
	//---------------------------------
	FILE *data = fopen("data.txt", "r");
	
	// First line: color info
	if(fscanf(data, "%f %f %f\n", &color[0], &color[1], &color[2]) != 3)
	{
		printf("Error: could not execute fscanf command (color).\n");
	}
	
	// All subsequent lines: points (x, y) for graph
	for(int i = 0; i < PTS; i++)
	{
		if(fscanf(data, "%f %f\n", &X[i], &Y[i]) != 2)
		{
			printf("Error: could not execute fscanf command (vertices).\n");
		}
	}
	
	fclose(data);
	
	//---------------------------------
	// Transform X and Y
	//---------------------------------
	float padX = 5.0;// pad with space so data doesn't appear at very edge of window
	float maxX = getMax(X) + padX;
	float minX = 0;// graph will always start at zero
	
	float padY = 5.0;
	float maxY = getMax(Y) + padY;
	float minY = 0;
	
	for(int i = 0; i < PTS; i++)
	{
		X[i] = transformX(X[i], minX, maxX);
		Y[i] = transformY(Y[i], minY, maxY);
	}
	
	// Initialize choice	
	choice = 'x';
	
	// Normalize colors
	color[0] = normalize(color[0]);
	color[1] = normalize(color[1]);
	color[2] = normalize(color[2]);
}

//--------------------------------
// Draw dot chart
//--------------------------------
void dot()
{
	float red = color[0];
	float green = color[1];
	float blue = color[2];
	
	glColor3f(red, green, blue);

	// Adjust size of rectangles here
	float xSize = 1.0;
	float ySize = 1.0;
	
	// Draw little squares according to transformed coords
	for(int i = 0; i < PTS; i++)
	{
		// TODO: use primitive GL_POINTS instead of polygon primitive, then all I will need will be coords
		glBegin(GL_POLYGON);
		
		float x1 = X[i];
		float y1 = Y[i];
		float x2 = x1 + xSize;
		float y2 = y1 + ySize;
		
		glVertex2f(x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glVertex2f(x1, y2);
		
		glEnd();
	}
	
	glFlush();
}

//--------------------------------
// Draw column chart
//--------------------------------
void column()
{
	float red = color[0];
	float green = color[1];
	float blue = color[2];
	
	glColor3f(red, green, blue);
	
	// Adjust size of columns
	float colW = 4.0;
	
	// Draw columns
	for(int i = 0; i < PTS; i++)
	{
		glBegin(GL_POLYGON);
		
		float x1 = X[i];
		float y1 = Y[i];
		float x2 = x1 + colW;
		float y2 = 1.0;
		
		glVertex2f(x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glVertex2f(x1, y2);
		
		glEnd();
	}
}

//--------------------------------
// Draw line chart
//--------------------------------
void line()
{
	float red = color[0];
	float green = color[1];
	float blue = color[2];
	
	glColor3f(red, green, blue);

	glLineWidth(1);
	
	glBegin(GL_LINE_STRIP);

	for (int i = 0; i < PTS; i++)
	{
		glVertex2f(X[i], Y[i]);
	}

	glEnd();
}

//--------------------------------
// Draw area chart
//--------------------------------
void area()
{
	float red = color[0];
	float green = color[1];
	float blue = color[2];
	
	glColor3f(red, green, blue);
	
	glBegin(GL_POLYGON);
	
	glVertex2f(X[0], 1);
	
	for (int i = 0; i < PTS; i++)
	{
		glVertex2f(X[i], Y[i]);
	}
	
	// Create a vertex in the lower-right corner to complete the area chart
	glVertex2f(X[PTS-1], 1);
	
	glEnd();
}

//================================
// Display callback for OpenGL
// Purpose: tell the OpenGL what we want to display on window here
//================================
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	// Draw according to user input
	switch(choice)
	{
		case 'd':
			dot();
			break;
		case 'c':
			column();
			break;
		case 'l':
			line();
			break;
		case 'a':
			area();
			break;
		default:
			// do nothing for incorrect input
			break;
	}
	
	glFlush();// make sure objects are drawn
}



//================================
// Keyboard callback for OpenGL
/*
	TODO: take in user input from file
	TODO: adjust colors in each function
*/
//================================
void keyboard(unsigned char key, int x, int y)
{
	if(key == 'x')
	{
		// clear display
	}
	else if(key == 'd')
	{
		choice = 'd';// draw dot
	}
	else if(key == 'c')
	{
		choice = 'c';// draw column
	}
	else if(key == 'l')
	{
		choice = 'l';// draw line
	}
	else if(key == 'a')
	{
		choice = 'a';// draw area chart
	}
	
	// Redraw objects
	glutPostRedisplay();
}



//================================
// Ask user for input
//================================
void prompt()
{
	printf("\nPlease select a chart type:\n");
	printf("  'd' = dot chart\n");
	printf("  'c' = column chart\n");
	printf("  'l' = line chart\n");
	printf("  'a' = area chart\n");
}



//================================
// Main
//================================
int main(int argc, char *argv[])
{
	// Use the below method to initialize the GLUT library
	//   &argc: pointer to command line options intented for GLUT,
	//   argv: another command line argument that GLUT also processes
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);// window size
	glutInitWindowPosition(80, 80);// TL corner of window
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Graphics Project 1: Manuel Serna-Aguilera");
	
	// Prompt user and get input
	prompt();
	glutKeyboardFunc(keyboard);
	
	init();
	glutDisplayFunc(display);// tell OpenGL to display our drawings
	glutMainLoop();// event-handling function, no more code goes after this

	return 0;
}
