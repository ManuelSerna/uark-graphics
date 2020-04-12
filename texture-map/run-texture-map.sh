#!/bin/bash
opengl='-lGL -lGLU -lglut'
gauchlib='libim/libim.a jpeg/libjpeg.a' # Reference 

# Use Dr. Gauch's jpeg and libim libraries to read an image
#g++ -std=c++11 -Wall -Wno-deprecated-declarations -O3 -o image image.cpp $opengl $gauchlib
#./image

g++ -Wall -o textureMap textureMap.cpp $opengl 
./textureMap
echo "Done."

