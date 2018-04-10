FUNDAMENTALS OF COMPUTER GRAPHICS -  PROJECT 2 REPORT

Author: Valentin KAO <valentin.kao@epitech.eu>
		张有请 - 2017280242
		
The purpose of this project is to implement an OpenGl program in which
multiple stars rotate around a center point and extend to the outer ring.
The stars must be of different colors.

---------------------------------------------------------------------------
VIDEO CAPTURE
---------------------------------------------------------------------------

The video capture of my program named screenrecord.mp4, is available from
the root of the folder.

---------------------------------------------------------------------------
REQUIREMENTS
---------------------------------------------------------------------------
•	GCC 5 or later
•	CMake 3.9 or later
•	OpenGL, GLUT and SOIL libraries.
The code hasn't been tested on Windows but should work on Visual Studio
2015 and later.

---------------------------------------------------------------------------
BUILD AND USAGE
---------------------------------------------------------------------------
From the folder in which you found this report, please enter the following
command lines.
1.		mkdir build && cd build
2.		cmake ..
3.		make

Once the compilated was successful, you can execute the program. 
Here is the usage of the program.

	./ThePyramid [--width=x] [--height=y] [--title=”Assignment 2”]
	
---------------------------------------------------------------------------
FLAGS – OPTIONS	DESCRIPTION	DEFAULT
---------------------------------------------------------------------------
width, w	Set the width of the window	900
height, h	Set the height of the window	900
title, t	Set the title of the window	“Assignment 2”


---------------------------------------------------------------------------
SOFTWARE DESIGN
---------------------------------------------------------------------------
In order to implement future project easily, I define a simple application
design. Those three classes are singletons avoiding any multiple instances.

---------------------------------------------------------------------------
ALGORITHM IMPLEMENTED
---------------------------------------------------------------------------
Using the formula to generate an Archimedean Spiral, first, we will store 
all possible positions into a vector of glm::vec2 in the function 
Engine::InitStars. Indeed, we compute only once the positions.

The class Star contains a color generated randomly and represented by a 
glm::vec3; and the current index in the pre-computed positions vector 
represented by an integer. 50 stars are created and store in a vector of 
Star. The main update loop of Engine::Update progressively generate the
stars one by one until 50, and then, it loops on the vector of Star, displays
the current star and increment its index position. If the index is superior
to the total number of pre-computed positions, it resets the index to zero:
the star goes back to the middle of the window.
This method provides the impression of infinite loop and expansion of the spiral.

---------------------------------------------------------------------------
FUNCTIONNALITIES
---------------------------------------------------------------------------
By pressing the key ESC or the key Q, you close the program properly.
