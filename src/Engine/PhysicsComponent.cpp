#include "PhysicsComponent.h"
#include "Engine.h"

#include "CollisionComponent.h"

void PhysicsComponent::BeginPlay()
{
	Super::BeginPlay();
    bActive = true;
}

void PhysicsComponent::ApplyForce(glm::vec3 ForceVector, float dt)
{
    //Ft = m(v-u)
    Velocity += ForceVector*dt/Mass;
}

void PhysicsComponent::PhysicsTick(Engine* e, float dt)
{
	for(auto& ent : e->GameEntityManager->EntityList)
	{
		auto p = ent->GetComponent<PhysicsComponent>();
		if(p)
		{
			p->UpdatePhysics(dt);
		}
	}
}

// The location of THIS tick delays the simulation update to the next frame. (Looks nice)
// UpdatePhysics could be moved to the Tick function in the entity to make the location update instantaneous.
void PhysicsComponent::Tick(float dt)
{
	Super::Tick(dt);
}

void PhysicsComponent::UpdatePhysics(float dt)
{
	// Deflection should occur here
	Owner->Location = Owner->Location + Velocity * dt;
    // TODO: Merge these two below.

    // Speed Cap
    if(MaximumSpeed > 0)
    {
        glm::vec3 Direction = glm::normalize(Velocity);
        if(glm::length(Velocity) > MaximumSpeed)
        {
            Velocity = Direction * MaximumSpeed;
        }
    }

    // Damping/Air Resistance
	Velocity /= VelocityDamping;
}
