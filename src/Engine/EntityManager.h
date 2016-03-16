#pragma once
#include "Object.h"
#include "Entity.h"

#include <list>
#include <memory>

class EntityManager : public Object
{
public:
	Entity* SpawnInternal(Entity* NewEntity);
	Component* AddComponentInternal(Entity* NewEntity, Component* NewComponent);

	template<class T> T* Spawn()
	{
		T* RetEntity = new T();
		Entity* NewEntity = static_cast<Entity*>(RetEntity);
		EntityList.push_back(std::unique_ptr<Entity>(NewEntity));
		NewEntity->GameEngine = GameEngine;
		NewEntity->BeginPlay();
		return RetEntity;
	};

	template<class T> T* AddComponent(Entity* Parent)
	{
		T* RetComponent = new T();
		Component* NewComponent = static_cast<Component*>(RetComponent);
		Parent->Components.push_back(std::unique_ptr<Component>(NewComponent));
		NewComponent->GameEngine = GameEngine;
		NewComponent->Owner = Parent;
		NewComponent->BeginPlay();
		return RetComponent;
	};

	virtual void RefreshComponents(Entity* PendingEntity);
	virtual void RefreshEntities();

	// TODO: Why doesn't std::list work and not cause SegFaults. An equivelant std::vector SegFaults with small lists :(
	std::list<std::unique_ptr<Entity>> EntityList;
};
