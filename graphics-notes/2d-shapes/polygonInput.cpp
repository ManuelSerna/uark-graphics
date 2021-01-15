//********************************
// Draw polygon(s) by reading txt file
/*
    How polygon_data.txt is formatted:

    command1 dataValue1 dataValue2 ... dataValueN1
    command2 dataValue1 dataValue2 ... dataValueN2
    .
    .
    .
    commandN dataValue1 dataValue2 ... dataValueNM

    For every command, there can be any number of data values (for vertices, color values, etc.).
*/
// Author: Manuel Serna-Aguilera
//********************************

#include <bits/stdc++.h>
#include <fstream>
#ifdef MAC
#include <GLUT/glut.h> // MAC naming
#else
#include <GL/glut.h> // Linux naming
#endif
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

//--------------------------------
// Draw Polygon
/*
 * Input: string vector of read line from file
 * Return: NA
*/
//--------------------------------
void drawPolygon(vector <string> &tokens)
{
    glBegin(GL_POLYGON);
    
    // Iterate through vertex (x,y) coord pairs
    for(int v = 1; v < (int)tokens.size(); v += 2)
    {
        //cout << "x: " << tokens[v] << endl;
        //cout << "y: " << tokens[v+1] << endl;
        float x = stof(tokens[v]);
        float y = stof(tokens[v+1]);
        
        glVertex2f(x, y);
    }
    
    glEnd();
}

//--------------------------------
// Read Polygon Information from File
//--------------------------------
void readPolygonInfo()
{
    // Open file
    ifstream data;
    data.open("polygon_data.txt");
    
    if(!data)
    {
        cout << " Error: file could not be read" << endl;
        return;
    }
    
    // Read polygon and color information
    if(data.is_open())
    {
        string line;
        
        while(getline(data, line))
        {
            // Get tokens from line read
            vector <string> tokens;
            stringstream check1(line);
            string intermediate;
            
            // Tokenize line, split along space " "
            while(getline(check1, intermediate, ' '))
            {
                tokens.push_back(intermediate);
            }
            
            // Read commands and then get data
            if(tokens[0] == "set_color")
            {
                glColor3f(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
            }
            else if(tokens[0] == "polygon")
            {
                drawPolygon(tokens);
            }
        }
    }
    
    // Done reading polygon info
    data.close();
}

//--------------------------------
// OpenGL Init callback
//--------------------------------
void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100, 100, -100, 100, -100, 100);
}

//--------------------------------
// OpenGL Display callback
//--------------------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    // Read in polygon information
    readPolygonInfo();
    
    glFlush();
}

//--------------------------------
// Main
//--------------------------------
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);// start with init callback
    glutInitWindowSize(500, 500);// set window size
    glutInitWindowPosition(80, 80);// set window position (upper left corner)
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Polygon Input");
    init();
    glutDisplayFunc(display);// call display callback (i.e. what we want to display)
    glutMainLoop();// enter loop until user closes out of window (no other code follows this line)
}
