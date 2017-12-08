#version 330 core
in vec3 fragTexCoord;
out vec4 fragColor;
uniform samplerCube Texture;

void main()
{
    fragColor = texture(Texture, fragTexCoord);
}
