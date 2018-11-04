#include "Window.h"

bool moveCamera = false;

Window::Window(int width, int height)
{
	this->width = width;
	this->height = height;
	glfwSetErrorCallback(this->error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}
	/*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//*/
	window = glfwCreateWindow(width, height, "ZPG", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetKeyCallback(window, this->key_callback);

	glfwSetCursorPosCallback(window, this->cursor_callback);

	glfwSetMouseButtonCallback(window, this->button_callback);

	glfwSetWindowFocusCallback(window, this->window_focus_callback);

	glfwSetWindowIconifyCallback(window, this->window_iconify_callback);

	glfwSetWindowSizeCallback(window, this->window_size_callback);
	

}


Window::~Window()
{
}

GLFWwindow* Window::getWindow()
{
	return window;
}

int Window::getWidth()
{
	return width;
}

int Window::getHeight()
{
	return height;
}

void Window::destroyWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Window::drawContent()
{
	//glEnable(GL_DEPTH_TEST);
	Camera* camera = new Camera();
	this->camera = camera;
	Light* light = new Light();

	Shader* shader = new Shader(camera, light);
	Shader* shader2 = new Shader(camera, light);
	Object* circle = new Object(shader2, VERTICES, sizeof(VERTICES) / sizeof(*VERTICES), sizeof(VERTICES));
	Model* k = new Model();


	Object * vSphere = new Object(shader, VERTICESSUZI, sizeof(VERTICESSUZI) / sizeof(*VERTICESSUZI), sizeof(VERTICESSUZI));
	Model* model = new Model();
	vSphere->translate(glm::vec3(-2.f, 2.f, 0.f), model);
	vSphere->scale(0.8, model);
	vSphere->rotate('y', 45.0, model);

	Model* model2 = new Model();
	vSphere->translate(glm::vec3(-2.f, -2.f, 0.f), model2);
	vSphere->scale(0.9, model2);
	vSphere->rotate('y', -45.0, model2);

	Model* model3 = new Model();
	vSphere->translate(glm::vec3(2.f, 2.f, 0.f), model3);
	vSphere->scale(1.1, model3);
	
	while (!glfwWindowShouldClose(window))
	{
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		vSphere->draw(model);
		vSphere->draw(model2);
		vSphere->draw(model3);
		//circle->draw(k);
		
		
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

void Window::error_callback(int error, const char * description)
{
	fputs(description, stderr);
}

void Window::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

	switch (key) {
	case 265:
		camera->moveForward();
		break;
	case 264:
		camera->moveBack();
		break;
	case 263:
		camera->moveLeft();
		break;
	case 262:
		camera->moveRight();
		break;
	}
}

void Window::window_focus_callback(GLFWwindow * window, int focused)
{
	printf("window_focus_callback \n");
}

void Window::window_iconify_callback(GLFWwindow * window, int iconified)
{
	printf("window_iconify_callback \n");
}

void Window::window_size_callback(GLFWwindow * window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Window::cursor_callback(GLFWwindow * window, double x, double y)
{
	printf("cursor_callback \n");
	if(moveCamera)
		camera->moveCursor(x, y);
}

void Window::button_callback(GLFWwindow * window, int button, int action, int mode)
{
	if (action == 1) {
		printf("button_callback [%d,%d,%d]\n", button, action, mode);
		moveCamera = true;
	}
	else {
		moveCamera = false;
		camera->firstMouse = true;
	}
}

