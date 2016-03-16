#include "Player.h"
#include "Engine.h"

#include <map>

#define MovementMultiplier 5.f
#define MouseMultiplier 1.31f

#include <iostream>

#include "Timer.h"

void Player::BeginPlay()
{
	Super::BeginPlay();

	Camera = AddComponent<CameraComponent>();
	Camera->SetCurrentCamera();
	Camera->bParentToOwner = true;

	Listener = AddComponent<SoundListenerComponent>();
	Listener->SetCurrentListener();
	Listener->bParentToOwner = true;

	std::cout << "Player Spawned!" << std::endl;

	VolumeTimer* VT = new VolumeTimer();
	VT->GetCurrentTicks = GameEngine->GetTime;
	//VT->Start(1);
	VT->Function = [VT](float dt, float waittime)
	{
		std::cout << "Timer completed!" << std::endl;

		glm::quat Q = glm::angleAxis(glm::radians(60.f), glm::vec3(0, 1, 0));
		glm::quat Qv = glm::quat(); Qv.w = 0; Qv.x = 2; Qv.y = 1; Qv.z = 3;
		Qv = glm::conjugate(Q)*Qv*Q;
		printf("{%f, %f, %f, %f}\n", Qv.w, Qv.x, Qv.y, Qv.z);

		VT->Destroy();
		//parent->Reset();
	};
}

void Player::Tick(float dt)
{
	Super::Tick(dt);
	std::map<int, float> ForwardKeys = {{Key::KEY_W, 1}, {Key::KEY_S, -1}};
	std::map<int, float> RightKeys = {{Key::KEY_D, 1}, {Key::KEY_A, -1}};
	std::map<int, float> UpKeys = {{Key::KEY_SPACE, 1}, {Key::KEY_C, -1}};
	for(auto& kv : ForwardKeys)
	{
		if(GameEngine->GameInput->GetKey(kv.first))
		{
			Location += GetForwardVector() * kv.second * MovementMultiplier * dt;
		}
	}
	for(auto& kv : RightKeys)
	{
		if(GameEngine->GameInput->GetKey(kv.first))
		{
			Location += GetRightVector() * kv.second * MovementMultiplier * dt;
		}
	}
	for(auto& kv : UpKeys)
	{
		if(GameEngine->GameInput->GetKey(kv.first))
		{
			Location += glm::vec3(0, 1, 0) * kv.second * MovementMultiplier * dt;
		}
	}

	Rotation = glm::angleAxis(MouseMultiplier * -GameEngine->GameInput->GetMouseVelocity().y * dt, GetRightVector()) * Rotation;
    Rotation = glm::angleAxis(MouseMultiplier * -GameEngine->GameInput->GetMouseVelocity().x * dt, glm::vec3(0, 1, 0)) * Rotation;
}
