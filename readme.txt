//---------------------------------------------------------------------------
NEO by Magnus Grander
Version:     1.0
Dated:       2 May 2023

Purpose.
--------
A utility to load Atari-ST Neochrome (.NEO) format
low-resolution 16-colour images, display and save as
Windows Bitmap image files (.BMP).

Also to load Windows Bitmap (.BMP) image files
and save as Neochrome (.NEO) format files. The image
should have been prepared as a 320x200 pixel image
with approximately 16 colours. This software does
not apply any scaling, re-colouring, shading or
dithering to the image during conversion.
Based on Jason "Joefish" Railton Neoload

-------------------------------------------------

installing SDL2 on Linux
Depending on your package management tool, run the following to install SDL2 on Linux:
apt package mananger:

$ sudo apt-get install libsdl2-dev

Simple compile:
g++ neo.cpp -o neo -lSDL2

On windows

1. Acquiring the Libraries
The libraries can be downloaded from the official GitHub release pages, here:
SDL: https://github.com/libsdl-org/SDL/releases

2.Installing the Libraries
extract it to a location on our hard drive. 
It can be helpful to add them to our project directory so that everything our project needs is in one place.
However, for the sake of this demo, I have extracted them to c:\sdl:

The folder includes 3 things we are interested in:
Header files (.h) within an include directory
Object Library files (.lib) within the lib directory
Dynamic Library files (.dll) within the lib directory

The lib directory includes both 32-bit (x86) and 64-bit (x64) versions of the libraries.
In this guide we’ll only be setting up the x64 version but,
if your project needs 32-bit as well, the steps can be repeated for that configuration.

3.Project Setup: Visual Studio

Let’s walk through how we’d add these libraries to our Visual Studio project. We can add the libraries to an existing project, or create a new project if needed.

Once we have our project open, we need to open the project properties window, available from the top menu under Project > Properties

Here, we need to do three things:

Add the SDL include directories
Under Configuration Properties > VC++ Directories, ensure we’re configuring the x64 version of our project
by looking at the Platform dropdown at the top. Then, open the Include Directories list, and click Edit:
Here, we need to add the include directory from the zip we extracted earlier:

Add the SDL library directories
Under Configuration Properties > VC++ Directories, open the Library Directories list, and click Edit
Here, we need to add the library directory from each of the three zips we extracted earlier. 
Because we’re configuring the 64-bit version of our project (x64) we use the x64 directories:

Add the SDL libraries as dependencies
Under Configuration Properties > Linker > Input, open the Additional Dependencies list, and click Edit:
Here, we need to add a list of .lib files:

SDL2.lib
SDL2main.lib
SDL2_ttf.lib
SDL2_image.lib

(SDL2_TTF, SDL2_image is not needed for this project)
These are file names that should exist within the lib directories we added to our project in step 2

Compiling the Project

If everything is installed correctly, the following simple program should now compile successfully.
Note, the program may not yet run successfully, but at this point, we want to ensure it compiles:












