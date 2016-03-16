#pragma once
#include "Entity.h"
#include "CameraComponent.h"
#include "SoundListenerComponent.h"

class Player : public Entity
{
public:
	virtual void BeginPlay() override;
	virtual void Tick(float dt) override;
protected:
	CameraComponent* Camera;
	SoundListenerComponent* Listener;
private:
	using Super = Entity;
};
