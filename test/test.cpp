// Test OpenGL

#include <GL/glut.h> // OpenGL lib on Linux

using namespace std;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100, 100, -100, 100, -100, 100);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	// Display square
	glColor3f(255, 0, 255);
	
	glBegin(GL_POLYGON);
		
	glVertex2f(20, 20);
	glVertex2f(-20, 20);
	glVertex2f(-20, -20);
	glVertex2f(20, -20);
	
	glEnd();
	
	glFlush();
}



int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(80, 80);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("test window");
	init();
	glutDisplayFunc(display);
	glutMainLoop();// enter loop until user closes out of window
}
