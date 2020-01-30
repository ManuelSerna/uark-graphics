//********************************
// CSCE 4813 Computer Graphics Projeect 1
// Part 2: Display 
// Manuel Serna-Aguilera
//********************************

#include <bits/stdc++.h> // tokenizing strings
#include <fstream>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

// Global constants, all lower bounds are zero in order for scaling to work
#define MIN_X_VIEW 0
#define MAX_X_VIEW 100
#define MIN_Y_VIEW 0
#define MAX_Y_VIEW 100
#define MIN_Z_VIEW 0
#define MAX_Z_VIEW 1

#define PTS 10

// Global variables
float X[PTS];
float Y[PTS];
float color[3];



//================================
// Draw point (small square)
//================================
void drawPoint(float dotSize, float x, float y)
{
	float red = color[0];
	float green = color[1];
	float blue = color[2];
	
	glColor3f(red, green, blue);
	
	for(int i = 0; i < PTS; i++)
	{
		glBegin(GL_POLYGON);
		
		float x1 = x;
		float y1 = y;
		float x2 = x1 + dotSize;
		float y2 = y1 + dotSize;
		
		glVertex2f(x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glVertex2f(x1, y2);
		
		glEnd();
	}
	
	glFlush();
}



//================================
// Draw line
//================================
void drawLine(int w, float x1, float y1, float x2, float y2)
{
	float red = color[0];
	float green = color[1];
	float blue = color[2];
	
	glColor3f(red, green, blue);

	glLineWidth(w);
	glBegin(GL_LINE_STRIP);
	
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	
	glEnd();
}



//================================
// Draw polygon--for either bar or area chart
//================================
void drawPolygon(int n, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	float red = color[0];
	float green = color[1];
	float blue = color[2];
	
	glColor3f(red, green, blue);
	
	// Draw area
	for(int i = 0; i < PTS; i++)
	{
		glBegin(GL_POLYGON);
		
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);
		glVertex2f(x4, y4);
		
		glEnd();
	}
}



//================================
// Init callback
//================================
void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(MIN_X_VIEW, MAX_X_VIEW, 
			MIN_Y_VIEW, MAX_Y_VIEW, 
			MIN_Z_VIEW, MAX_Z_VIEW);
	glEnable(GL_DEPTH_TEST);
	
	// Clear global arrays
	for(int i = 0; i < PTS; i++)
	{
		X[i] = 0.0;
		Y[i] = 0.0;
	}
}



//================================
// Display callback
// - Process chart file and according to which command it encounters, it will draw a certain object
//================================
void display()
{
	string line;

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	// Draw chart itself
	ifstream data;
	data.open("chart.txt");
	
	// TODO: process scale lines
	// TODO: get scale lines color
	// TODO: draw scale lines
	
	if(!data)
	{
		cout << "Error: could not read file. Bailing.";
		return;
	}
	
	// Read each line, then place tokens in a vector and process commands and extract values
	if(data.is_open())
	{
		while(getline(data, line))
		{			
			// Extract tokens from each line
			vector <string> tokens;
			stringstream check1(line);// stringstream obj
		    string intermediate;
      
			// Tokenize line, split along space " "
			while(getline(check1, intermediate, ' '))
			{
				tokens.push_back(intermediate);
			}
			
			string token = tokens[0];// size = tokens.size()
			if(token == "set_color")
			{
				color[0] = stof(tokens[1]);// r
				color[1] = stof(tokens[2]);// g
				color[2] = stof(tokens[3]);// b
			}
			else if(token == "draw_point")
			{
				// Pass: dot size, x, y.
				drawPoint(
					stof(tokens[1]), 
					stof(tokens[2]), 
					stof(tokens[3])
				);
			}
			else if(token == "draw_line")
			{
				// Pass: line width, x1, y1, x2, y2.
				drawLine(
					stoi(tokens[1]), 
					stof(tokens[2]), 
					stof(tokens[3]),
					stof(tokens[4]),
					stof(tokens[5])
				);
				
			}
			else if(token == "draw_polygon")
			{
				// Pass: n (#points), x1, y1, x2, y1, x2, y2, x1, y2
				drawPolygon(
					stoi(tokens[1]),			 
					stof(tokens[2]),
					stof(tokens[3]),
					stof(tokens[4]),
					stof(tokens[5]),
					stof(tokens[6]),
					stof(tokens[7]),
					stof(tokens[8]),
					stof(tokens[9])
				);
			}
		}
	}
	
	data.close();
	glFlush();
}



//================================
// Main
//================================
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(80, 80);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Graphics Project 1: Manuel Serna-Aguilera");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}

