#include "EntityManager.h"

#include <algorithm>
#include <vector>

Entity* EntityManager::SpawnInternal(Entity* NewEntity)
{
	EntityList.push_back(std::unique_ptr<Entity>(NewEntity));
	NewEntity->GameEngine = GameEngine;
	NewEntity->BeginPlay();
	return NewEntity;
}

Component* EntityManager::AddComponentInternal(Entity* Parent, Component* NewComponent)
{
	Parent->Components.push_back(std::unique_ptr<Component>(NewComponent));
	NewComponent->GameEngine = GameEngine;
	NewComponent->Owner = Parent;
	NewComponent->BeginPlay();
	return NewComponent;
}

void EntityManager::RefreshComponents(Entity* PendingEntity)
{
	PendingEntity->Components.erase(
		std::remove_if(
            PendingEntity->Components.begin(),
            PendingEntity->Components.end(),
            [&] (std::unique_ptr<Component>& comp)
            {
                return comp.get() == nullptr || comp->IsDestroyed();
            }),
        	PendingEntity->Components.end()
    	);
}

void EntityManager::RefreshEntities()
{
	EntityList.erase(
		std::remove_if(
            EntityList.begin(),
            EntityList.end(),
            [&] (std::unique_ptr<Entity>& ent)
            {
                return ent.get() == nullptr || ent->IsDestroyed();
            }),
        	EntityList.end()
    	);
}
