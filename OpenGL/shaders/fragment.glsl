// FRAGMENT SHADER

#version 430 core

out vec4 gl_FragColor;

in vec4 Colors;  // Getting colors from vertex shader
in vec2 TexCordinates; // Getting texture cordinates form vertex shader

uniform sampler2D texture1; // Creating uniform variables for textures
uniform sampler2D texture2;

void main ()
{	
	// Mixing two textures,	last value means, if set to 0, first texture will show only and if set to 1, 
	// Second texture will show only, so setting it in te bettwen 0-1 two textures will be mixed
	gl_FragColor = mix(texture(texture1, TexCordinates), texture(texture2, TexCordinates), 0.4); 
}