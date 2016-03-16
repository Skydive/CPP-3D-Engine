#include "Shader.h"

#include <iostream>
#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "File.h"


Shader::Shader()
{
	Program = glCreateProgram();

	Color = {1, 1, 1, 1};

	AttachShaders();
	Link();
}

void Shader::AttachShaders()
{
	AttachVertex("./res/Basic.V.glsl");
	AttachFragment("./res/Basic.F.glsl");
}

Shader::~Shader()
{
	if(glIsShader(VS))
	{
		glDeleteShader(VS);
	}
	if(glIsShader(GS))
	{
		glDeleteShader(GS);
	}
	if(glIsShader(FS))
	{
		glDeleteShader(FS);
	}
	glDeleteProgram(Program);
}

void Shader::AttachVertex(const std::string& path)
{
	VS = LoadShader(path, GL_VERTEX_SHADER);
	glAttachShader(Program, VS);
}
void Shader::AttachGeometry(const std::string& path)
{
	GS = LoadShader(path, GL_GEOMETRY_SHADER);
	glAttachShader(Program, GS);
}
void Shader::AttachFragment(const std::string& path)
{
	FS = LoadShader(path, GL_FRAGMENT_SHADER);
	glAttachShader(Program, FS);
}

void Shader::Enable()
{
	glUseProgram(Program);

	glUniform4f(GetUniform("Color"), Color.x, Color.y, Color.z, Color.w);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(GetUniform("Texture"), 0);
	glBindTexture(GL_TEXTURE_2D, BindTexture->ID);
}
void Shader::Render(){}
void Shader::Disable()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool Shader::StoreUniform(std::string name)
{
	GLint UniformLoc = glGetUniformLocation(Program, name.c_str());
	if (UniformLoc == -1)
	{
		std::cout << "Could not bind uniform: " << name << std::endl;
		return false;
	}
	Uniforms[name] = UniformLoc;
	return true;
}
int Shader::GetUniform(std::string name)
{
	return Uniforms[name];
}

void Shader::Link()
{
	glLinkProgram(Program);
	GLint success = GL_FALSE;
	glGetProgramiv(Program, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        fprintf(stderr, "glLinkProgram: Error:"); PrintLog(Program);
		return;
    }
	StoreUniform("Model");
	StoreUniform("View");
	StoreUniform("Projection");

	StoreUniform("Texture");
	StoreUniform("Color");

	UModel = GetUniform("Model");
	UView = GetUniform("View");
	UProjection = GetUniform("Projection");
}

unsigned int Shader::LoadShader(const std::string& path, int shadertype)
{
	std::string source = File(path).FileData;
	if(source.empty())
	{
		std::cout << "Error opening " << path << ": "; perror("");
		return 0;
	}
	GLuint CreatedShader = glCreateShader(shadertype);
	const char* cstr = source.c_str();
	glShaderSource(CreatedShader, 1, &cstr, NULL);
	glCompileShader(CreatedShader);
	GLint success = GL_FALSE;
	glGetShaderiv(CreatedShader, GL_COMPILE_STATUS, &success);
	if(success == GL_FALSE)
	{
		fprintf(stderr, "%s:", path.c_str()); PrintLog(CreatedShader);
		glDeleteShader(CreatedShader);
		return 0;
	}

	return CreatedShader;
}

void Shader::PrintLog(unsigned int object)
{
	GLint log_length = 0;
	if (glIsShader(object))
	{
		glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
	}
	else if (glIsProgram(object))
	{
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
	}
	else
	{
		std::cout << "PrintLog: Not a shader or program!" << std::endl;
		return;
	}

	//  char* log = (char*)malloc(log_length);
	std::unique_ptr<char> log = std::unique_ptr<char>(new char[log_length]);

	if (glIsShader(object))
	{
		glGetShaderInfoLog(object, log_length, 0, log.get());
	}
	else if (glIsProgram(object))
	{
		glGetProgramInfoLog(object, log_length, 0, log.get());
	}

	std::cout << log.get() << std::endl;
}
