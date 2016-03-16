# CPP-2D-Engine
## Current Version: Alpha 0.045
A work in development, to say the least.

Compile using the GNU Compiler Collection (GCC) or CodeBlocks.

### DLL Dependencies:
- OpenGL and SDL:
  - glew32.dll
  - SDL2.dll
  - SDL2_image.dll
  - SDL2_ttf.dll
  - SDL2_mixer.dll
- For filetypes:
  - libjpeg-9.dll
  - libpng16-16.dll
  - libtiff-5.dll
  - libwebp-4.dll
  - libfreetype-6.dll
  - smpeg2.dll
  - libvorbisfile-3.dll
  - libvorbis-0.dll
  - libogg-o.dll
  - libmodplug-1.dll
  - libFLAC-8.dll
- Weird GCC Dependencies: (Are they even dependencies? Regardless, they SHOULD BE required.)
  - libgcc_s_dw2-1.dll
  - libstdc++-6.dll
- Other:
  - zlib1.dll
  
## Commandlines for compilation:
### Windows:
	mingw32-make -f *PATH TO MAKEFILE*
### Linux:
	make -f *PATH TO MAKEFILE*
	
### TODO (Non-exhaustive list):
- ~~Add launch message + version notify~~ (3-7-2014)
- ~~Use a linked list to house the entities for faster insertion~~ (4-7-2014)
- ~~Make a linked list class for the linked list to house the entities.~~ (4-7-2014)
- ~~Add SDL TTF support~~ (5-7-2014)
- ~~Code Local/World position converters and rename arguments+variables to avoid confusion.~~ (5-7-2014)
- ~~Make coordinate render view setting a lot easier.~~ (6-7-2014)
- ~~Add a negate operator to -Vector2 and -Vector2f.~~ (6-7-2014)
- ~~Fix font directory finding. Should be local with debugger.~~ (7-7-2014)
- ~~Add SDL Mixer support~~ (7-7-2014)
- ~~Fixed LinkedList deletion~~ (8-7-2014)
- Fix the OpenGL renderer to work with images
- Complete the Direct3D renderer.
- Improve collision
- Make more utility functions
- Fix Tick. (Make it an ACTUAL tick rather than being called when render is) {TICK IS A LIE}
- Add FPS counter
- Add GUI support
- Make some sort of API documentation
- 64 bit
- Fix the cause of the render jitter when dealing with coordinate translations to do with int->float vector conversion.
- Add SDL Mixer support
- Add Linux compatibility
- Improve and add better iteration to LinkedLists
- Get rid of inconsistencies between char* and std::string, surely the latter is better.
- Implement pausing
- Move SDL_mixer stuff OUT of RendererSDL.
- Separate precaching of files and to texture conversion. (Add a BETTER resource manager which is linked to the renderer).
- MP3s with SDL Mixer MUST be of a bitrate of 256kbps and 44100Hz sample rate. (Fix this, perhaps?)
- Properly implement Entity:IDCount
- Create a method to generate this, and the readme easily and effectively. (Python for a script perhaps?) 
  -- This job doesn't deserve to be done by a good programming language due to effort.
- BORING: Deal with licensing
By Khalid Aleem
(Open source. Do whatever the heck you want with it!)
(Some licensing restrictions may apply. I don't know what they are. [See bottom of TODO list])



