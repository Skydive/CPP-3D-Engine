#pragma once
#include "Component.h"

class CameraComponent : public Component
{
public:
	virtual void Tick(float dt) override;
	virtual void SetCurrentCamera();

	static CameraComponent* CurrentCamera;
private:
	using Super = Component;
};
