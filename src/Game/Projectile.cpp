#include "Projectile.h"
#include "Engine.h"

void Projectile::BeginPlay()
{
	Super::BeginPlay();
	CreationTime = GameEngine->GetTime();

	ProjectileModel = AddComponent<RenderComponent>();
	ProjectileModel->Owner = this;
	ProjectileModel->Scale = {0.1, 0.01, 0.01};
	ProjectileModel->bParentToOwner = true;
	ProjectileModel->RenderModel = GameEngine->GameResourceManager->GetResource<Model>("ModelPrimitiveUVSphere");
	ProjectileModel->AttachShader(GameEngine->GameShaderManager->GetShader<Shader>("BasicShader"));
	ProjectileModel->RenderTexture = GameEngine->GameResourceManager->GetResource<Texture>("TextureRed");

	ProjectileCollision = AddComponent<CollisionComponent>();
	ProjectileCollision->bSolid = false;
	ProjectileCollision->bParentToOwner = true;
	ProjectileCollision->CollisionType = C_Sphere;
	ProjectileCollision->Radius = 0.1;
}

void Projectile::Tick(float dt)
{
	Super::Tick(dt);
	if(GameEngine->GetTime() - CreationTime > Timer::FloatToTime(LifeSpan))
	{
		Destroy();
	}
	Location += Velocity;
}
