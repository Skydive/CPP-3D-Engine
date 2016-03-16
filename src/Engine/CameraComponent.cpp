#include "CameraComponent.h"
#include "Engine.h"

CameraComponent* CameraComponent::CurrentCamera = nullptr;

void CameraComponent::Tick(float dt)
{
	Super::Tick(dt);
	if(CurrentCamera == this)
	{
		GameEngine->GameRenderer->RenderLocation = Location;
		GameEngine->GameRenderer->RenderRotation = Rotation;
	}
}

void CameraComponent::SetCurrentCamera()
{
	CurrentCamera = this;
}
