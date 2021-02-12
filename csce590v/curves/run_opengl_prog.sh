#*********************************
# Run C++ Program
#*********************************
prog_name=$1
opengl='-lGL -lGLU -lglut'

g++ -Wall -o program $prog_name $opengl
./program

echo "Done."

