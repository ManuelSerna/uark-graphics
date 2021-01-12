#!/bin/bash

# Attach OpenGL flags for OpenGL projects
#g++ -Wall charts.cpp -o charts -lGL -lGLU -lglut
#./charts

# Read text file and output chart file
echo "Reading data."
g++ -Wall readCharts.cpp -o readCharts -lGL -lGLU -lglut
./readCharts
echo "Done."

# Display charts
echo "Display chart."
g++ -Wall displayCharts.cpp -o display -lGL -lGLU -lglut
./display
echo "Done."

