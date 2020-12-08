#version 330 core

layout (location = 0) out vec4 color; //defines where vairable location is

uniform vec4 color_uniform;
uniform vec2 light_position;

in vec4 position;

void main()
{
	float intensity = 1.0 / length(position.xy - light_position);
	color = color_uniform * intensity;
}