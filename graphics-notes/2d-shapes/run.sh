#*********************************
# Run OpenGL program given name of single program.
#*********************************

# Check if file exists
if [ ! -f "$1" ]
then
    echo "No file to compile and run"
    exit 1
fi

# Run program
g++ -Wall $1 -o program -lGL -lGLU -lglut
./program
