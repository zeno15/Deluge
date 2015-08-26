#version 330

in vec2 texCoords;
in vec4 colour;

uniform sampler2D tex;

out vec4 frag_Colour;

void main(void)
{
    frag_Colour = texture(tex, texCoords) * colour;
}