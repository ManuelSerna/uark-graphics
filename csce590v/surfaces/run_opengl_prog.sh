#*********************************
# Run C++ Program
#*********************************
prog_name=$1
opengl='-lGL -lGLU -lglut'

g++ -Wall -o prog $prog_name $opengl
./prog

echo "Done."

