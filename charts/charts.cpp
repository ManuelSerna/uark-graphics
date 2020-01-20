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
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

//================================
// Display callback for OpenGL
// Purpose: tell the OpenGL what we want to display on window here
//================================
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	// draw functions here
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
	glutInitWindowPosition(250, 250);

	
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Test 123");

	// Tell OpenGL
	glutDisplayFunc(display);

	init();

	glutMainLoop();

	return 0;
}
