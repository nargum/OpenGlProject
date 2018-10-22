#include "Application.h"
#include "Camera.h"
#include "Window.h"


Application * Application::instance;
Camera* Window::camera = new Camera();


int main(void)
{
	Application* application = Application::getInstance();
	
}