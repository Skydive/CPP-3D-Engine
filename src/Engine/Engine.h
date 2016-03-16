#pragma once
#include "Object.h"

#include "EntityManager.h"
#include "CollisionManager.h"
#include "ShaderManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Renderer.h"
#include "Input.h"

#include <stdint.h>
#include <string>
#include <memory>

class Engine : public Object
{
public:
	Engine();

	// Info
	std::string EngineName;
	std::string GameName;
	glm::vec2 Dimensions;

	// Events
	virtual void Start();
	virtual void Precache();
	virtual void BeginPlay();
	virtual void MainLoop();
	virtual void Destroyed();

	static uint32_t GetTime();

	// Start
	virtual void CreateInternals();

	bool bQuit;
	std::unique_ptr<EntityManager> GameEntityManager;
	std::unique_ptr<CollisionManager> GameCollisionManager;
	std::unique_ptr<ResourceManager> GameResourceManager;
	std::unique_ptr<ShaderManager> GameShaderManager;
	std::unique_ptr<SoundManager> GameSoundManager;
	std::unique_ptr<Renderer> GameRenderer;
	std::unique_ptr<Input> GameInput;
};
