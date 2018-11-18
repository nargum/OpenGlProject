#include "Application.h"
#include "Camera.h"
#include "Window.h"
#include "ObjectHandler.h"


Application * Application::instance;
Camera* Window::camera = new Camera();
ObjectHandler* Window::handler = new ObjectHandler();


int main(void)
{
	Application* application = Application::getInstance();
	
}