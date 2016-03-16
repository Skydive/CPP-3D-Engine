#pragma once
#include "Object.h"
#include "ITransform.h"
#include "IDestroyable.h"

#include <vector>
#include <memory>

#include "Component.h"
#include "CollisionManager.h"

class Entity : public Object,
			   public ITransform,
			   public IDestroyable
{
public:
	virtual void BeginPlay();
	virtual void Tick(float dt);
	virtual void Destroy() override;

	std::vector<std::unique_ptr<Component>> Components;

	Entity* Owner;

	// Easier spawning and component creation. No need to typecast.
	template<class T> T* Spawn()
	{
		return static_cast<T*>(SpawnInternal(static_cast<Entity*>(new T())));
	};
	template<class T> T* AddComponent()
	{
		return static_cast<T*>(AddComponentInternal(static_cast<Component*>(new T())));
	};
	template<class T> T* GetComponent()
	{
		for(auto& comp : Components)
		{
			T* CastedComp = dynamic_cast<T*>(comp.get());
			if(CastedComp)
			{
				return CastedComp;
			}
		}
		return nullptr;
	}
	template<class T> bool GetComponents(std::vector<T*>* RetComponents)
	{
		bool bFound;
		for(auto& comp : Components)
		{
			T* CastedComp = dynamic_cast<T*>(comp.get());
			if(CastedComp)
			{
				if(RetComponents)
				{
					RetComponents->push_back(CastedComp);
				}
				bFound = true;
			}
		}
		return bFound;
	}

	// Raytracing
	bool TraceLine(RayTraceInfo* Info, glm::vec3 Start, glm::vec3 End, float Interval);

private:
	// Nasty template hack.
	Entity* SpawnInternal(Entity* NewEntity);
	Component* AddComponentInternal(Component* NewComponent);
};
