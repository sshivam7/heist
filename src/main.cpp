/**
* main.cpp
* Description: Main program entry point for OpenGl Heist Game
* @author Shivam Sood
* @version 1.0 2022/03/29
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

#include "game/game.h"
#include "../lib/stb_image.h"

// Function declarations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void config_window(GLFWwindow* window);

// Constants 
const unsigned int SCREEN_WIDTH = 1000;
const unsigned int SCREEN_HEIGHT = 700;
const char* GAME_NAME = "Heist";

Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char* argv) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create game window
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME, nullptr, nullptr);

	if (window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	config_window(window);

	// GLAD: Load all glad function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
	}

	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// OpenGL configuration
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// initialize game
	game.init();

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window)) {
		// Delta time calculations
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();

		// Game functionality
		game.processInput(deltaTime);
		game.update(deltaTime);

		// Set color and render game data
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		game.render();
		glfwSwapBuffers(window);
	}

	// Delete data and terminate
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	// Exit on escape
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			game.set_key(key, true);
		else if (action == GLFW_RELEASE)
			game.set_key(key, false);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void config_window(GLFWwindow* window) {
	// Center window in screen
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	unsigned int pos_x = (mode->width / 2) - (SCREEN_WIDTH / 2);
	unsigned int pos_y = (mode->height / 2) - (SCREEN_HEIGHT / 2);

	glfwSetWindowPos(window, pos_x, pos_y);

	// Set Logo
	GLFWimage images[1];
	images[0].pixels = stbi_load("resources/logo.png", &images[0].width, &images[0].height, 0, 4);
	glfwSetWindowIcon(window, 1, images);
	stbi_image_free(images[0].pixels);
}