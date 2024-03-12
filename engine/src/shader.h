#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <GLAD/glad.h>
#include <GLM/glm.hpp>

class Shader {
public:
	Shader(const char* vertPath, const char* fragPath);
	Shader(const char* sPath, GLenum shaderType);
	~Shader();

	void Use();

	// Setting vectors
	void SetUniform(std::string sName, glm::vec2* vVectors, int iCount = 1);
	void SetUniform(std::string sName, const glm::vec2 vVector);
	void SetUniform(std::string sName, glm::vec3* vVectors, int iCount = 1);
	void SetUniform(std::string sName, const glm::vec3 vVector);
	void SetUniform(std::string sName, glm::vec4* vVectors, int iCount = 1);
	void SetUniform(std::string sName, const glm::vec4 vVector);

	// Setting floats
	void SetUniform(std::string sName, float* fValues, int iCount = 1);
	void SetUniform(std::string sName, const float fValue);

	// Setting 3x3 matrices
	void SetUniform(std::string sName, glm::mat3* mMatrices, int iCount = 1);
	void SetUniform(std::string sName, const glm::mat3 mMatrix);

	// Setting 4x4 matrices
	void SetUniform(std::string sName, glm::mat4* mMatrices, int iCount = 1);
	void SetUniform(std::string sName, const glm::mat4 mMatrix);

	// Setting integers
	void SetUniform(std::string sName, int* iValues, int iCount = 1);
	void SetUniform(std::string sName, const int iValue);

private:
	unsigned int shaderID;
};

#endif