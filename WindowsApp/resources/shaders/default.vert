#version 300 es

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Color;
layout(location = 2) in vec2 Texture;

varying	vec4 fragmentColor;
varying	vec2 fragmentTexture;

void main()
{
	gl_Position = Position;
	fragmentColor = Color;
	fragmentTexture = Texture;
}