#version 330 core

in vec3 fragPosition;
in vec2 fragTexCoord;
in vec3 fragNormal;
out vec4 fragColor;

uniform sampler2D Texture;
uniform vec4 Color;

void main(void)
{
	vec4 surfaceColor = Color * texture(Texture, fragTexCoord).rgba;
	//vec4 surfaceColor = vec4(fragnormal, 1);
	fragColor = surfaceColor;
}
