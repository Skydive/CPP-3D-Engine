#pragma once
#include "Object.h"
#include "File.h"
#include "Texture.h"

#include <map>
#include <glm/glm.hpp>

#define UBO_MODEL 0
#define UBO_VIEW 1
#define UBO_PROJECTION 2
#define UBO_MATRIX_LENGTH 3

class Shader : public Object
{
public:
	Shader();
	virtual ~Shader();
	virtual void AttachShaders();

	void AttachVertex(const std::string& path);
	void AttachGeometry(const std::string& path);
	void AttachFragment(const std::string& path);

	virtual void Link();
	virtual void Enable();
	virtual void Render();
	virtual void Disable();

	static void PrintLog(unsigned int object);
	static unsigned int LoadShader(const std::string& path, int shadertype);

	bool StoreUniform(std::string name);
	int GetUniform(std::string name);
	int UModel, UView, UProjection, UNormal;

	Texture* BindTexture;
	glm::vec4 Color;

	std::string Name;
	unsigned int Program;

protected:
	unsigned int VS, GS, FS;
	std::map<std::string, int> Uniforms;
};
