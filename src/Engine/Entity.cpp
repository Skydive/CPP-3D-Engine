#include "Entity.h"

#include "Engine.h"

void Entity::BeginPlay(){}

void Entity::Tick(float dt){}

void Entity::Destroy()
{
	for(auto& comp : Components)
	{
		comp->Destroy();
	}
	IDestroyable::Destroy();
}

bool Entity::TraceLine(RayTraceInfo* Info, glm::vec3 Start, glm::vec3 End, float Interval)
{
	return GameEngine->GameCollisionManager->TraceLine(Info, this, Start, End, Interval);
}

Entity* Entity::SpawnInternal(Entity* NewEntity)
{
	return GameEngine->GameEntityManager->SpawnInternal(NewEntity);
}

Component* Entity::AddComponentInternal(Component* NewComponent)
{
	return GameEngine->GameEntityManager->AddComponentInternal(this, NewComponent);
}
