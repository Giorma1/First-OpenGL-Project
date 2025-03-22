// MAIN FILE

#include "res/header.h"

#include "GLFW/glfw3.h"
#include "stb_image.h"

void frame_buffer_size_callback(GLFWwindow* window, int width, int height) // Functions to scale window when resizing
{
	glViewport(0, 0, width, height);
}

int main() //Main function
{
	if (!glfwInit()) //GLFW initialisation
	{
		std::cout << "GLFW::INITIALISATION::FAILED ";
		return -1;
	}
	//Hints for GLFW window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "OpenGL", NULL, NULL); //Creating window
	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback); // Setting frame buffer size callback for window to scale when resizing
	glfwMakeContextCurrent(window); // Setting context to window

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))) // GLAD initialisation
	{
		std::cout << "GLAD::INITIALISATION::FAILED";
		return -1;
	}
	// Vertice cordinates
	std::array<float, 32> vertices = {  
	  // Position Cordinates			Vertice Colors				Texture Cordinates
		-0.5f, 0.7f, 0.0f,				1.0f, 0.0f, 0.0f,			0.0f, 1.0f,
		0.5f, 0.7f, 0.0f,				0.0f, 1.0f, 0.0f,			1.0f, 1.0f,
		0.5f, -0.7f, 0.0f,				0.0f, 1.0f, 0.0f,			1.0f, 0.0f,
		-0.5f, -0.7f, 0.0f,				0.0f, 0.0f, 1.0f,			0.0f, 0.0f
	};

	// Indices 
	std::array<int, 6> indices = {
		0, 1, 3,
		1, 2, 3
	};

	// Data for buffers, vertex and textures
	unsigned int VBO = 0, EBO = 0, VAO = 0, texture = 0; 

	// Data for textures
	int width = 0, height = 0, nrChannels = 0;
	unsigned char* data = nullptr; 

	//Path to textures
	const char* texturePath = "assets/wall.jpg";
	const char* texturePath2 = "assets/awesomeface.png";
	
	Texture tex1(GL_TEXTURE0, texture, data, texturePath, width, height, nrChannels, GL_RGB); // Creating texture object 1 and 2
	Texture tex2(GL_TEXTURE1, texture, data, texturePath2, width, height, nrChannels, GL_RGBA);
	stbi_set_flip_vertically_on_load(true); // Fliping textures vertically, because its loading upside down

	CreateTexture(tex1.ID, tex1.textureData, tex1.data, tex1.texturePath, tex1.width, tex1.height, tex1.nrChannels, tex1.type); //Creating textures
	CreateTexture(tex2.ID, tex2.textureData, tex2.data, tex2.texturePath, tex2.width, tex2.height, tex2.nrChannels, tex2.type);
	
	DataForGPU(VBO, EBO, VAO, vertices, indices); //Calling function dataforgpu to give data to gpu
	
	Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl"); // Giving shader object path to shaders files
	shader.use(); // Activating shader program

	while (!glfwWindowShouldClose(window)) // While loop for window
	{
		glClear(GL_COLOR_BUFFER_BIT);

		shader.setInt("texture1", 0); // Setting texture values to 0 and 1 values in fragment shader
		shader.setInt("texture2", 1);
		
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Drawing elements
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}