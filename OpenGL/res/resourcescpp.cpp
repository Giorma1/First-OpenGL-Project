// RESOURCE FILE FOR DECLARATIONS

#include "res/header.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" // Library to read images

#include <fstream>
#include <sstream>


// With this function checking if there is a errors in shader compilation or in program linking
bool checkStatus(unsigned int ID, PFNGLGETPROGRAMIVPROC getterFuncName, PFNGLGETPROGRAMINFOLOGPROC getinfologFunc, unsigned int statusType) {
	int success;
	char infolog[512];

	getterFuncName(ID, statusType, &success);
	if (!success)
	{
		getinfologFunc(ID, 512, NULL, infolog);
		std::cout << "Shaders Failed " << infolog;
		return false;
	}
	std::cout << "Shader " << ID <<  " Loaded Successfully \n";
	return true;
}

Shader::Shader(const char* vPath, const char* fPath) // Class Shader constructor, geting paths to shader files and reading form it
{
	std::string vertexCode, fragmentCode;
	std::fstream vertexFile, fragmentFile;

	

	vertexFile.exceptions(std::ifstream::badbit | std::ifstream::failbit); // Checking if there is a problem when reading files
	fragmentFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	try
	{
		vertexFile.open(vPath);
		fragmentFile.open(fPath);

		std::stringstream vertexStream, fragmentStream;

		vertexStream << vertexFile.rdbuf(); // Reading form files and saving it in Stream variables
		fragmentStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexCode = vertexStream.str(); // Saving code readed from files in string type
		fragmentCode = fragmentStream.str();

	}
	catch (const std::exception&)
	{
		std::cout << "FAILED::TO::OPEN::FILE";
	}
	
	const char* vertexSource = vertexCode.c_str(); // Saving code readed from file into C Type string
	const char* fragmentSource = fragmentCode.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // Creating shaders
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	ID = glCreateProgram(); //Creating program

	glShaderSource(vertexShader, 1, &vertexSource, NULL); // Binding shader source code readed from file to shaders
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

	glCompileShader(vertexShader); // Compiling shaders
	glCompileShader(fragmentShader);

	glAttachShader(ID, vertexShader); // Attaching shaders to program
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID); // Linking program

	checkStatus(vertexShader, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS); // Calling check status function to check if there is a errors
	checkStatus(ID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
	
	glDeleteShader(vertexShader); // Deleting shaders
	glDeleteShader(fragmentShader);

}	

void Shader::use() // Method to use shader program
{
	glUseProgram(ID);
}

void Shader::setInt(std::string name, int value) // Method for set unifrom variables easly in shaders
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

Texture::Texture(unsigned int ID, unsigned int textureData, unsigned char* data, 
	const char* texturePath, int width, int height, int nrChannels, unsigned int type) // Texture class constructor
{
	this->ID = ID;
	this->type = type;
	this->textureData = textureData;
	this->data = data;
	this->texturePath = texturePath;
	this->width = width;
	this->height = height;
	this->nrChannels = nrChannels;
}

void CreateTexture(unsigned int ID, unsigned int &textureData, unsigned char* data,
	const char* texturePath, int width, int height, int nrChannels, unsigned int type) // Function to create Texture
{
	glGenTextures(1, &textureData);
	glActiveTexture(ID); // Activating textures with ID
	glBindTexture(GL_TEXTURE_2D, textureData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	
	if (data) // If there is a data create texture, if not dont
	{
		std::cout << "Loaded texture: " << texturePath << " (" << width << "x" << height << ", " << nrChannels << " channels)\n";
		glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data); // Type is if texture is RGB or RGBA
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture: " << texturePath << std::endl;
	}
	stbi_image_free(data); // Deleting data to free memory

}

void DataForGPU(unsigned int& VBO, unsigned int& EBO, unsigned int& VAO, 
	std::array<float, 32> &vertices, std::array<int, 6> &indices) // Giving Data to GPU
{

	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);
}