#include "Engine.h"

#include "RendererOpenGL.h"
#include "Config.h"

#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <AL/alut.h>

#include "Timer.h"
#include "CollisionComponent.h"

Engine::Engine(){}

void Engine::Start()
{
	EngineName = "CPP-3D-Engine";
	// TODO: Make a ParseConfigs() function. Perhaps link this with other stuff? Display.cfg is also accessed in the renderer.
	std::string Resolution = Config("./Display.cfg").GetValueString("WindowedResolution", "1366x786");
	std::stringstream ss(Resolution);
	std::string rx, ry;
	std::getline(ss, rx, 'x');
	std::getline(ss, ry, 'x');

	Dimensions.x = atof(rx.c_str());
	Dimensions.y = atof(ry.c_str());

	CreateInternals();
	Precache();
	BeginPlay();
	MainLoop();
}

void Engine::Precache(){}

void Engine::CreateInternals()
{
	// Hahaha! Side effect of Object possessing a GameEngine variable. (Engine has one too.)
	GameEngine = this;

	GameEntityManager = std::unique_ptr<EntityManager>(new EntityManager());
	GameEntityManager->GameEngine = this;

	GameCollisionManager = std::unique_ptr<CollisionManager>(new CollisionManager());
	GameCollisionManager->GameEngine = this;

	GameShaderManager = std::unique_ptr<ShaderManager>(new ShaderManager());
	GameShaderManager->GameEngine = this;

	GameResourceManager = std::unique_ptr<ResourceManager>(new ResourceManager());
	GameResourceManager->GameEngine = this;

	GameSoundManager = std::unique_ptr<SoundManager>(new SoundManager());
	GameSoundManager->GameEngine = this;
	GameSoundManager->Start();

	GameRenderer = std::unique_ptr<Renderer>(new RendererOpenGL());
	GameRenderer->GameEngine = this;
	GameRenderer->Start();

	GameInput = std::unique_ptr<Input>(new Input());
	GameInput->GameEngine = this;
}

void Engine::BeginPlay(){}

uint32_t Engine::GetTime()
{
	return (uint32_t)(glfwGetTime()*1000);
}

void Engine::MainLoop()
{
	float dt = 0;
	Timer TickTimer = Timer();
	TickTimer.GetCurrentTicks = GetTime;
	TickTimer.Start();

	while(!bQuit)
	{
		GameRenderer->Update();
		GameRenderer->RenderClear();

		GameInput->Update(dt);

		for(auto& ent : GameEntityManager->EntityList)
		{
			ent->Tick(dt);
			for(auto& comp : ent->Components)
			{
				comp->Tick(dt);
				comp->Render();
			}
			GameEntityManager->RefreshComponents(ent.get());
		}
		GameEntityManager->RefreshEntities();

		GameCollisionManager->Update();

		PhysicsComponent::PhysicsTick(this, dt);

		VolumeTimer::TimerTick(dt);

		GameRenderer->RenderPresent();

		dt = TickTimer.GetTickCount()/1000.f; TickTimer.Reset();
	}
	GameRenderer->Clean();
}

void Engine::Destroyed()
{
	std::cout << "Engine Destroying" << std::endl;
}
