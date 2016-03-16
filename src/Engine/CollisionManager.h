#pragma once
#include "Object.h"

#include <functional>
#include <tuple>
#include <vector>

#include "CollisionComponent.h"
#include "PhysicsComponent.h"

enum ECollisionType
{
    C_Sphere,
    C_Box,
    C_Max
};

struct RayTraceInfo
{
    glm::vec3 Location;
    Entity* HitEntity;
    CollisionComponent* HitComponent;
};

namespace CollisionUtil
{
    using CollisionFunction = std::function<bool(CollisionComponent*, CollisionComponent*)>;
    using CollisionTuple = std::tuple<std::tuple<int, int>, CollisionFunction>;
    using CollisionList = std::vector<CollisionTuple>;

    bool DetermineCollision(CollisionComponent* c1, CollisionComponent* c2);

    bool SphereToSphere(CollisionComponent* c1, CollisionComponent* c2);
    bool SphereToBox(CollisionComponent* c1, CollisionComponent* c2);
    bool BoxToBox(CollisionComponent* c1, CollisionComponent* c2);

    const CollisionList CollisionFunctionList =
    {
        std::make_tuple(std::make_tuple(C_Sphere, C_Sphere) , &SphereToSphere),
        std::make_tuple(std::make_tuple(C_Sphere, C_Box) , &SphereToBox),
        std::make_tuple(std::make_tuple(C_Box, C_Box) , &BoxToBox)
    };
};

namespace DeflectionUtil
{
    using DeflectionFunction = std::function<void(CollisionComponent*, CollisionComponent*)>;
    using DeflectionTuple = std::tuple<std::tuple<int, int>, DeflectionFunction>;
    using DeflectionList = std::vector<DeflectionTuple>;

    void ProcessDeflection(std::tuple<int, int> types, CollisionComponent* c1, CollisionComponent* c2);

    void SphereToSphere(CollisionComponent* c1, CollisionComponent* c2);
    void SphereToBox(CollisionComponent* c1, CollisionComponent* c2);
    void BoxToBox(CollisionComponent* c1, CollisionComponent* c2);

    const DeflectionList DeflectionFunctionList =
    {
        std::make_tuple(std::make_tuple(C_Sphere, C_Sphere) , &SphereToSphere),
        std::make_tuple(std::make_tuple(C_Sphere, C_Box) , &SphereToBox),
        std::make_tuple(std::make_tuple(C_Box, C_Box) , &BoxToBox)
    };
};



class CollisionManager : public Object
{
public:
    void Update();
    bool TraceLine(RayTraceInfo* Info, Entity* Invoker, glm::vec3 Start, glm::vec3 End, float Interval);
};
