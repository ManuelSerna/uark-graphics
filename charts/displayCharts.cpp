//********************************
// CSCE 4813 Computer Graphics Projeect 1
// Part 2: Display 
// Manuel Serna-Aguilera
//********************************

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
	
	//FILE *data = fopen("chart.txt", "r");
	
	// TODO: process scale lines
	// TODO: get scale lines color
	// TODO: draw scale lines
	
	// Draw chart itself
	ifstream data;
	data.open("chart.txt");
	
	if(!data)
	{
		cout << "Error: could not read file. Bailing.";
		return;
	}
	
	if(data.is_open())
	{
		while(getline(data, line))
		{
			cout << line << endl;
		}
	}
	
	data.close();
	
	/*
	if(fscanf(data, "%s %f %f %f\n", command, &color[0], &color[1], &color[2]) != 3)
	{
		printf("Error: could not execute fscanf command (color).\n");
	}
	*/
	
	//cout << "command -> " << command << endl;
	
	/*
	FILE *data = fopen("chart.txt", "r");
	
	// First line: color info
	if(fscanf(data, "%f %f %f\n", &color[0], &color[1], &color[2]) != 3)
	{
		printf("Error: could not execute fscanf command (color).\n");
	}
	
	// All subsequent lines: points (x, y) for graph
	for(int i = 0; i < PTS; i++)
	{
		if(fscanf(data, "%f %f\n", &X[i], &Y[i]) != 2)
		{
			printf("Error: could not execute fscanf command (vertices).\n");
		}
	}
	
	fclose(data);
	//*/
	
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

