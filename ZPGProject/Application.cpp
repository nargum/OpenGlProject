#include "Application.h"



Application::Application()
{
	Window* window = new Window(800, 600);
	this->window = window;

	setupApplication();

	glfwMakeContextCurrent(window->getWindow());
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();


	float ratio = window->getWidth() / (float)window->getHeight();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

	window->drawContent();
	window->destroyWindow();
}

void Application::setupApplication()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}


Application::~Application()
{
}


void Application::getVersionInfo()
{
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
	int width, height;
	glfwGetFramebufferSize(window->getWindow(), &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
}


Application * Application::getInstance()
{
	if (instance == NULL)
		instance = new Application();

	return instance;
}

