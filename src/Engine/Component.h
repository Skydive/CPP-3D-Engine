#pragma once
#include "Object.h"
#include "ITransform.h"
#include "IDestroyable.h"


class Entity;
class Engine;
class Component : public Object,
				  public ITransform,
				  public IDestroyable
{
public:
	virtual void BeginPlay();
	virtual void Tick(float dt);
	virtual void Render();

	Entity* Owner;

	bool bParentToOwner;

	glm::vec3 LocalLocation;
	glm::quat LocalRotation;
};
