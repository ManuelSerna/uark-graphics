//********************************
// Computer Graphics Project 2
// Author: Manuel Serna-Aguilera
//********************************
#include <GL/glut.h> // OpenGL lib on Linux
#include <iostream>
#include <cmath>

// Global constants
// Drawing window coordinates
#define MIN_X_VIEW 0
#define MAX_X_VIEW 100

#define MIN_Y_VIEW 0
#define MAX_Y_VIEW 100

#define MIN_Z_VIEW 0
#define MAX_Z_VIEW 100

// OpenGL window coordinates
#define X_SCREEN 500
#define Y_SCREEN 500

GLenum mode = GL_POLYGON;

// Global variables
float cubeX;
float cubeY;
float cubeSize = 5.0;

using namespace std;


//================================
// Transformation functions
/*
	input range:  [a..b] = [0..WINDOWX/Y]
	output range: [c..d] = [MINX/Y..MAXX/Y]
	out =         (d - c)(input pt - a)/(b - a) + c
*/
// Return: adjusted x or y so it can fit in drawing window
//================================
/*
float transformX(float x)
{
    float out = ((MAXX - MINX) * x / X_SCREEN) + MINX;
    return out;
}

float transformY(float y)
{	
	float out = ((MAXY - MINY) * y / Y_SCREEN) + MINY;
    return -1.0 * out;
}//*/


//================================
// Init function for OpenGL
//================================
void init()
{
    // Initialize cube coordinates
    cubeX = 0.0;//transformX(0.0);
    cubeY = 0.0;//transformY(0.0);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(MIN_X_VIEW, MAX_X_VIEW, MIN_Y_VIEW, MAX_Y_VIEW, MIN_Z_VIEW, MAX_Z_VIEW);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(30.0, 1.0, 1.0, 1.0);// 1st param: angle of rotation (deg)
	glEnable(GL_DEPTH_TEST);
}


//================================
// Draw cube
//================================
void cube(float midx, float midy, float midz, float size)
{
   // Define 8 vertices
   float ax = midx - size / 2;
   float ay = midy - size / 2;
   float az = midz + size / 2;

   float bx = midx + size / 2;
   float by = midy - size / 2;
   float bz = midz + size / 2;

   float cx = midx + size / 2;
   float cy = midy + size / 2;
   float cz = midz + size / 2;

   float dx = midx - size / 2;
   float dy = midy + size / 2;
   float dz = midz + size / 2;

   float ex = midx - size / 2;
   float ey = midy - size / 2;
   float ez = midz - size / 2;

   float fx = midx + size / 2;
   float fy = midy - size / 2;
   float fz = midz - size / 2;

   float gx = midx + size / 2;
   float gy = midy + size / 2;
   float gz = midz - size / 2;

   float hx = midx - size / 2;
   float hy = midy + size / 2;
   float hz = midz - size / 2;

   // Draw 6 faces
   glBegin(mode);
   glColor3f(1.0, 0.0, 0.0);
   glVertex3f(ax, ay, az);
   glVertex3f(bx, by, bz);
   glVertex3f(cx, cy, cz);
   glVertex3f(dx, dy, dz);
   glEnd();

   glBegin(mode);
   glColor3f(0.0, 1.0, 0.0);
   glVertex3f(ax, ay, az);
   glVertex3f(dx, dy, dz);
   glVertex3f(hx, hy, hz);
   glVertex3f(ex, ey, ez);
   glEnd();

   glBegin(mode);
   glColor3f(0.0, 0.0, 1.0);
   glVertex3f(ax, ay, az);
   glVertex3f(ex, ey, ez);
   glVertex3f(fx, fy, fz);
   glVertex3f(bx, by, bz);
   glEnd();

   glBegin(mode);
   glColor3f(0.0, 1.0, 1.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(fx, fy, fz);
   glVertex3f(ex, ey, ez);
   glVertex3f(hx, hy, hz);
   glEnd();

   glBegin(mode);
   glColor3f(1.0, 0.0, 1.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(cx, cy, cz);
   glVertex3f(bx, by, bz);
   glVertex3f(fx, fy, fz);
   glEnd();

   glBegin(mode);
   glColor3f(1.0, 1.0, 0.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(hx, hy, hz);
   glVertex3f(dx, dy, dz);
   glVertex3f(cx, cy, cz);
   glEnd();
}


//================================
// Mouse callback for OpenGL
//================================
void mouse(int button, int state, int x, int y)
{
    //float x_scale = (MAX_X_VIEW - MIN_X_VIEW) / (float)(MAX_X_SCREEN - MIN_X_SCREEN);
    //point[count][0] = MIN_X_VIEW + (x - MIN_X_SCREEN) * x_scale;

    float xScale = (MAX_X_VIEW - MIN_X_VIEW)/(float)X_SCREEN;
    float yScale = (MAX_Y_VIEW - MIN_Y_VIEW)/(float)Y_SCREEN;

    // When mouse button is clicked
    if (state == GLUT_DOWN)
    {
        // Transform coordinates
        //cubeX = transformX(x);
        cubeX = MIN_X_VIEW + x * xScale;
        cubeY = MIN_Y_VIEW + y * yScale;
    }

    // Update display
    glutPostRedisplay();
}


//================================
// Display callback for OpenGL
//================================
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
    
	cube(cubeX, cubeY, 0.0, cubeSize);
	
	glFlush();
}


//================================
// Main
//================================
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(X_SCREEN, Y_SCREEN);
	glutInitWindowPosition(80, 80);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutCreateWindow("Graphics Project 2--Serna-Aguilera");
	init();
	//glutIdleFunc(idle):// TODO: maybe include idle callback
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	glutMainLoop();// enter loop until user closes out of window
}
