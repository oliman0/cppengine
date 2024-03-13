#include "shader.h"

Shader::Shader(const char* vertPath, const char* fragPath) {
	std::string vertSrc;
	std::ifstream fileStream(vertPath, std::ios::in);
	std::ostringstream stringStream;

	if (fileStream) {
		stringStream << fileStream.rdbuf();
		vertSrc = stringStream.str();
	}
	else {
		std::cerr << "Failed to open Vertex Shader file." << std::endl;
	}

	std::string fragSrc;
	fileStream = std::ifstream(fragPath, std::ios::in);

	if (fileStream) {
		stringStream = std::ostringstream();
		stringStream << fileStream.rdbuf();
		fragSrc = stringStream.str();
	}
	else {
		std::cerr << "Failed to open Fragment Shader file." << std::endl;
	}

	const GLchar* src[1];

	//vertex shader
	src[0] = vertSrc.c_str();

	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, src, nullptr);
	glCompileShader(vertShader);

	// check for shader compile errors
	GLint success = GL_FALSE;
	GLchar elog[512] = { 0 };

	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE) {
		glGetShaderInfoLog(vertShader, 512, nullptr, elog);
		std::cerr << "VERTEX SHADER ERROR:\n" << elog << std::endl;
	}

	// fragment shader
	src[0] = fragSrc.c_str();

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, src, nullptr);
	glCompileShader(fragShader);

	// check for shader compile errors
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE) {
		glGetShaderInfoLog(fragShader, 512, nullptr, elog);
		std::cerr << "VERTEX SHADER ERROR:\n" << elog << std::endl;
	}

	// link shaders
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertShader);
	glAttachShader(shaderID, fragShader);
	glLinkProgram(shaderID);

	// check for linking errors
	glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
	if (success != GL_TRUE) {
		glGetProgramInfoLog(shaderID, 512, nullptr, elog);
		std::cerr << "PROGRAM ERROR:\n" << elog << std::endl;
	}
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

Shader::Shader(const char* sPath, GLenum shaderType) {
	std::string shaderSrc;
	std::ifstream fileStream(sPath, std::ios::in);
	std::ostringstream stringStream;

	if (fileStream) {
		stringStream << fileStream.rdbuf();
		shaderSrc = stringStream.str();
	}
	else {
		std::cerr << "Failed to open Shader file." << std::endl;
	}

	const GLchar* src[1];

	//vertex shader
	src[0] = shaderSrc.c_str();

	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, src, nullptr);
	glCompileShader(shader);

	// check for shader compile errors
	GLint success = GL_FALSE;
	GLchar elog[512] = { 0 };

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE) {
		glGetShaderInfoLog(shader, 512, nullptr, elog);
		std::cerr << "VERTEX SHADER ERROR:\n" << elog << std::endl;
	}

	// link shaders
	shaderID = glCreateProgram();
	glAttachShader(shaderID, shader);
	glLinkProgram(shaderID);

	// check for linking errors
	glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
	if (success != GL_TRUE) {
		glGetProgramInfoLog(shaderID, 512, nullptr, elog);
		std::cerr << "PROGRAM ERROR:\n" << elog << std::endl;
	}
	glDeleteShader(shader);
}

Shader::~Shader() { glDeleteProgram(shaderID); }

void Shader::Use() { glUseProgram(shaderID); }

// Setting floats

void Shader::SetUniform(std::string sName, float* fValues, int iCount)
{
	glUseProgram(shaderID);
	int iLoc = glGetUniformLocation(shaderID, sName.c_str());
	glUniform1fv(iLoc, iCount, fValues);
}

void Shader::SetUniform(std::string sName, const float fValue)
{
	glUseProgram(shaderID);
	int iLoc = glGetUniformLocation(shaderID, sName.c_str());
	glUniform1fv(iLoc, 1, &fValue);
}

// Setting vectors

void Shader::SetUniform(std::string sName, glm::vec2* vVectors, int iCount)
{
	glUseProgram(shaderID);
	int iLoc = glGetUniformLocation(shaderID, sName.c_str());
	glUniform2fv(iLoc, iCount, (GLfloat*)vVectors);
}

void Shader::SetUniform(std::string sName, const glm::vec2 vVector)
{
	glUseProgram(shaderID);
	int iLoc = glGetUniformLocation(shaderID, sName.c_str());
	glUniform2fv(iLoc, 1, (GLfloat*)&vVector);
}

void Shader::SetUniform(std::string sName, glm::vec3* vVectors, int iCount)
{
	glUseProgram(shaderID);
	int iLoc = glGetUniformLocation(shaderID, sName.c_str());
	glUniform3fv(iLoc, iCount, (GLfloat*)vVectors);
}

void Shader::SetUniform(std::string sName, const glm::vec3 vVector)
{
	glUseProgram(shaderID);
	int iLoc = glGetUniformLocation(shaderID, sName.c_str());
	glUniform3fv(iLoc, 1, (GLfloat*)&vVector);
}

void Shader::SetUniform(std::string sName, glm::vec4* vVectors, int iCount)
{
	glUseProgram(shaderID);
	int iLoc = glGetUniformLocation(shaderID, sName.c_str());
	glUniform4fv(iLoc, iCount, (GLfloat*)vVectors);
}

void Shader::SetUniform(std::string sName, const glm::vec4 vVector)
{
	glUseProgram(shaderID);
	int iLoc = glGetUniformLocation(shaderID, sName.c_str());
	glUniform4fv(iLoc, 1, (GLfloat*)&vVector);
}

// Setting 3x3 matrices

void Shader::SetUniform(std::string sName, glm::mat3* mMatrices, int iCount)
{
	glUseProgram(shaderID);
	int iLoc = glGetUniformLocation(shaderID, sName.c_str());
	glUniformMatrix3fv(iLoc, iCount, false, (GLfloat*)mMatrices);
}

void Shader::SetUniform(std::string sName, const glm::mat3 mMatrix)
{
	glUseProgram(shaderID);
	int iLoc = glGetUniformLocation(shaderID, sName.c_str());
	glUniformMatrix3fv(iLoc, 1, false, (GLfloat*)&mMatrix);
}

// Setting 4x4 matrices

void Shader::SetUniform(std::string sName, glm::mat4* mMatrices, int iCount)
{
	glUseProgram(shaderID);
	int iLoc = glGetUniformLocation(shaderID, sName.c_str());
	glUniformMatrix4fv(iLoc, iCount, false, (GLfloat*)mMatrices);
}

void Shader::SetUniform(std::string sName, const glm::mat4 mMatrix)
{
	glUseProgram(shaderID);
	int iLoc = glGetUniformLocation(shaderID, sName.c_str());
	glUniformMatrix4fv(iLoc, 1, false, (GLfloat*)&mMatrix);
}

// Setting integers

void Shader::SetUniform(std::string sName, int* iValues, int iCount)
{
	glUseProgram(shaderID);
	int iLoc = glGetUniformLocation(shaderID, sName.c_str());
	glUniform1iv(iLoc, iCount, iValues);
}

void Shader::SetUniform(std::string sName, const int iValue)
{
	glUseProgram(shaderID);
	int iLoc = glGetUniformLocation(shaderID, sName.c_str());
	glUniform1i(iLoc, iValue);
}

void Shader::SetUniform(std::string sName, unsigned int* iValues, int iCount)
{
	glUseProgram(shaderID);
	int iLoc = glGetUniformLocation(shaderID, sName.c_str());
	glUniform1uiv(iLoc, iCount, iValues);
}

void Shader::SetUniform(std::string sName, const unsigned int iValue)
{
	glUseProgram(shaderID);
	int iLoc = glGetUniformLocation(shaderID, sName.c_str());
	glUniform1ui(iLoc, iValue);
}