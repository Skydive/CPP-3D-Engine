#include "CollisionManager.h"
#include "Engine.h"

#include <iostream>

bool CollisionUtil::DetermineCollision(CollisionComponent* c1, CollisionComponent* c2)
{
    if(c1 == c2) return false;
    for(auto& pair : CollisionUtil::CollisionFunctionList)
    {
        if((c1->CollisionType == std::get<0>(std::get<0>(pair)) && c2->CollisionType == std::get<1>(std::get<0>(pair)))
        || (c1->CollisionType == std::get<1>(std::get<0>(pair)) && c2->CollisionType == std::get<0>(std::get<0>(pair))))
        {
            bool bCollided = std::get<1>(pair)(c1, c2);
            if(bCollided && c1->Owner && c2->Owner && c1->bSolid && c2->bSolid)
            {
                DeflectionUtil::ProcessDeflection(std::get<0>(pair), c1, c2);
            }
            return bCollided;
        }
    }
    return false;
}

bool CollisionUtil::SphereToSphere(CollisionComponent* c1, CollisionComponent* c2)
{
    return glm::length(c1->Location - c2->Location) < c1->Radius + c2->Radius;
}

// http://www.ics.uci.edu/~arvo/code/BoxSphereIntersect.c

bool CollisionUtil::SphereToBox(CollisionComponent* c1, CollisionComponent* c2)
{
    return false;
}

bool CollisionUtil::BoxToBox(CollisionComponent* c1, CollisionComponent* c2)
{
    return false;
}

void DeflectionUtil::ProcessDeflection(std::tuple<int, int> types, CollisionComponent* c1, CollisionComponent* c2)
{
    for(auto& pair : DeflectionUtil::DeflectionFunctionList)
    {
        if(std::get<0>(pair) == types)
        {
            std::get<1>(pair)(c1, c2);
            return;
        }
    }
}

void DeflectionUtil::SphereToSphere(CollisionComponent* c1, CollisionComponent* c2)
{
    PhysicsComponent* p1 = c1->Owner->GetComponent<PhysicsComponent>();
    PhysicsComponent* p2 = c2->Owner->GetComponent<PhysicsComponent>();
    if(!p1) // Ensure that p1 is ALWAYS a physics component.
    {
        std::swap(p1, p2);
        std::swap(c1, c2);
    }
    if(p1)
    {
        glm::vec3 Normal = glm::normalize(c1->Owner->Location - c2->Owner->Location);
        float DotVN = glm::dot(p1->Velocity, -Normal);
        if(DotVN > 0)
        {
            p1->Velocity = p1->Velocity + Normal*DotVN;
        }
    }
}

void DeflectionUtil::SphereToBox(CollisionComponent* c1, CollisionComponent* c2)
{
}

void DeflectionUtil::BoxToBox(CollisionComponent* c1, CollisionComponent* c2)
{
}

void CollisionManager::Update()
{
    std::vector<CollisionComponent*> CollisionList;
    for(auto& ent : GameEngine->GameEntityManager->EntityList)
    {
        ent->GetComponents<CollisionComponent>(&CollisionList);
    }

    for(auto cola : CollisionList)
    {
        // Wipe CollisionList
        cola->CollidingComponents.clear();
        for(auto colb : CollisionList)
        {
            if(CollisionUtil::DetermineCollision(cola, colb))
            {
                cola->CollidingComponents.push_back(colb);
                if(cola->Function)
                {
                    // TODO: Two args? Really?
                    cola->Function(colb->Owner, colb);
                }
            }
        }
    }
}

bool CollisionManager::TraceLine(RayTraceInfo* Info, Entity* Invoker, glm::vec3 Start, glm::vec3 End, float Interval)
{
    for(glm::vec3 Point=Start;
    glm::length(Point-Start)<glm::length(End-Start);
    Point+=glm::normalize(End-Start)*Interval)
    {
        for(auto& ent : GameEngine->GameEntityManager->EntityList)
        {
            for(auto& comp : ent->Components)
            {
                CollisionComponent* colcomp = dynamic_cast<CollisionComponent*>(comp.get());
                if(colcomp && colcomp->Owner != Invoker)
                {
                    CollisionComponent PointCC; // Hack
                    PointCC.Location = Point;
                    PointCC.CollisionType = C_Sphere;
                    PointCC.Radius = 0.1;
                    if(CollisionUtil::DetermineCollision(colcomp, &PointCC))
                    {
                        Info->Location = Point;
                        Info->HitComponent = colcomp;
                        Info->HitEntity = colcomp->Owner;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
