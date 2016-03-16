#pragma once
#include "Resource.h"

#include <vector>
#include <glm/glm.hpp>

#define ATTRIBUTE_VERTEX_POSITION 0
#define ATTRIBUTE_UV_COORD 1
#define ATTRIBUTE_NORMAL 2

class Model : public Resource
{
public:
	Model(std::string NewName, std::string NewPath) : Resource(NewName, NewPath) {}
	virtual bool Load() override;
	virtual void Destroy() override;
	void CalculateCollisionInfo();
    std::vector<unsigned short> VertexIndices;
	std::vector<float> Vertices, Normals, UVs;

	float MaximumRadius;
	glm::vec3 CentreOffset;

	unsigned int VBO, IBO, UVBO, NBO;
	unsigned int VAO;
};
