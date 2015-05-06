A small program to test object creation in OpenGL by placing certain logic gates around and connecting them. There is no further abilities once connected unfortunately

Included are the following:

main.cpp
DisplayClass.cpp
script

-main.cpp and DisplayClass.cpp are the files for the program
-script is a bash script that will compile, run, and delete the executable upon completion.
-script runs:
		g++ main.cpp DisplayClass.h -framework GLUT -framework OpenGL 
		./a.out
		rm a.out
-invoke the program by bash script via commandline. Takes no arguments.

*To place gates*
-Click on the rectangle in the upper left corner for the corresponding logic gate
-Place as many gates as necessary; click on another gate to change or hit 'esc' to stop gate placement
-'esc' will return to a no input state.

*To place wires*
-Right click and select a color AND a wire type (xy, yx, xyx, yxy). Color is necessary to place a wire.
-Click on any terminal in any order to place the wire.
-If the XYX or YXY options are chosen, upon first click the program will prompt for a floating point value
 between 0.0 and 1.0. Enter the number and press the space bar
 If a number less than 0.0 or greater than 1.0, the program resumes it's default state and will not allow wireplacement
-Place as many of the same time of wire, then press 'esc' or select another wiretype.
-'esc' will return to a no input state.

*Clearing*
-Right click and select Clear. This empties the lists that store the coordinates for the gates and wires

*Exiting*
-Right click and select Exit. This empties the lists and deletes the class object from the heap before closing
