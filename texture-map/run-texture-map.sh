#*********************************
# Execute texture mapping program
#*********************************

opengl='-lGL -lGLU -lglut'
gauchlib='libim/libim.a jpeg/libjpeg.a'

g++ -Wall -o textureMap textureMap.cpp cubeTexture.cpp $gauchlib $opengl
./textureMap
echo "Done."

