#pragma once

//Include GLEW
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>  
#include <stdlib.h>
#include <stdio.h>

#include "Object.h"
#include "Shader.h"
#include "Camera.h"
#include "VSphere.h"
#include "Suzi.h"


class Window
{
public:
	Window(int width, int height);
	~Window();
	GLFWwindow* getWindow();
	int getWidth();
	int getHeight();
	void destroyWindow();
	void drawContent();
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow *window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
	

private:
	GLFWwindow* window = NULL;
	static Camera* camera;
	int width;
	int height;
	
};

