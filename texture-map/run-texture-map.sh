#*********************************
# Execute texture mapping program
#*********************************

opengl='-lGL -lGLU -lglut'
gauchlib='libim/libim.a jpeg/libjpeg.a' # Reference 

g++ -Wall -o textureMap textureMap.cpp $gauchlib $opengl
./textureMap
echo "Done."

