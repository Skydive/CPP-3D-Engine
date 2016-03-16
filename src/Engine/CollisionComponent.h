#pragma once
#include "Component.h"
#include <functional>
#include <vector>

class CollisionComponent : public Component
{

public:
    virtual void BeginPlay() override;

    int CollisionType;
    glm::vec3 Dimensions; // C_Box // with respect to centre
    float Radius; // with respect to centre

    bool bSolid;
    std::function<void(Entity*, CollisionComponent*)> Function;
    std::vector<CollisionComponent*> CollidingComponents;
private:
    using Super = Component;
};
