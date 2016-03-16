#include "CollisionComponent.h"
#include "Engine.h"

void CollisionComponent::BeginPlay()
{
    Super::BeginPlay();
    bSolid = true;
    bParentToOwner = true;
}
