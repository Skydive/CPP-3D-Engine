#include "Game.h"
#include "Model.h"

#include <iostream>

#include <stdlib.h>

void EntryPoint()
{
	//Model ModelCube = Model("./res/Cube.obj");
	Game E = Game();
	E.GameName = "Game";
	E.Start();
}

#undef main
int main(int argc, char** argv)
{
	EntryPoint();
	system("PAUSE");
	return 0;
}
