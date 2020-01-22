//********************************
// Graphics Projeect 1: Charts
// Manuel Serna-Aguilera
//********************************

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

//GLenum mode = GL_LINE_LOOP;

//================================
// Init function for OpenGL
//================================
void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//================================
// TODO: Draw dot chart
// TODO: Generalize for input
//================================
void dot()
{
	// Color values
	float red = 1.0;
	float green = 0.0;
	float blue = 0.0;

	// Sizes of x and y dims of circle
	float mx = 0.02;
	float my = 0.02;

	// Translation values for x and y dims
	//float bx = -0.0;
	//float by = -0.0;

	// Draw a circle to represent a bigger dot
	glBegin(GL_POLYGON);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);// ???
	glColor3f(red, green, blue);
	
	// Draw 360 vertices to create circle
	for(int t = 0; t < 360; t++)
	{
		float radians = M_PI * t/180.0;
		float x = mx * cos(radians);
		float y = my * sin(radians);
		//printf("%f %f \n", x, y);
		glVertex2f(x, y);
	}
	
	glEnd();
	glFlush();
}

//================================
// TODO: Draw column chart
// TODO: Generalize for input
//================================
void column()
{
	// Color values
	float red = 0.0;
	float green = 1.0;
	float blue = 1.0;

	// Coords for rectangle
	float x1 = 0.0;
	float y1 = 0.5;
	float x2 = 0.25;
	float y2 = -0.25;

	glBegin(GL_POLYGON);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);// ???
	//glOrtho(MIN_X_VIEW, MAX_X_VIEW, MIN_Y_VIEW, MAX_Y_VIEW, MIN_Z_VIEW, MAX_Z_VIEW);
	
	glColor3f(red, green, blue);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	
	glEnd();
}


// TODO: Draw line chart
// TODO: Draw area chart

//================================
// Display callback for OpenGL
// Purpose: tell the OpenGL what we want to display on window here
//================================
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	// TODO: place draw functions here
	//dot();
	column();
	glFlush();
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
	glutCreateWindow("Graphics Project 1-Manuel Serna-Aguilera");

	// Tell OpenGL
	glutDisplayFunc(display);

	init();

	glutMainLoop();

	// Printing a string a chars iwth stdio
	//printf("%s \n", "Hello mom!");

	return 0;
}
