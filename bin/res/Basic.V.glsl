#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 inUVCoord;
layout (location = 2) in vec3 normal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec2 fragTexCoord;
out vec3 fragNormal;


void main(void)
{
	fragTexCoord = inUVCoord;
	gl_Position = Projection * View * Model * vec4(position, 1.0);
    //fragNormal = normalize(NormalMatrix * normal);
}
