#pragma once
#include "Shader.h"

class ShaderSkybox : public Shader
{
public:
	virtual void Link() override
	{
		Shader::Link();
		float skyboxVertices[] = {
	        // Positions
	        -1.0f,  1.0f, -1.0f,
	        -1.0f, -1.0f, -1.0f,
	         1.0f, -1.0f, -1.0f,
	         1.0f, -1.0f, -1.0f,
	         1.0f,  1.0f, -1.0f,
	        -1.0f,  1.0f, -1.0f,

	        -1.0f, -1.0f,  1.0f,
	        -1.0f, -1.0f, -1.0f,
	        -1.0f,  1.0f, -1.0f,
	        -1.0f,  1.0f, -1.0f,
	        -1.0f,  1.0f,  1.0f,
	        -1.0f, -1.0f,  1.0f,

	         1.0f, -1.0f, -1.0f,
	         1.0f, -1.0f,  1.0f,
	         1.0f,  1.0f,  1.0f,
	         1.0f,  1.0f,  1.0f,
	         1.0f,  1.0f, -1.0f,
	         1.0f, -1.0f, -1.0f,

	        -1.0f, -1.0f,  1.0f,
	        -1.0f,  1.0f,  1.0f,
	         1.0f,  1.0f,  1.0f,
	         1.0f,  1.0f,  1.0f,
	         1.0f, -1.0f,  1.0f,
	        -1.0f, -1.0f,  1.0f,

	        -1.0f,  1.0f, -1.0f,
	         1.0f,  1.0f, -1.0f,
	         1.0f,  1.0f,  1.0f,
	         1.0f,  1.0f,  1.0f,
	        -1.0f,  1.0f,  1.0f,
	        -1.0f,  1.0f, -1.0f,

	        -1.0f, -1.0f, -1.0f,
	        -1.0f, -1.0f,  1.0f,
	         1.0f, -1.0f, -1.0f,
	         1.0f, -1.0f, -1.0f,
	        -1.0f, -1.0f,  1.0f,
	         1.0f, -1.0f,  1.0f
	    };

	    glGenVertexArrays(1, &SkyboxVAO);
	    glBindVertexArray(SkyboxVAO);
	    {
	        glGenBuffers(1, &SkyboxVBO);
	        glBindBuffer(GL_ARRAY_BUFFER, SkyboxVBO);
	        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices)*sizeof(float), skyboxVertices, GL_STATIC_DRAW);
	        glVertexAttribPointer(ATTRIBUTE_VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
	        glEnableVertexAttribArray(ATTRIBUTE_VERTEX_POSITION);
	    }
	    glBindVertexArray(0);
	}
	virtual void AttachShaders() override
	{
		AttachVertex("./res/SkyBox.V.glsl");
		AttachFragment("./res/SkyBox.F.glsl");
	}
	virtual void Render() override
	{
		//Shader::Enable();

		/*glDepthMask(GL_FALSE);
        glUseProgram(Program);
        glActiveTexture(GL_TEXTURE0);
    	glUniform1i(SkyboxShader->GetUniform("Texture"), 0);
    	glBindTexture(GL_TEXTURE_CUBE_MAP, CurrentSkybox->ID);
            glUniformMatrix4fv(SkyboxShader->UView, 1, GL_FALSE, glm::value_ptr(GetViewMatrix()));
            glUniformMatrix4fv(SkyboxShader->UProjection, 1, GL_FALSE, glm::value_ptr(GetProjectionMatrix()));
            glBindVertexArray(SkyboxVAO);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        glDepthMask(GL_TRUE);*/

		//Shader::Disable();
	}
	unsigned int SkyboxVAO, SkyboxVBO;

	virtual ~ShaderSkybox()
	{
		glDeleteBuffers(1, &SkyboxVBO);
		glDeleteVertexArrays(1, &SkyboxVAO);
	}
};
