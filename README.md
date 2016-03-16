# CPP-2D-Engine
## Current Version: $ENGINE_VERSION
A work in development, to say the least.

Compile using the GNU Compiler Collection (GCC) or CodeBlocks.

### DLL Dependencies:
- Engine.dll
- FreeImage.dll
- glew32.dll
- libgcc_s_dw2-1.dll
- libstdc++-6.dll
- SDL2.dll


## Commandlines for compilation:
### Windows:
	mingw32-make -f *PATH TO MAKEFILE*
### Linux:
	make -f *PATH TO MAKEFILE*

### TODO (Non-exhaustive list):
- Engine (Major and Significant):
  - Config.h: Line 10: Somehow support writing.
  - Config.h: Line 11: Link this with console manager
  - Config.h: Line 19: Template this somehow
  - Engine.cpp: Line 17: Make a ParseConfigs() function. Perhaps link this with other stuff? Display.cfg is also accessed in the renderer.
  - Object.cpp: Line 3: EVERYTHING
  - RendererOpenGL.cpp: Line 80: OpenGL 3.3 Update
  - RendererOpenGL.cpp: Line 140: Make this a function
- Game (Minor and virtually pointless):


### Changelog
- 2-7-14:
- Prepared for release:
  - Fixed a few warnings/errors
  - Redid the makefile to work in ANY directory.
  - Removed needless Entity.cpp class inside src/ which was there for no particular reason.
- 3-7-14:
  - Created THIS changelog.
  - Fixed filepaths containing '\' by replacing all '\' to '/'
  - Updated SDL from 2.0.1 to 2.0.3
  - Added launch message. Engine.h -> "virtual void LaunchMessage()"
  - Added version control Globals.h --> "Global::ENGINE_VERSION" type std::string
  - Added basic timer class
 - 4-7-14
  - Version -> Alpha 0.02
  - Implemented LinkedLists (TODO: Fix deletion, improve and add better iteration)
  - Changed compilation to C++ 14. (-std=C++1y)
  - Added a pointless linkedlist example to TestEntity.cpp DefaultProperties
- 5-7-14
  - Added SDL_ttf. (Yay more dependencies)
    - libfreetype-6.dll
	- SDL2_ttf.dll
  - Added some minor TODOs.
  - Version -> Alpha 0.03
  - RendererBase.cpp/RendererBase.h:
    - Added: Vector2 LocalToWorldVector(Vector2 in)
    - Added: Vector2 WorldToLocalVector(Vector2 in)
	- Self-explanatory, really.
- 6-7-14
  - Version -> Alpha 0.035
  - Made SetRenderView(int x, int y); set the view at the CENTRE of the screen
  - Added -Vector2 and -Vector2f operators.
  - Found the cause of the jitter. Remember to use .ToInteger() with Vectors. Vector -> FloatVector conversions need to be improved.
- 7-7-14
  - Version -> Alpha 0.04
  - Implemented SDL_mixer (badly?)
  - Fixed font directory finding by making it use a base directory of the executable folder. (Only works in windows) (Bye bye multiple OS support for a while.)
- 8-7-14
  - Version -> Alpha 0.045
  - Fixed vector magnitude functions. (Thanks Coi!)
  - Fixed LinkedList deletion!
- 20-7-14 / 21-7-14
  - Version -> Alpha 0.05
  - Added readme generation (python3) (23:59)
  - Moved SDL_mixer out of RendererBase class. (0:30)
  - Added lots of TODOS (1:05)
- 21-7-14
  - Version -> Alpha 0.055
  - Fixed RenderView function. It is a lot easier to work with now.
  - Gave Sprite class a purpose. (Already supports textures)
  - Origin of sprite texture is the centre. (Is this bad?)
- 24-7-14
  - Implemented an FPS counter.
  - Got sick of 60 fps and disabled VSync. (Everything experienced a spasm. Character was moving too fast, the tick function was in the render function and was called a the same rate!)
  - Fixed a memory leak in SDLRenderer::RenderFont(). Surface and Texture was not being Freed/Destroyed. (First memory leak, found during the spasm as the render rate was so high!)
  - Implemented Tick using Timer class to fix the spasm. (Gameplay is very smooth now).
  - Added float LevelSpeed to Level.cpp
  - Tick function now is Tick(float DeltaTime) (Multiply all movement with DeltaTime)
  - Iterated through the game and made these changes to each Entity respectively.
  - Whoa! 5000 fps when holding left to remove the other entities. This sure is cool! I bet you don't get 5000 fps playing Call of Duty! Hah!
  - Updated Generation to include line numbers in the TODO list.
- 27-7-14
  - Added AnimationSprite class (Work in progress)
  - Fixed a linkedlist bug, where iterate would attempt to call the lambda function when h_node->x is a nullpointer and the linkedlist is empty.
  - Did not commit. (Started updating OpenGL)
- 27-7-14
  - Version -> Alpha 0.065
  - OpenGL renderer dealt with. It is now functional and set to default. (It can be changed with one line of code. See: Engine::Initialize())
