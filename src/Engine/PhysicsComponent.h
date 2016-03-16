#pragma once
#include "Component.h"

class Engine;

class PhysicsComponent : public Component
{
public:
    virtual void BeginPlay() override;
	virtual void Tick(float dt) override;
    virtual void UpdatePhysics(float dt);

    virtual void ApplyForce(glm::vec3 ForceVector, float dt);

    static void PhysicsTick(Engine* e, float dt);

    bool bActive;

    float Mass;
    glm::vec3 Velocity;
    float VelocityDamping;
    float MaximumSpeed;
private:
	using Super = Component;
};
