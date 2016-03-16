#version 330

in vec3 vPosition;
in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D UniformTexture;
uniform vec4 UniformColor;

void main(void)
{
	vec4 surfaceColor = UniformColor * texture(UniformTexture, texCoord).rgba;
	fragColor = surfaceColor;
}
