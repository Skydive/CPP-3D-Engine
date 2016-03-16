#pragma once
#include "Entity.h"
#include "Timer.h"

#include "RenderComponent.h"
#include "CollisionComponent.h"

class Projectile : public Entity
{
public:
	virtual void BeginPlay() override;
	virtual void Tick(float dt) override;
	float LifeSpan;
	glm::vec3 Velocity;
private:
	using Super = Entity;
	RenderComponent* ProjectileModel;
	CollisionComponent* ProjectileCollision;
	Time CreationTime;
};
