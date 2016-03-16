#pragma once
#include "Player.h"

#include "Timer.h"

#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"
#include "SoundSourceComponent.h"

class TestEntity : public Entity
{
public:
	virtual void BeginPlay() override;
private:
	RenderComponent* TestModel;
};

class PlayerShip : public Player
{
public:
	virtual void BeginPlay() override;
	virtual void Tick(float dt) override;

	virtual void HandleMovement(float dt);
	virtual void HandleFire(float dt);
private:
	bool bFireRight;
	VolumeTimer* VT;
public:
	bool bCanFire;
	float WeaponDefaultOffset, WeaponFireOffset;
	float FireCooldown;
private:
	RenderComponent* ShipModelLeft;
	RenderComponent* ShipModelRight;
	CollisionComponent* ShipCollision;
	PhysicsComponent* ShipPhysics;
	SoundSourceComponent* ShipSound;
	using Super = Player;
};
