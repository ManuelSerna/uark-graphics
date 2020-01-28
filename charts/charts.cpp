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
float color[3];// hold RGB valuess



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
// Input: some x or y component of a point
// Return: adjusted x or y so it can fit in window
//================================
float transformX(float x)
{
	float padX = 5.0;// pad with space so data doesn't appear at very edge of window
	float maxX = getMax(X) + padX;
	float minX = 0;// graph will always start at zero
	float out = ((MAX_X_VIEW) * (x - minX))/(maxX - minX);
	return out;
}

float transformY(float y)
{	
	float padY = 5.0;
	float maxY = getMax(Y) + padY;
	float minY = 0;
	float out = ((MAX_Y_VIEW) * (y - minY))/(maxY - minY);
	return out;
}



//================================
// Init function for OpenGL
//================================
void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(MIN_X_VIEW, MAX_X_VIEW, 
			MIN_Y_VIEW, MAX_Y_VIEW, 
			MIN_Z_VIEW, MAX_Z_VIEW);// define area that one can draw in
	glEnable(GL_DEPTH_TEST);
	
	// Clear global arrays
	for(int i = 0; i < PTS; i++)
	{
		X[i] = 0.0;
		Y[i] = 0.0;
	}
	
	color[0] = 0.0;
	color[1] = 0.0;
	color[2] = 0.0;
}

//--------------------------------
// Draw dot chart
//--------------------------------
void dot()
{
	// Color values
	float red = 0.0;
	float green = 1.0;
	float blue = 1.0;
	
	glColor3f(red, green, blue);

	// Adjust size of rectangles here
	float xSize = 1.0;
	float ySize = 1.0;
	
	// Draw little squares according to transformed coords
	for(int i = 0; i < PTS; i++)
	{
		// TODO: use primitive GL_POINTS instead of polygon primitive, then all I will need will to coords
		glBegin(GL_POLYGON);
		
		float x = transformX(X[i]);
		float y = transformY(Y[i]);
		
		float x1 = x;
		float y1 = y;
		float x2 = x + xSize;
		float y2 = y + ySize;
		
		
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
	// Color values
	float red = 1.0;
	float green = 1.0;
	float blue = 0.0;
	glColor3f(red, green, blue);
	
	// Adjust size of columns
	float colW = 4.0;
	
	// Draw columns
	for(int i = 0; i < PTS; i++)
	{
		glBegin(GL_POLYGON);
		
		float x = transformX(X[i]);
		float y = transformY(Y[i]);
		
		float x1 = x;
		float y1 = y;
		float x2 = x + colW;
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
	// Color values
	float red = 0.0;
	float green = 1.0;
	float blue = 0.0;
	glColor3f(red, green, blue);

	glLineWidth(1);
	
	glBegin(GL_LINE_STRIP);

	for (int i = 0; i < PTS; i++)
	{
		float x = transformX(X[i]);
		float y = transformY(Y[i]);
		glVertex2f(x, y);
	}

	glEnd();
}

//--------------------------------
// Draw area chart
//--------------------------------
void area()
{
	// Color values
	float red = 1.0;
	float green = 0.0;
	float blue = 1.0;
	glColor3f(red, green, blue);
	
	glBegin(GL_POLYGON);
	
	glVertex2f(transformX(X[0]), 1);
	
	for (int i = 0; i < PTS; i++)
	{
		float x = transformX(X[i]);
		float y = transformY(Y[i]);
		glVertex2f(x, y);
	}
	
	// Create a vertex in the lower-right corner to complete the area chart
	glVertex2f(transformX(X[PTS-1]), 1);
	
	glEnd();
}

//================================
// Display callback for OpenGL
// Purpose: tell the OpenGL what we want to display on window here
//================================
void display()
{
	// Manually set points for now
	/*
	X[0] = 10.0;
	X[1] = 20.0;
	X[2] = 30.0;
	X[3] = 40.0;
	X[4] = 50.0;
	
	Y[0] = 10.0;
	Y[1] = 25.0;
	Y[2] = 35.0;
	Y[3] = 40.0;
	Y[4] = 42.0;
	//*/

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	dot();
	column();
	line();
	//area();
	
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
	if(key == 'h')
	{
		printf("hello mom");
	}
	
	// TODO: it seems like I will do file i/o here
	
	// Redraw objects
	//glutPostRedisplay();
	
	
	/*
	 // Read point array
	FILE *fd = fopen("rectangle.txt", "r");
	if (fscanf(fd, "%d\n", &count) != 1)
		printf("Error: could not execute fscanf command\n");
	for (int i=0; i<count; i++)
		if (fscanf(fd, "%f %f %f %f %f %f %f\n",
		&color[i][0], &color[i][1], &color[i][2],
		&point[i][0], &point[i][1], &point[i][2], &point[i][3]) != 7)
			printf("Error: could not execute fscanf command\n");
	fclose(fd);
	*/
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

	// Declare window size
	glutInitWindowSize(500, 500);

	// Declare location of top-left corner of window
	glutInitWindowPosition(80, 80);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Graphics Project 1: Manuel Serna-Aguilera");
	init();
	prompt();

	// Tell OpenGL to display our drawings
	glutDisplayFunc(display);
	
	// TODO: take in data from file
	glutKeyboardFunc(keyboard);
	
	glutMainLoop();// event-handling function, no more code goes after this

	return 0;
}
