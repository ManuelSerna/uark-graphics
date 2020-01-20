#!/bin/bash

# Attach OpenGL flags for OpenGL projects
g++ -Wall charts.cpp -o charts -lGL -lGLU -lglut
./charts

