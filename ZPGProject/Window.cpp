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
	Material mat;
	mat.ambient = glm::vec3(0.0, 0.0, 0.0);
	mat.diffuse = glm::vec3(0.5, 0.0, 0.0);
	mat.specular = glm::vec3(0.7, 0.6, 0.6);
	Material mat2;
	mat2.ambient = glm::vec3(1.0f, 0.5f, 0.31f);
	mat2.diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
	mat2.specular = glm::vec3(0.5f, 0.5f, 0.5f);
	
	Material gold;
	gold.ambient = glm::vec3(0.24725, 0.1995, 0.0745);
	gold.diffuse = glm::vec3(0.75164, 0.60648, 0.22648);
	gold.specular = glm::vec3(0.628281, 0.555802, 0.366065);

	Shader* shader2 = new Shader(camera, light);
	Shader* shader = new Shader(camera, light);
	

	ShaderLoader* loader = new ShaderLoader();
	loader->addShader(shader);
	loader->addShader(shader2);
	loader->loadShaders();

	Object* circle = new Object(shader2, VERTICES, sizeof(VERTICES) / sizeof(*VERTICES), sizeof(VERTICES));
	Model* k = new Model(gold);
	


	Object * suzi = new Object(shader, VERTICESSUZI, sizeof(VERTICESSUZI) / sizeof(*VERTICESSUZI), sizeof(VERTICESSUZI));
	Model* model = new Model(gold);
	model->translate(glm::vec3(-2.f, 2.f, 0.f));
	model->scale(0.6);
	

	k->translate(glm::vec3(-1.f, 0.f, 0.f));
	k->rotate('z', 30.0);
	

	Model* model2 = new Model(mat2);
	model2->translate(glm::vec3(-2.f, -2.f, 0.f));
	

	Model* model3 = new Model(mat2);
	model3->translate(glm::vec3(2.f, 2.f, 0.f));
	
	
	while (!glfwWindowShouldClose(window))
	{
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		suzi->draw(k);
		circle->draw(model);
		circle->draw(model2);
		circle->draw(model3);
		
		//light->setLightPosition(glm::vec4(0.02f, 0.0, 0.0, 0.0));
		//light->setLightPosition(2.0);
		
		
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

