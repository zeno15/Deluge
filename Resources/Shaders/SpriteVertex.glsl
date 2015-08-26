#version 330

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec4 in_Colour;
layout (location = 2) in vec2 in_TexUV;

uniform mat4 View = mat4(1.0f);

out vec2 texCoords;
out vec4 colour;

void main(void)
{
    gl_Position = View * vec4(in_Position, 1.0f);
    texCoords = in_TexUV;
    colour = in_Colour;
}