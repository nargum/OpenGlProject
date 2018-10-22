#include "Shader.h"


const char* vertex_shader =
"#version 330\n"
"uniform mat4 viewMatrix;"
"uniform mat4 modelMatrix;"
"uniform mat4 projectionMatrix;"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 normal;"
"out vec4 ex_worldPosition;"
"out vec4 ex_worldNormal;"
"void main () {"
"     gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4 (vp, 1.0);"
"     ex_worldPosition = modelMatrix * vec4 (vp, 1.0);"
"     ex_worldNormal = vec4(normal, 1.0);"
"}";

const char* fragment_shader =
"#version 330\n"
"uniform vec3 lightPosition;"
"out vec4 frag_colour;"
"in vec4 ex_worldPosition;"
"in vec4 ex_worldNormal;"
"void main () {"
"     vec3 lightDirection = normalize(lightPosition - ex_worldPosition);"
"     float dot_product = max(dot(lightDirection, normalize(ex_worldNormal)), 0.0);"
"     vec4 diffuse = dot_product * vec4 (1.0, 1.0, 1.0, 1.0);"
"     vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);"
"     frag_colour =  ambient + diffuse;"
"}";

Shader::Shader(Camera* camera)
{
	glEnable(GL_DEPTH_TEST);
	this->camera = camera;
	camera->addListener(this);
	//create and compile shaders
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);
}


Shader::~Shader()
{
}

void Shader::sendUniform(const GLchar * name, glm::vec4 data)
{
	GLint uniformID = glGetUniformLocation(this->shaderProgram, name);
	if (uniformID >= 0) {
		glUniform4f(uniformID, data.x, data.y, data.z, data.w);
	}
	else {
		// in shader doesn't exist uniform variable 
	}
}

void Shader::updateModelMatrix(Object* object)
{
	GLint id = glGetUniformLocation(shaderProgram, "modelMatrix");
	glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(object->getModelMatrix()));
}

void Shader::updateViewMatrix()
{
	GLint id = glGetUniformLocation(shaderProgram, "viewMatrix");
	glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
}

void Shader::updateProjectionMatrix()
{
	GLint id = glGetUniformLocation(shaderProgram, "projectionMatrix");
	glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));
}

void Shader::updateLight()
{
	GLint myLoc = glGetUniformLocation(shaderProgram, "lightPosition");
	glProgramUniform3f(shaderProgram, myLoc, 1.f, 0.f, 2.f);
}

void Shader::useProgram()
{
	glUseProgram(shaderProgram);
}

void Shader::onEvent()
{
	updateViewMatrix();
	updateProjectionMatrix();
	updateLight();
}

