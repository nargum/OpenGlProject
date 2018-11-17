#include "Window.h"
bool shoot = false;
int sirka = 600;

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

	GLuint id1 = 1;
	GLuint id2 = 2;
	GLuint id3 = 3;
	GLuint id4 = 4;
	
	Material gold;
	gold.ambient = glm::vec3(0.24725, 0.1995, 0.0745);
	gold.diffuse = glm::vec3(0.75164, 0.60648, 0.22648);
	gold.specular = glm::vec3(0.628281, 0.555802, 0.366065);
	gold.shininess = 0.4 * 128;

	Material pearl;
	pearl.ambient = glm::vec3(0.25, 0.20725, 0.20725);
	pearl.diffuse = glm::vec3(1.0, 0.829, 0.829);
	pearl.specular = glm::vec3(0.296648, 0.296648, 0.296648);
	pearl.shininess = 0.088 * 128;

	Shader* shader2 = new Shader(camera, light);
	Shader* shader = new Shader(camera, light);
	

	ShaderLoader* loader = new ShaderLoader();
	loader->addShader(shader);
	loader->addShader(shader2);
	loader->loadShaders();

	Model* circle = new Model(shader2, VERTICES, sizeof(VERTICES) / sizeof(*VERTICES), sizeof(VERTICES));
	Model * suzi = new Model(shader, VERTICESSUZI, sizeof(VERTICESSUZI) / sizeof(*VERTICESSUZI), sizeof(VERTICESSUZI));



	Object* k = new Object(pearl,id1);
	Object* model = new Object(pearl, id2);
	model->translate(glm::vec3(-2.f, 2.f, 0.f));
	model->scale(0.6);
	

	k->translate(glm::vec3(-1.f, 0.f, 0.f));
	k->rotate('z', 30.0);
	

	Object* model2 = new Object(gold, id3);
	model2->translate(glm::vec3(-2.f, -2.f, 0.f));
	

	Object* model3 = new Object(gold, id4);
	model3->translate(glm::vec3(2.f, 2.f, 0.f));
	
	
	while (!glfwWindowShouldClose(window))
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		
		
		suzi->draw(k);
		circle->draw(model);
		circle->draw(model2);
		circle->draw(model3);
		
		
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

	if (camera->getMoveCamera())
		camera->moveCursor(x, y);

	if (shoot) {
		GLbyte color[4];
		GLfloat depth;
		GLuint indexx;

		GLint X = (GLint)x;
		GLint Y = (GLint)y;

		int newy = (int)sirka - Y - 10;

		glReadPixels(X, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(X, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(X, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &indexx);

		/*printf(Clicked on pixel %d, %d, color % 02hhx % 02hhx % 02hhx % 02hhx, depth
			%f, stencil index %u\n, x, y, color[0], color[1], color[2], color[3], depth, index);*/
		printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n", X, Y, color[0], color[1], color[2], color[3], depth, indexx);

		shoot = false;
	}
}

void Window::button_callback(GLFWwindow * window, int button, int action, int mode)
{
	if (action == 1 && button == 1) {
		printf("button_callback [%d,%d,%d]\n", button, action, mode);
		camera->setMoveCamera(true);
	}
	else {
		camera->setMoveCamera(false);
		camera->firstMouse = true;
	}

	if (button == 0) {
		shoot = true;
	}
}


