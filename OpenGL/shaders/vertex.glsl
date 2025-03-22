// VERTEX SHADER

#version 430 core

in layout (location = 0) vec4 aPos;  // Getting positions from vertices array
in layout (location = 1) vec4 aColor; // Getting colors from vertices array
in layout (location = 2) vec2 aTexCord; // Getting texture cordinates from vertices array

out vec4 Colors; //Sending Colors to fragment shader
out vec2 TexCordinates; //Sending Texture cordinates to fragment shader

void main() 
{
	gl_Position = aPos;
	Colors = aColor;
	TexCordinates = aTexCord;
}