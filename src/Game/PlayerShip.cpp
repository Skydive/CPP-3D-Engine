#include "PlayerShip.h"
#include "Engine.h"

#include "Projectile.h"

#include <iostream>
#include <map>
#include <iostream>
#include <glm/gtx/compatibility.hpp> // Lerp

#define MovementMultiplier 100.f
#define MouseMultiplier 1.31f
#define RollMultiplier 2.5f

void TestEntity::BeginPlay()
{
	Entity::BeginPlay();

	//Model = static_cast<RenderComponent*>(AddComponent(new RenderComponent()));
	TestModel = AddComponent<RenderComponent>();
	TestModel->RenderModel = GameEngine->GameResourceManager->GetResource<Model>("ModelPrimitiveUVSphere");
	TestModel->Owner = this;
	TestModel->bParentToOwner = true;
	TestModel->AttachShader(GameEngine->GameShaderManager->GetShader<Shader>("BasicShader"));
	TestModel->RenderTexture = GameEngine->GameResourceManager->GetResource<Texture>("TextureRainbow");
	TestModel->Scale = 100.f*glm::vec3(1.f, 1.f, 1.f);

	auto TCol = AddComponent<CollisionComponent>();
	TCol->bParentToOwner = true;
	TCol->CollisionType = C_Sphere;
	TCol->Radius = 100.f;
}

void PlayerShip::BeginPlay()
{
	Super::BeginPlay();
	std::cout << "Ship Created!";
	GameEngine->GameInput->SetMouseFrozen(true);

	ShipPhysics = AddComponent<PhysicsComponent>();
	ShipPhysics->Mass = 1;
	ShipPhysics->bActive = true;
	ShipPhysics->MaximumSpeed = 30;
	ShipPhysics->VelocityDamping = 1.05;

	ShipSound = AddComponent<SoundSourceComponent>();
	ShipSound->bParentToOwner = true;
	ShipSound->SetSourceSound(GameEngine->GameResourceManager->GetResource<Sound>("SoundLaser"));

	ShipCollision = AddComponent<CollisionComponent>();
	ShipCollision->bParentToOwner = true;
	ShipCollision->CollisionType = C_Sphere;
	ShipCollision->Radius = 0.75;

	ShipModelLeft = AddComponent<RenderComponent>();
	ShipModelLeft->Scale = {1, 0.1, 0.1};
	ShipModelLeft->bParentToOwner = true;
	ShipModelLeft->RenderModel = GameEngine->GameResourceManager->GetResource<Model>("ModelConeShip");
	ShipModelLeft->AttachShader(GameEngine->GameShaderManager->GetShader<Shader>("BasicShader"));
	ShipModelLeft->RenderTexture = GameEngine->GameResourceManager->GetResource<Texture>("TextureBlue");

	ShipModelRight = AddComponent<RenderComponent>();
	ShipModelRight->Scale = {1, 0.1, 0.1};
	ShipModelRight->bParentToOwner = true;
	ShipModelRight->RenderModel = GameEngine->GameResourceManager->GetResource<Model>("ModelConeShip");
	ShipModelRight->AttachShader(GameEngine->GameShaderManager->GetShader<Shader>("BasicShader"));
	ShipModelRight->RenderTexture = GameEngine->GameResourceManager->GetResource<Texture>("TextureBlue");

	WeaponDefaultOffset = -0.2f;
	WeaponFireOffset = WeaponDefaultOffset-0.4f; // Must be below WeaponDefaultOffset

	ShipModelLeft->LocalLocation = {WeaponDefaultOffset, -0.2f, -0.3f};
	ShipModelRight->LocalLocation = {WeaponDefaultOffset, -0.2f, 0.3f};

	FireCooldown = 0.1f;
	bCanFire = true;
}


void PlayerShip::Tick(float dt)
{
	// Skip Super::Tick()
	Entity::Tick(dt);

	HandleMovement(dt);
	HandleFire(dt);
	// Derive movement from Entity rather than Player.
}


void PlayerShip::HandleFire(float dt)
{
	if(GameEngine->GameInput->GetMouse(0) && bCanFire)
	{
		if(VT == nullptr)
		{
			VT = new VolumeTimer(); VT->GetCurrentTicks = GameEngine->GetTime;
			VT->Function = [this](float dt, float waittime)
			{
				bCanFire = true;
				VT->Reset(); VT->Stop();
			};
		}

		ShipSound->Play();

		Projectile* Proj = Spawn<Projectile>();
		Proj->Location = Location + LocalToRelative(bFireRight ? ShipModelRight->LocalLocation : ShipModelLeft->LocalLocation);
		(bFireRight ? ShipModelRight : ShipModelLeft)->LocalLocation.x = WeaponFireOffset; // Offset for animation
		bFireRight = !bFireRight;
		Proj->Rotation = Rotation;
		Proj->Velocity = GetForwardVector()*1.f;
		Proj->LifeSpan = 2.f;
		Proj->GetComponent<CollisionComponent>()->Function = [Proj, this](Entity* collided, CollisionComponent* collidedcomp)
		{
			TestEntity* T = Cast<TestEntity*>(collided);
			if(T != nullptr)
			{
				T->Destroy();
				Proj->Destroy();
			}
		};

		bCanFire = false;
		VT->Start(FireCooldown);
	}

	// Animation!
	ShipModelLeft->LocalLocation.x = glm::clamp(ShipModelLeft->LocalLocation.x+dt*2.f, WeaponFireOffset, WeaponDefaultOffset);
	ShipModelRight->LocalLocation.x = glm::clamp(ShipModelRight->LocalLocation.x+dt*2.f, WeaponFireOffset, WeaponDefaultOffset);
}

void PlayerShip::HandleMovement(float dt)
{
	std::map<int, float> ForwardKeys = {{Key::KEY_W, 1}, {Key::KEY_S, -1}};
	std::map<int, float> RightKeys = {{Key::KEY_D, 1}, {Key::KEY_A, -1}};
	for(auto& kv : ForwardKeys)
	{
		if(GameEngine->GameInput->GetKey(kv.first))
		{
			ShipPhysics->ApplyForce(GetForwardVector() * kv.second * MovementMultiplier, dt);
		}
	}
	for(auto& kv : RightKeys)
	{
		if(GameEngine->GameInput->GetKey(kv.first))
		{
			if(GameEngine->GameInput->GetKey(Key::KEY_LEFT_SHIFT))
			{
				ShipPhysics->ApplyForce(GetRightVector() * kv.second * MovementMultiplier, dt);
			}
			else
			{
				Rotation = glm::angleAxis(RollMultiplier * kv.second * dt, GetForwardVector()) * Rotation;
			}
		}
	}

	Rotation = glm::angleAxis(MouseMultiplier * -GameEngine->GameInput->GetMouseVelocity().y * dt, GetRightVector()) * Rotation;
    Rotation = glm::angleAxis(MouseMultiplier * -GameEngine->GameInput->GetMouseVelocity().x * dt, GetUpVector()) * Rotation;
}
