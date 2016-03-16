#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 inUVCoord;
layout (location = 2) in vec3 normal;

layout (std140) uniform Matrices
{
    mat4 Model;
    mat4 View;
	mat4 Projection;
};

out vec2 texCoord;


out VS_OUT {
    vec3 normal;
} vs_out;

void main(void)
{
	texCoord = inUVCoord;
	gl_Position = Projection * View * Model * vec4(position, 1.0);

	mat3 normalMatrix = mat3(transpose(inverse(View * Model)));
    vs_out.normal = normalize(vec3(Projection * vec4(normalMatrix * normal, 1.0)));
}
