#include "Shader.h"


Shader::Shader(Camera* camera, Light* light, std::string vertex_shader, std::string fragment_shader)
{
	string v = loadFile(vertex_shader);
	string f = loadFile(fragment_shader);
	this->vertex_shader = v.c_str();
	this->fragment_shader = f.c_str();
	glEnable(GL_DEPTH_TEST);
	this->camera = camera;
	this->light = light;
	camera->addListener(this);
	light->addListener(this);
	light->publishEvent();
	//create and compile shaders
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &this->vertex_shader, NULL);
	glCompileShader(vertexShader);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &this->fragment_shader, NULL);
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

void Shader::updateModelMatrix(glm::mat4 modelMatrix)
{
	GLint id = glGetUniformLocation(shaderProgram, "modelMatrix");
	glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(modelMatrix));
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
	//glProgramUniform3f(shaderProgram, myLoc, -5.f, 0.f, 0.5f);
	glProgramUniform4f(shaderProgram, myLoc, light->getLightPosition().x, light->getLightPosition().y, light->getLightPosition().z, light->getLightPosition().w);
	//glProgramUniform4f(shaderProgram, myLoc, 0.0, 0.0, 0.0, 1.0);
	GLint myColor = glGetUniformLocation(shaderProgram, "lightColor");
	glProgramUniform4f(shaderProgram, myColor, light->getLightColor().x, light->getLightColor().y, light->getLightColor().z, light->getLightColor().w);
}

void Shader::updateCameraPosition()
{
	glm::vec3 camPosition = camera->getCamPosition();
	GLint myLoc = glGetUniformLocation(shaderProgram, "viewPosition");
	glProgramUniform3f(shaderProgram, myLoc, camPosition.x, camPosition.y, camPosition.z);
}

void Shader::updateMaterial(Material mat)
{
	GLint ambient = glGetUniformLocation(shaderProgram, "materialAmbient");
	glProgramUniform3f(shaderProgram, ambient, mat.ambient.x, mat.ambient.y, mat.ambient.z);

	GLint diffuse = glGetUniformLocation(shaderProgram, "materialDiffuse");
	glProgramUniform3f(shaderProgram, diffuse, mat.diffuse.x, mat.diffuse.y, mat.diffuse.z);

	GLint specular = glGetUniformLocation(shaderProgram, "materialSpecular");
	glProgramUniform3f(shaderProgram, specular, mat.specular.x, mat.specular.y, mat.specular.z);

	GLint shininess = glGetUniformLocation(shaderProgram, "shininess");
	glProgramUniform1f(shaderProgram, shininess, mat.shininess);

}

void Shader::updateTexture(Texture* texture)
{
	texture->bindTexture();
	GLint uniformID = glGetUniformLocation(shaderProgram, "textureUnitID");
	glUniform1i(uniformID, 0);
}

void Shader::useProgram()
{
	glUseProgram(shaderProgram);
}

void Shader::onEvent()
{
	updateCameraPosition();
}

void Shader::onLightEvent()
{
	updateLight();
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

string Shader::loadFile(std::string fileName)
{
	std::string line;
	std::string text;
	bool first = true;

	std::ifstream myFile(fileName);
	if (myFile.is_open()) {
		while (std::getline(myFile, line)) {
			
				line += '\n';
				text += line;
			
		}

		myFile.close();
	}

	return text;
}

