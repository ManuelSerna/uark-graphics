//********************************
// Computer Graphics Project 3
// Author: Manuel Serna-Aguilera
// A sizable portion of this code was created by Dr. John M. Gauch
//********************************
#include <GL/glut.h> // OpenGL lib on Linux
#include <iostream>
#include <cmath>

// Global constants
// Drawing window coordinates
#define MIN_X_VIEW -50
#define MAX_X_VIEW 50

#define MIN_Y_VIEW -50
#define MAX_Y_VIEW 50

#define MIN_Z_VIEW -50
#define MAX_Z_VIEW 50

// OpenGL window coordinates
#define X_SCREEN 500
#define Y_SCREEN 500

#define SPEED 0.05

#define SLEEP_TIME 20

GLenum mode = GL_POLYGON;

// Global variables
float cubeX = 0.0;
float cubeY = 0.0;
float cubeSize = 5.0;
float cubeRotation = 15.0;// rotation of cube in deg

float vX = 0.0;
float vY = 0.0;

using namespace std;


//================================
// Get random number from range [min..max]
//================================
float getRandomValue(float min, float max)
{
	return rand() * (max - min) / RAND_MAX + min;
}


//================================
// Init function for OpenGL
//================================
void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	glEnable(GL_DEPTH_TEST);
	
	//vX = getRandomValue(-SPEED, SPEED);// start with random velocity
	//vY = getRandomValue(-SPEED, SPEED);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(MIN_X_VIEW, MAX_X_VIEW, MIN_Y_VIEW, MAX_Y_VIEW, MIN_Z_VIEW, MAX_Z_VIEW);
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
// Timer callback for OpenGL
//================================
void timer(int value)
{
	// TODO: simulate physics with timer OR idle callback
}


//================================
// Idle callback for OpenGL
//================================
void idle()
{
	float bounce = -1.0;

	// TODO: simulate physics with timer OR idle callback
	// Update velocity
	cubeX += vX;
	cubeY += vY;
	
	// Bounce off edges of drawing window
	//cout << cubeX << endl;
	if (cubeX < MIN_X_VIEW)
	{
		vX *= bounce;// hit left wall
	}
	if (cubeX > MAX_X_VIEW)
	{
		vX *= bounce;// hit right wall
	}
	if (cubeY < MIN_Y_VIEW)
	{
		vY *= bounce;// hit bottom of window
	}
	if (cubeY > MAX_Y_VIEW)
	{
		vY *= bounce;// hit top of window
	}

	// Redraw everything
	glutPostRedisplay();
}


//================================
// Mouse callback for OpenGL
//================================

// Capture mouse coordinates when button is pressed
float ix = 0.0;
float iy = 0.0;

void mouse(int button, int state, int x, int y)
{
    // Calculate scale factors
    float xScale = (MAX_X_VIEW - MIN_X_VIEW)/(float)X_SCREEN;
    float yScale = (MAX_Y_VIEW - MIN_Y_VIEW)/(float)Y_SCREEN;

    // When mouse button is clicked
    if (state == GLUT_DOWN)
    {
        cubeX = MIN_X_VIEW + x * xScale;
        cubeY = MIN_Y_VIEW + y * yScale;
        
        ix = MIN_X_VIEW + x * xScale;
		iy = MIN_Y_VIEW + y * yScale;
    }

    // TODO: When user lets go of button, launch brick
    // Mouse button let go
    if (state == GLUT_UP)
    {
    	//cout << "mouse let go!" << endl;
    	
    	vX = (cubeX - ix) / 100.0;
    	vY = (cubeY - iy) / 100.0;
    	
    	cubeX = ix;
    	cubeY = iy;
    }

    // Redraw everything
    glutPostRedisplay();
}


//================================
// Motion callback for OpenGL
//================================
void motion(int x, int y)
{
    // Calculate scale factors
    float xScale = (MAX_X_VIEW - MIN_X_VIEW)/(float)X_SCREEN;
    float yScale = (MAX_Y_VIEW - MIN_Y_VIEW)/(float)Y_SCREEN;

    // Handle mouse motion
    cubeX = MIN_X_VIEW + x * xScale;
    cubeY = MIN_Y_VIEW + y * yScale;
    
    // Redraw everything
    glutPostRedisplay();
}


//================================
// Display callback for OpenGL
//================================
void display()
{
	// Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Draw cube
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
    /*
    Properly draw--translate and rotate--the cube:
    	- Move cube center of mass back to origin
    	- Rotate by desired angle
    	- Finally, move cube center of mass back
    Recall: the last transformation applied in code is the one that's applied first
    */
    glTranslatef(cubeX, -cubeY, 0.0);// go back to original pos
	glRotatef(cubeRotation, 1.0, 1.0, 1.0);
	glTranslatef(-cubeX, cubeY, 0.0);// go to: origin
	
	cube(cubeX, -cubeY, 0.0, cubeSize);
	
	glFlush();
}


//================================
// Main
//================================
int main(int argc, char *argv[])
{
    // OpenGL setup
	glutInit(&argc, argv);
	glutInitWindowSize(X_SCREEN, Y_SCREEN);
	glutInitWindowPosition(80, 80);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutCreateWindow("Graphics Project 3--Serna-Aguilera");
	
    // OpenGL functions with callbacks
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutDisplayFunc(display);
    glutTimerFunc(SLEEP_TIME, timer, 0);

    init();
	glutMainLoop();

    return 0;
}
