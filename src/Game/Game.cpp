#include "Game.h"
#include "PlayerShip.h"

#include <iostream>

#include "Model.h"
#include "Texture.h"
#include "Sound.h"
#include "ShaderSkybox.h"
#include "CubeMapTexture.h"

void Game::Precache()
{
	Super::Precache();

	GameResourceManager->PrecacheResource(new Model("ModelPrimitiveCube", "./res/Primitives/Cube.obj"));
	GameResourceManager->PrecacheResource(new Model("ModelPrimitiveUVSphere", "./res/Primitives/UVSphere.obj"));
	GameResourceManager->PrecacheResource(new Model("ModelConeShip", "./res/ConeShip.obj"));
	GameResourceManager->PrecacheResource(new Texture("TextureBlue", "./res/Blue.png"));
	GameResourceManager->PrecacheResource(new Texture("TextureRed", "./res/Red.png"));
	GameResourceManager->PrecacheResource(new Texture("TextureRainbow", "./res/Rainbow.png"));
	GameResourceManager->PrecacheResource(new Sound("SoundLaser", "./res/LASER.wav"));

	GameResourceManager->PrecacheResource(new CubeMapTexture("CubeMapSpace", "./res/drakeq"));


	// Generate Shaders:
	Shader* BasicShader = new Shader();
	GameShaderManager->PrecacheShader("BasicShader", BasicShader);

}

void Game::BeginPlay()
{
	Super::BeginPlay();

	PlayerShip* Pawn = GameEntityManager->Spawn<PlayerShip>();
	Pawn->Location = {0, 0, 0};

	TestEntity* T = GameEntityManager->Spawn<TestEntity>();
	T->Location = {190, 0, 0};

}
