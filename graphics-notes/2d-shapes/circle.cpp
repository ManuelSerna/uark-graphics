//********************************
// Draw circle
// Author: Manuel Serna-Aguilera
//********************************

#include <math.h>
#ifdef MAC
#include <GLUT/glut.h> // MAC naming
#else
#include <GL/glut.h> // Linux naming
#endif

using namespace std;

const int FULL_CIRCLE_DEG = 360;
const int RADIUS = 20;

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

    // Display circle
    glColor3f(255, 255, 0);

    glBegin(GL_POLYGON);
    
    for (int t = 0; t < FULL_CIRCLE_DEG; t++)
    {
        float radians = M_PI * t / 180.0;
        float x = RADIUS * cos(radians);
        float y = RADIUS * sin(radians);
        
        glVertex2f(x, y);
    }
    
    glEnd();// end drawing shape
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(80, 80);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Window Title Here");
    init();
    glutDisplayFunc(display);
    glutMainLoop();// enter loop until user closes out of window
}
