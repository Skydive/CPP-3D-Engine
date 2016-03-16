#include "Component.h"

#include "Engine.h"

void Component::BeginPlay(){}

void Component::Tick(float dt)
{
	if(bParentToOwner && Owner)
	{
		Rotation = LocalRotation * Owner->Rotation;
		Location = Owner->Location + LocalToRelative(LocalLocation);
	}
}

void Component::Render(){}
