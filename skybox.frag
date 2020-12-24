#version 330 core
in vec3 TexCoords;
out vec4 color;

uniform samplerCube skybox;

void main()
{
    //color = texture(skybox, TexCoords);
    color=vec4(1.0f, 0.5f, 0.2f, 1.0f);
}