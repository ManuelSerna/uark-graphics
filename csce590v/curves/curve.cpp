//---------------------------------------
// Program: curve.cpp
// Purpose: Demonstrate interactive drawing 
//          of four types of curves.
// Author:  John Gauch
// Date:    Spring 2013
// Catmull-Rom spline added by: Manuel Serna-Aguilera
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Global constants
#define MIN_X_VIEW -50
#define MAX_X_VIEW 50
#define MIN_Y_VIEW -50
#define MAX_Y_VIEW 50
#define MIN_Z_VIEW -50
#define MAX_Z_VIEW 50
#define MIN_X_SCREEN 0
#define MAX_X_SCREEN 800
#define MIN_Y_SCREEN 0
#define MAX_Y_SCREEN 800
#define LINE_COUNT 1000
#define LINE 0
#define CURVE 1
#define BEZIER 2
#define SPLINE 3
#define CATMULL_ROM 4

// Global variables 
int count = -1;
int mode = LINE;
float X[LINE_COUNT];
float Y[LINE_COUNT];

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(MIN_X_VIEW, MAX_X_VIEW, 
      MIN_Y_VIEW, MAX_Y_VIEW, 
      MIN_Z_VIEW, MAX_Z_VIEW);
   glEnable(GL_DEPTH_TEST);
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
    // Change drawing mode
    if ((key == 'l') || (key == 'L'))
        mode = LINE;
    else if ((key == 'i') || (key == 'I'))
        mode = CURVE;
    else if ((key == 'b') || (key == 'B'))
        mode = BEZIER;
    else if ((key == 's') || (key == 'S'))
        mode = SPLINE;
    else if ((key == 'c') || (key == 'C'))
        mode = CATMULL_ROM;
   
   // Redraw objects
   glutPostRedisplay();
}

//---------------------------------------
// Mouse callback for OpenGL
//---------------------------------------
void mouse(int button, int state, int x, int y)
{
   // Calculate scale factors
   float x_scale = (MAX_X_VIEW - MIN_X_VIEW) / 
      (float)(MAX_X_SCREEN - MIN_X_SCREEN);
   float y_scale = (MIN_Y_VIEW - MAX_Y_VIEW) / 
      (float)(MAX_Y_SCREEN - MIN_Y_SCREEN);

   // Handle mouse down
   if (state == GLUT_DOWN)
   {
      count++; 
      X[count] = MIN_X_VIEW + (x - MIN_X_SCREEN) * x_scale;
      Y[count] = MAX_Y_VIEW + (y - MIN_Y_SCREEN) * y_scale;
      glutPostRedisplay();
   }
}

//---------------------------------------
// Motion callback for OpenGL
//---------------------------------------
void motion(int x, int y)
{
   // Calculate scale factors
   float x_scale = (MAX_X_VIEW - MIN_X_VIEW) / 
      (float)(MAX_X_SCREEN - MIN_X_SCREEN);
   float y_scale = (MIN_Y_VIEW - MAX_Y_VIEW) / 
      (float)(MAX_Y_SCREEN - MIN_Y_SCREEN);

   // Handle mouse motion
   X[count] = MIN_X_VIEW + (x - MIN_X_SCREEN) * x_scale;
   Y[count] = MAX_Y_VIEW + (y - MIN_Y_SCREEN) * y_scale;
   glutPostRedisplay();
}

//---------------------------------------
// Draw interpolating curve
//---------------------------------------
void draw_curve(int start, int count)
{
   // Local variables
   float Matrix[4][4] = {
      { 1.0,   0.0,   0.0,  0.0},
      {-5.5,   9.0,  -4.5,  1.0},
      { 9.0, -22.5,  18.0, -4.5},
      {-4.5,  13.5, -13.5,  4.5} };
   float Cx[4] = {0,0,0,0};
   float Cy[4] = {0,0,0,0};

   // Calculate polynomial
   for (int i=0; i<4; i++)
      for (int j=0; j<4; j++)
      {
         Cx[i] += Matrix[i][j] * X[j+start];
         Cy[i] += Matrix[i][j] * Y[j+start];
      }

   // Connect control points
   glBegin(GL_LINE_STRIP);
   float step = 1.0 / count;
   for (float t=0; t<=1; t+=step)
   {
      float x = Cx[0] + Cx[1]*t + Cx[2]*t*t + Cx[3]*t*t*t;
      float y = Cy[0] + Cy[1]*t + Cy[2]*t*t + Cy[3]*t*t*t;
      glVertex2f(x, y);
   }
   glEnd();
}

//---------------------------------------
// Draw Bezier curve
//---------------------------------------
void draw_bezier(int start, int count)
{
   // Local variables
   float Matrix[4][4] = {
      { 1.0,   0.0,   0.0,  0.0},
      {-3.0,   3.0,   0.0,  0.0},
      { 3.0,  -6.0,   3.0,  0.0},
      {-1.0,   3.0,  -3.0,  1.0} };
   float Cx[4] = {0,0,0,0};
   float Cy[4] = {0,0,0,0};

   // Calculate polynomial
   for (int i=0; i<4; i++)
      for (int j=0; j<4; j++)
      {
         Cx[i] += Matrix[i][j] * X[j+start];
         Cy[i] += Matrix[i][j] * Y[j+start];
      }

   // Connect control points
   glBegin(GL_LINE_STRIP);
   float step = 1.0 / count;
   for (float t=0; t<=1; t+=step)
   {
      float x = Cx[0] + t*(Cx[1] + t*(Cx[2] + t*Cx[3]));
      float y = Cy[0] + t*(Cy[1] + t*(Cy[2] + t*Cy[3]));
      glVertex2f(x, y);
   }
   glEnd();
}

//---------------------------------------
// Draw B-spline curve
//---------------------------------------
void draw_spline(int start, int count)
{
   // Local variables
   float Matrix[4][4] = {
      { 1.0,   4.0,   1.0,  0.0},
      {-3.0,   0.0,   3.0,  0.0},
      { 3.0,  -6.0,   3.0,  0.0},
      {-1.0,   3.0,  -3.0,  1.0} };
   float Cx[4] = {0,0,0,0};
   float Cy[4] = {0,0,0,0};

   // Calculate polynomial
   for (int i=0; i<4; i++)
      for (int j=0; j<4; j++)
      {
         Cx[i] += Matrix[i][j] * X[j+start] / 6.0;
         Cy[i] += Matrix[i][j] * Y[j+start] / 6.0;
      }

   // Connect control points
   glBegin(GL_LINE_STRIP);
   float step = 1.0 / count;
   for (float t=0; t<=1; t+=step)
   {
      float x = Cx[0] + t*(Cx[1] + t*(Cx[2] + t*Cx[3]));
      float y = Cy[0] + t*(Cy[1] + t*(Cy[2] + t*Cy[3]));
      glVertex2f(x, y);
   }
   glEnd();
}

//---------------------------------------
// Draw Catmull-Rom curve
//---------------------------------------
void draw_catmullrom(int start, int count)
{
    // Local variables
    float tau = 0.5;// parameter for "tension"; affects how sharply curve bends at interpolated control pts
    float Matrix[4][4] = {
        {0.0,   1.0,   0.0,     0.0},
        {-tau,  0.0,   tau,     0.0},
        {2*tau, tau-3, 3-2*tau, -tau},
        {-tau,  2-tau, tau-2, tau}
    };
    
    float Cx[4] = {0.0, 0.0, 0.0, 0.0};
    float Cy[4] = {0.0, 0.0, 0.0, 0.0};
   
    // Calculate polynomial
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            Cx[i] += Matrix[i][j] * X[j+start];
            Cy[i] += Matrix[i][j] * Y[j+start];
        }
    }
    
    // Connect control points
    glBegin(GL_LINE_STRIP);
    float step = 1.0 / count;
    
    for(float t=0.0; t<=1.0; t+=step)
    {
        float x = Cx[0] + t*(Cx[1] + t*(Cx[2] + t*Cx[3]));
        float y = Cy[0] + t*(Cy[1] + t*(Cy[2] + t*Cy[3]));
        glVertex2f(x, y);
    }
    
    glEnd();
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   // Draw lines
   if (mode >= LINE)
   {
      // Draw control points
      glColor3f(1.0, 1.0, 1.0);
      glPointSize(3);
      glBegin(GL_POINTS);
      for (int i=0; i<=count; i++)
         glVertex2f(X[i], Y[i]);
      glEnd();

      // Connect control points
      glLineWidth(1);
      glBegin(GL_LINE_STRIP);
      for (int i=0; i<=count; i++)
         glVertex2f(X[i], Y[i]);
      glEnd();
   }

   // Draw interpolating curves
   if (mode == CURVE)
   {
      glColor3f(1.0, 0.0, 0.0);
      glLineWidth(2);
      for (int i=0; i<=count-3; i+=3)
         draw_curve(i, 100);
   }

   // Draw Bezier curves
   if (mode == BEZIER)
   {
      glColor3f(1.0, 1.0, 0.0);
      glLineWidth(2);
      for (int i=0; i<=count-3; i+=3)
         draw_bezier(i, 100);
   }

   // Draw B-spline curves
   if (mode == SPLINE)
   {
      glColor3f(0.0, 1.0, 0.0);
      glLineWidth(2);
      for (int i=0; i<=count-3; i++)
         draw_spline(i, 100);
   }
   
   // Draw Catmull-Rom curves
   if (mode == CATMULL_ROM)
   {
       glColor3f(1.0, 0.0, 1.0);
       glLineWidth(2);
       for (int i=0; i<=count-3; i++)
       {
           draw_catmullrom(i, 100);
       }
   }

   glFlush();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitWindowSize(MAX_Y_SCREEN, MAX_X_SCREEN);
   glutInitWindowPosition(MAX_Y_SCREEN/2, MAX_X_SCREEN/2);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
   glutCreateWindow("Curve");
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutMotionFunc(motion);
   init();
   printf("Keyboard commands:\n");
   printf("   'l' - draw lines\n");
   printf("   'i' - draw interpolating curves\n");
   printf("   'b' - draw Bezier curves\n");
   printf("   's' - draw B-spline curves\n");
   printf("   'c' - draw Catmull-Rom curve\n");
   printf("Mouse operations:\n");
   printf("   'mouse down' - start drawing line\n");
   printf("   'mouse motion' - draw rubber-band line\n");
   printf("   'mouse up' - finish drawing line\n");
   glutMainLoop();
   return 0;
}
