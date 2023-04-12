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
glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
GLfloat camera_speed = 5.0f;
GLfloat camera_yaw = -90.0f;
GLfloat camera_pitch = 0.0f;
GLfloat camera_sensitivity = 0.1f;
GLfloat camera_zoom = 45.0f;
bool keys[1024];
GLfloat delta_time = 0.0f;
GLfloat last_frame = 0.0f;
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
bool jwla2 = false;
bool sarawa = false;
GLfloat 	deltaTime = 0.0f;
GLfloat 	lastTime = 0.0f;
//////////////////////////////*****************************************************************************************
// Camera h

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat Xchange, GLfloat Ychange);

	glm::vec3 getCameraPosition();
	glm::vec3 getCameraDirection();
	glm::mat4 calculateViewMatrix();



	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;
	void Update();
};

//////////////////////////////*****************************************************************************************
// Camera Cpp

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	Update();
}
/////////////
void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	//delta time is toslow down frames in games otherwise have 10k frame per second
	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}
	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}
	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}
	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
	if (keys[GLFW_KEY_R]) //rotate 
	{
		sarawa = true;
	}
	if (keys[GLFW_KEY_F]) //reset rotate
	{
		sarawa = false;
	}
}

void Camera::mouseControl(GLfloat Xchange, GLfloat Ychange)
{
	Xchange *= turnSpeed;
	Ychange *= turnSpeed;
	yaw += Xchange;
	pitch += Ychange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;

	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	Update();
}

glm::mat4 Camera::calculateViewMatrix()
{

	return glm::lookAt(position, position + front, up); //lookAt functioneka wata bnwara :)


}
//////////////
///vec3 for shininess and stuff specular lighting 
glm::vec3 Camera::getCameraPosition()
{
	return position; // hold that position and pass it into our shader , now we go to shader vert ...
}
//////////////
glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}

//////////////
void Camera::Update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

Camera::~Camera()
{
}

////////
Camera camera;
///////
/*
 Window mainWindow; //for other projects
mainWindow = Window(1920, 1080); //1280 , 1024 or 1024, 768 mainWindow = Window(1366, 768); //this line is inside int main

*/
//GLFWwindow* mainWindow;
Window mainWindow; //for other projects

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
	mainWindow = Window(1920, 1080); //1280 , 1024 or 1024, 768 mainWindow = Window(1366, 768);
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
	//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-__________camera movement
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);

	camera.keyControl(mainWindow.getsKeys(), deltaTime);
	camera.mouseControl(mainWindow.getXchange(), mainWindow.getYchange());
	//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

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

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		//uniformAmbientIntensity = 0, uniformAmbientColour = 0, uniformDirection = 0, uniformDiffuseintensity = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;

	while (!glfwWindowShouldClose(window)) {
		glClearColor(1.0f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//*********************************************************************************
		glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 80.0f / 60.0f, 0.1f, 100.0f);
		//glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y,
			camera.getCameraPosition().z);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
			viewMatrix * viewMatrix;
		}
		if (jwla2)
		{
			axis = glm::vec3(0.5f, 1.0f, 0.5f);
			rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
			viewMatrix = glm::lookAt(
				glm::vec3(0.9f, 2.5f, 0.6f), // camera position
				glm::vec3(0.5f, 2.0f, 0.5f), // target position
				glm::vec3(1.0f, 3.0f, 1.0f)  // up vector
			);
			viewMatrix* viewMatrix;
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
			jwla2 = false;
		}
		if (key == GLFW_KEY_S) {
			jwla2 = true;
			jwla = false;

		}
	}
	

}