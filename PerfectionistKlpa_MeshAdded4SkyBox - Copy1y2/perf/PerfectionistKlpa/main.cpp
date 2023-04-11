#include <iostream>
#include "Window.h"
#include<cmath>
#include<string.h>
#include<stdlib.h>
//#include<GL/glew.h>
				//#include<GLFW/glfw3.h>
#include<cstdio>
//#include 
//#include"glad.h"
#include "HeightmapTerrain.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>




#include<glm/gtc/type_ptr.hpp>
#include "stb_image.h"
//#include "stb_image.h"
//#define STB_IMAGE_IMPLEMENTATION
using namespace std;
////////////////
// const GLuint WIDTH = 800, HEIGHT = 600;

// Camera variables

////////////////
/// <rotate>

//this class not called yet 
							//loadKrdn lod;
							// lod.loadka();
//class loadKrdn
//{
//    
//public:
//    ///////////<textureID filelocation  >////////
//    GLuint textureID;
//    
//
//    int width, height, bitdepth;
//    
//
//    const char* fileSize;
//    unsigned char* texData = stbi_load(fileSize, &width, &height, &bitdepth, 0);
//    void loadka();
//    ~loadKrdn();
//};
//
//void loadKrdn::loadka()
//{
//    textureID = 0;
//    width = 110;
//    height = 110;
//    bitdepth = 0;
//    fileSize = "";
//    //stbi_set_flip_vertically_on_load(true);
//    //////////////</textureID filelocation  >////////////////////
//
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
//
//    //*******<load>************
//   
//    if (!texData)
//    {
//        printf(" failed ...to do stuff find: %s\n", fileSize);
//        return;
//    }
//    ////// gl stuff
//    glGenTextures(1, &textureID);
//    glBindTexture(GL_TEXTURE_2D, textureID);
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
//    glGenerateMipmap(GL_TEXTURE_2D);
//    ///////////////////////////// unbind
//    glBindTexture(GL_TEXTURE_2D, 0);
//
//    //stbi_image_free(texData);
//
//    //*******</load>************
//
//    //*******<use>************
//    //*******</use>************
//}


/// <class camera>

/// </summary>
/// <re</class camera>
/// 
bool jwla = false;


	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW\n";
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(1800, 900, "Heightmap Terrain", nullptr, nullptr);
	if (!window) {
		std::cerr << "Failed to create window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		glfwTerminate();
		return -1;
	}
	// Set the key callback function
	glfwSetKeyCallback(window, key_callback);
	//////////////////////////////////////////
	glEnable(GL_DEPTH_TEST);

	HeightmapTerrain terrain("heightmap.png", 256, 10.0f);
	//HeightmapTerrain terrain("irelandHeightMap01.raw", 255, 10.0f);



	while (!glfwWindowShouldClose(window)) {
		glClearColor(1.0f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//*********************************************************************************
		glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 80.0f / 60.0f, 0.1f, 100.0f);
		//glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(glm::value_ptr(projectionMatrix));
		//*********************************************************************************

		glm::mat4 viewMatrix = glm::lookAt(
			glm::vec3(0.9f, 15.5f, 0.6f), // camera position
			glm::vec3(0.5f, 0.0f, 0.5f), // target position
			glm::vec3(1.0f, 2.0f, 1.0f)  // up vector
		);

		float angle = 45.0f;
		glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
		// Define the rotation matrix
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
		if (jwla)
		{
			axis = glm::vec3(0.5f, 1.0f, 0.5f);
			rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
			viewMatrix = glm::lookAt(
				glm::vec3(0.9f, 1.5f, 0.6f), // camera position
				glm::vec3(0.5f, 0.0f, 0.5f), // target position
				glm::vec3(1.0f, 5.0f, 1.0f)  // up vector
			);
		}

		glm::mat4 model(1.0f);
		model = glm::mat4(1.0f);

		//model = glm::rotate(model, 10 * 4, glm::vec3(0.0f, 1.0f, 0.0f));

			//model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
			//model = glm::rotate(model, 10, glm::vec3(1.0f, -1.0f, 0.0f));


		//glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(glm::value_ptr(viewMatrix));
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glfwPollEvents();
		terrain.render();
		glfwSwapBuffers(window);
		//loadKrdn lod;
	   // lod.loadka();
	}
	
	glfwTerminate();
	return 0;

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		
		if (key == GLFW_KEY_W) {
			jwla = true;
		}
	}
	

}