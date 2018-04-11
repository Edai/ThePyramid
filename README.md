FUNDAMENTALS OF COMPUTER GRAPHICS -  PROJECT 2 REPORT

Author: Valentin KAO <valentin.kao@epitech.eu>
		张有请 - 2017280242
		
The purpose of this project is to implement an OpenGl program using display
list to draw a pyramid :
- The top layer has one cylinder or cone, the number in each layer is 
ascend downward.
- Texture on each cone/each cylinder
- Use different colors to draw each layer
- Click right mouse button to display a menu to add a new layer
- Drag the mouse to rotate the whole pyramid

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

	./ThePyramid [--width=x] [--height=y] [--title=”Assignment”]
	
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

Application class is in charge of parsing the arguments and to init the
graphical core of the program with the input window size or the input
window name. 

GraphicalCore initializes OpenGL engine : window creation, keyboard handler,
mouse handler, reshape handler, etc.

Engine is the core of the project : it will init the lights, the display
lists, textures. The main Update function is in this class.

---------------------------------------------------------------------------
ALGORITHM IMPLEMENTED
---------------------------------------------------------------------------

First, basic initializations are made, such as Textures and Lights. but then
we will init the display lists in InitDisplayList() :

- We will generate NB_LIST lists.
- The list of index 0 has one objective : display a tower composed of a 
  textured cone and a textured cylinder on position (0, 0).
- The other lists will correspond to a line : the 1st list will display 1 
  tower, the 2nd will display 2 towers, etc, until (NB_LIST - 1)th list. Each
  list calls the list of index 0 to display a number of towers as much as its
  index.

All colors of each layer are stored in an array of Gfloats as an attribute of
Engine class, generated randomly. 

The update function calls the lists from 1 to nb_lines (the number of
layers the user wants to display) : glCallList((*indexes)[i + 1]);

---------------------------------------------------------------------------
FUNCTIONNALITIES
---------------------------------------------------------------------------
By pressing the key ESC, you close the program properly.
By pressing SPACE key, the colors of each layer will change.
Adding or removing layers can be made by pressing the arrows or down.

If you right-click with your mouse, a menu will be displayed and you will
be able to change the colors of each layer and to add/remove a layer.

Last functionality is by dragging your mouse, the whole pyramid will rotate.