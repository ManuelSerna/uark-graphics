//********************************
// Draw rectangle
// Author: Manuel Serna-Aguilera
//********************************

#ifdef MAC
#include <GLUT/glut.h> // MAC naming
#else
#include <GL/glut.h> // Linux naming
#endif

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
    glColor3f(255, 0, 0);

    glBegin(GL_POLYGON);
        
    glVertex2f(20, 20);
    glVertex2f(-20, 20);
    glVertex2f(-20, -20);
    glVertex2f(20, -20);

    glEnd();// end drawing polygon
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);// start with init callback
    glutInitWindowSize(500, 500);// set window size
    glutInitWindowPosition(80, 80);// set window position (upper left corner)
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Window Title Here");
    init();
    glutDisplayFunc(display);// call display callback (i.e. what we want to display)
    glutMainLoop();// enter loop until user closes out of window (no other code follows this line)
}
