//********************************
// CSCE 4813 Computer Graphics Projeect 1
// Part 1: Preprocessing
// Manuel Serna-Aguilera
//********************************

#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
//#include <GL/glut.h>

using namespace std;

// Global constants, all lower bounds are zero in order for scaling to work
#define MIN_X_VIEW 0
#define MAX_X_VIEW 100
#define MIN_Y_VIEW 0
#define MAX_Y_VIEW 100
#define PTS 10

// Global variables
float X[PTS];
float Y[PTS];
float color[3];



//================================
// Return max value from an array A
//================================
float getMax(float A[])
{
	float max = -INFINITY;
	
	for(int i = 0; i < PTS; i++)
	{
		if(max < A[i])
		{
			max = A[i];
		}
	}
	
	return max;
}



//================================
// Transformation functions
/*
	input range:  [a..b] = [min..max]
	output range: [c..d] = [MIN_VIEW..MAX_VIEW]
	out =         (d - c)(input pt - a)/(b - a) + c
*/
// Input: some x or y component of a point, and upper and lower bounds of array
// Return: adjusted x or y so it can fit in window
//================================
float transformX(float x, float minX, float maxX)
{
	float out = ((MAX_X_VIEW) * (x - minX))/(maxX - minX);
	return out;
}

float transformY(float y, float minY, float maxY)
{	
	float out = ((MAX_Y_VIEW) * (y - minY))/(maxY - minY);
	return out;
}



//================================
// Scale x and y coords
//================================
void scale()
{
	float padX = 1.0;// pad with space so data doesn't appear at very edge of window
	float maxX = getMax(X) + padX;
	float minX = 0.0;// graph will always start at zero
	
	float padY = 5.0;
	float maxY = getMax(Y) + padY;
	float minY = 0.0;
	
	for(int i = 0; i < PTS; i++)
	{
		X[i] = transformX(X[i], minX, maxX);
		Y[i] = transformY(Y[i], minY, maxY);
	}
}



//================================
// Write graphs commands to file (given choice of graph type)
//================================
void write(char choice)
{
	ofstream dataOut;
	dataOut.open("chart.txt");
	
	// TODO: write scale line commands in-function and color commands
	
	// Set color for graph next
	dataOut << "set_color " 
			<< color[0] << " " 
			<< color[1] << " " 
			<< color[2] 
			<< endl;
	
	// Store commands according to user choice
	switch(choice)
	{
		case 'd':
		{
			//dataOut << "asdfasdf" << endl;
			float size = 1.0;// change size of dots here
			
			for(int i = 0; i < PTS; i++)
			{
				// Dot write:
				// draw_point #size #x #y
				dataOut << "draw_point " 
						<< size << " " 
						<< X[i] << " " 
						<< Y[i] 
						<< endl;
			}
		}
		break;
		
		case 'l':
		{
			int w = 2;
			
			for(int i = 0; i < PTS-1; i++)
			{
				// Line write:
				// draw_line #w #x1 #y1 #x2 #y2
				float x1 = X[i];
				float y1 = Y[i];
				float x2 = X[i+1];
				float y2 = Y[i+1];
				
				dataOut << "draw_line " 
						<< w << " " 
						<< x1 << " " 
						<< y1 << " " 
						<< x2 << " " 
						<< y2 
						<< endl;
			}
		}	
		break;
		
		case 'c':
		{
			int n = 4;
			float colW = 2.0;
			
			for(int i = 0; i < PTS; i++)
			{
				// Column write:
				// draw_polygon #N #x1 #y1 #x2 #y2 ... #xN #yN 
				// Where N >= 3
				float x1 = X[i];
				float y1 = Y[i];
				float x2 = x1 + colW;
				float y2 = 1.0;// floor
				
				dataOut << "draw_polygon " 
						<< n << " " 
						<< x1 << " " 
						<< y1 << " " 
						<< x2 << " " 
						<< y1 << " " 
						<< x2 << " " 
						<< y2 << " " 
						<< x1 << " " 
						<< y2 << " " 
						<< endl;
			}
		}
		break;
		
		case 'a':
		{
			int n = 4;
			
			for(int i = 0; i < PTS-1; i++)
			{
				// Area write:
				// draw_polygon #N #x1 #y1 #x2 #y2 ... #xN #yN 
				// Where N >= 3
				float x1 = X[i];
				float y1 = Y[i];
				float x2 = X[i+1];
				float y2 = Y[i+1];
				float x3 = X[i+1];
				float y3 = 1.0;
				float x4 = X[i];
				float y4 = 1.0;
				
				dataOut << "draw_polygon " 
						<< n << " " 
						<< x1 << " " 
						<< y1 << " " 
						<< x2 << " " 
						<< y2 << " " 
						<< x3 << " " 
						<< y3 << " " 
						<< x4 << " " 
						<< y4 << " " 
						<< endl;
			}
		}	
		break;
		
		default:
			// do nothing for incorrect input
			break;
	}
	
	dataOut.close();
}



//================================
// Get user input
//================================
void getUserInput(char *choicePtr)
{
	string userInput;// name of .txt file
	string dataInput;// incoming data
	int pos = 0;// position of X and Y
	float r = 0.0;
	float g = 0.0;
	float b = 0.0;
	for(int i = 0; i < 3; i++)
	{
		color[i] = 0.0;
	}
	
	// Prompt user
	cout << "Enter name of input file: ";
	cin >> userInput;
	
	cout << endl;
	cout << "Please select one of the following chart types\n";
	cout << "\t'd' = dot chart\n";
	cout << "\t'c' = column chart\n";
	cout << "\t'l' = line chart\n";
	cout << "\t'a' = area chart\n";
	cout << "Choice: ";
	cin >> *choicePtr;
	
	cout << "\nChoose RGB values (0-255):\n";
	cout << "\nR: ";
	cin >> r;
	cout << "\nG: ";
	cin >> g;
	cout << "\nB: ";
	cin >> b;
	
	// NOTE: For some reason, normalizing rgb vals here changes
	// color[0]'s value. It has thus been moved to the very 
	// end of the function.
	
	ifstream data;
	data.open(userInput);
	
	if(!data)
	{
		cout << "Error: could not read file. Bailing.";
		return;
	}
	
	if(data.is_open())
	{
		while(!data.eof())
		{
			data >> dataInput;
			//X[pos] = stof(dataInput);
			X[pos] = (float)(pos) + 1.0;
			Y[pos] = stof(dataInput);
			//Y[pos] = (float)(pos) + 1.0;
			pos++;
		}
	}
	
	data.close();
	
	// Normalize rgb values
	color[0] = r/255.0;
	color[1] = g/255.0;
	color[2] = b/255.0;
}



//================================
// Main
//================================
int main()
{
	char choice = 'x';

	getUserInput(&choice);
	scale();
	write(choice);

	return 0;
}

