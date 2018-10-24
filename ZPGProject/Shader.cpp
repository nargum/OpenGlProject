#include "Shader.h"


const char* vertex_shader =
"#version 330\n"
"uniform mat4 viewMatrix;"
"uniform mat4 modelMatrix;"
"uniform mat4 projectionMatrix;"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 normal;"
"out vec4 ex_worldPosition;"
"out vec3 ex_worldNormal;"
"void main () {"
"     gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4 (vp, 1.0);"
"     ex_worldPosition = modelMatrix * vec4 (vp, 1.0);"
"     ex_worldNormal = transpose(inverse(mat3(modelMatrix))) * normal;"
"}";

const char* fragment_shader =
"#version 330\n"
"uniform vec3 lightPosition;"
"uniform vec3 viewPosition;"
"out vec4 frag_colour;"
"in vec4 ex_worldPosition;"
"in vec3 ex_worldNormal;"
"void main () {"
"     vec4 lightDirection = normalize(vec4(lightPosition, 1.0) - ex_worldPosition);"
"     float dot_product = max(dot(lightDirection, normalize(vec4(ex_worldNormal, 1.0))), 0.0);"
"     vec4 diffuse = dot_product * vec4 (1.0, 1.0, 1.0, 1.0);"
"     vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);"
"     float specularStrength = 0.8;"
"     vec3 viewDirection = normalize(viewPosition - vec3(ex_worldPosition));"
"     vec3 reflectDirection = reflect(vec3(-lightDirection), ex_worldNormal);"
"     float dot_product2 = pow(max(dot(viewDirection, reflectDirection), 0.0),25);"
"     vec3 specular = specularStrength * dot_product2 * vec3(1.0, 1.0, 1.0);"
"     frag_colour =  (ambient + diffuse + vec4(specular, 1.0)) * vec4(1.0, 0.0, 0.0, 1.0);"
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

	checkShaderCompilation();
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
	glProgramUniform3f(shaderProgram, myLoc, 0.f, 0.f, 0.5f);
}

void Shader::updateCameraPosition()
{
	glm::vec3 camPosition = camera->getCamPosition();
	GLint myLoc = glGetUniformLocation(shaderProgram, "viewPosition");
	glProgramUniform3f(shaderProgram, myLoc, camPosition.x, camPosition.y, camPosition.z);
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
	updateCameraPosition();
}

void Shader::checkShaderCompilation()
{
	GLint status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

