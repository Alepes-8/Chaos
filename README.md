# The Chaos Engine
 
This simple Game Engine was created as a school project at Luleå University of Technology in Sweden. It is made as a project for the course "D7049E, Virtual interactive environments".
In the end the Game Engine is the goal, however to ease up and specialize the game engine it will be made to create a battle simulator. Here with focus of multiple entities going against multiple other entities with complex prioritization trees. <br>

# Installation
 
### Prerequisite

Chaos was made to run on Windows and does not provide any version that can be run on Linux or MacOS

## Starting up

Start of by cloning the git repository onto your computer. Then go into the chaos folder and open
a terminal there. Here we want to download the libraries used in the project. So to download the
sub modules with ease in the right place use the following command "git submodule update –init –
recursive" within the main directory. Then clone SDL2, jsoncpp, bx, bgfx and bimg into the same
folder,"GameEngine/library". When SDL mixer has been downloaded, place its header and lib files in
the corresponding directories inside SDL2. References to the repositories can be seen in the section 5.2.3.
You will need to run the Jsoncpp. Here you should run the cmake file within the folder or follow this
https://github.com/open-source-parsers/jsoncpp/wiki/Building to build the jsoncpp library.

To build RecastNavigation run Cmake and place the output in the same recast folder, use the SDL
library already downloaded from git submodules. Open up the project in visual studio and change the
runtime library field for each library project to MTd in properties->C/C++->Code Generation . Now
you can build the libraries.

However, due to how bgfx is built up we will need to fix some things within the folder. So open bgfx,
then open a command prompt within the main directory of bgfx. Here run "../bx/tools/bin/windows/genie
–with-examples –with-tools vs2017".

You should now have a "./Build" folder, if not it may be hidden so put on the possibilities to see
hidden files/folders in the view settings. Then you wanna go to ".build/projects/vs2017/bgfx".sln and
start it up. When starting it for the first time you may get asked to update the project, do it. Then when
it is update build the project. If you wanna make sure it works as intended run example 14 by setting it
as the "startup project" you can also try to run shaderc if you want to compile new shaders later on (see
section Compile shaders below). If it works you should have prepared the bgfx library correctly.(for the
instructions from bgfx them self follow this (https://bkaradzic.github.io/bgfx/build.html))

When the download has been done it is time to run "GenerateProject.bat" in the main directory. This
will make the necessary connections and links within the solution.
Then Start up the project with the sln file and you should be good to go
 
## Used projects
https://github.com/gabime/spdlog.git

https://www.libsdl.org/download-2.0.php (development library, SDL2-Devel-2 0.20-VC.zip)

https://www.libsdl.org/projects/SDL_mixer/ (Development library, SDL2_mixer-devel-2.0.4-VC.zip)

https://github.com/bkaradzic/bx.git

https://github.com/bkaradzic/bimg.git

https://github.com/bkaradzic/bgfx.git

https://github.com/open-source-parsers/jsoncpp

https://github.com/recastnavigation/recastnavigation


## Compile shaders

This section explain how to create new shaders and to compile them using bfx library. If you only want to use default shaders you can skip this section.

The existing shaders are located in "/Game/Data/Shaders". The fragment shader and vertex shader use in Choas to render basic 3D model are shader from the bgfx repository shader folder (https://github.com/bkaradzic/bgfx/tree/master/examples/runtime/shaders). If you want to create your own shader you can find some example of .sc shader source files in this website https://blog.actorsfit.com/a?ID=00001-ecd59bca-4e4f-4861-a8ab-4ba3e246fa8f. Then you have to use the tool shaderc to compile the shader source files into binary shaders files that can be read by bgfx. Shaderc tool is located in "GameEngine/library/bgfx/.build/win64_vs2017/bin/shadercDebug.exe" and you can compile shaders as followed :
shadercDebug.exe -f intputShader.sc -o output.bin --platform windows --type shaderType 
--varyingdef varying.def.sc

To find more information about shaderc please read the corresponding documentation (https://bkaradzic.github.io/bgfx/tools.html#shader-compiler-shaderc)

## Usage

Refer to the GameEngine report in the main directory in section 5.3.

## Credits
 
### Programers
 
Alex Peschel: @github/Alepes-8
 
Oliver Olofsson: @github/oliolo
 
Josef Vilestad: @github/klingelschmidt
 
Raphaël Dupont: @github/Quittqick
 
### Other Sources
 
I will give credit to youtubers such as: [ The Cherno ](https://www.youtube.com/channel/UCQ-W1KE9EYfdxhL6S4twUNw) and his GameEngine [Hazel](https://github.com/TheCherno/Hazel). As well as [Ather Omar](https://www.youtube.com/channel/UCCKlrE0p4IZxqBpq98KFBmw).
