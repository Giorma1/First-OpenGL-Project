// HEADER FILE FOR DEFINITIONS

#pragma once
#include "glad/glad.h"
#include <iostream>
#include <array>

class Shader
{
public:
	unsigned int ID;

	Shader(const char* vPath, const char* fPath);

	void use();

	void setInt(std::string name, int value);
};

class Texture
{
public:
	Texture(unsigned int ID, unsigned int textureData, unsigned char* data, const char* texturePath, int width, int height, int neChannels, unsigned int type);
	~Texture() {
		std::cout << "Texture " << ID << " Deleted\n";
	}
	unsigned int textureData;
	unsigned int ID;
	unsigned int type;
	int width, height, nrChannels;

	const char* texturePath;

	unsigned char* data;
};

void DataForGPU(unsigned int& VBO, unsigned int &EBO, unsigned int& VAO, std::array<float, 32>& vertices, std::array<int, 6> &indices);

void CreateTexture(unsigned int ID, unsigned int &textureData, unsigned char* data, const char* texturePath, int width, int height, int nrChannels, unsigned int type);