#ifndef LIGHT_H
#define LIGHT_H

#include "mesh.h"

class PointLight : public Mesh {
public:
	PointLight(glm::vec3 position, glm::vec3 size, glm::vec4 meshColour, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float attenuationConstant, float attenuationLinear, float attenuationQuadratic);
	~PointLight() {}

	void SetShaderData(Shader& shader, unsigned int lightNum);

private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float attenuationConstant;
	float attenuationLinear;
	float attenuationQuadratic;
};

class DirectionalLight {
public:
	DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	~DirectionalLight() {}

	void SetShaderData(Shader& shader);

private:
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class SpotLight : public Mesh {
public:
	SpotLight(glm::vec3 position, glm::vec3 size, glm::vec4 meshColour, glm::vec3 direction, float innerCutOff, float outerCutOff, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float attenuationConstant, float attenuationLinear, float attenuationQuadratic);
	~SpotLight() {}

	void SetShaderData(Shader& shader, unsigned int lightNum);

	void SetDirection(glm::vec3 direction);

private:
	glm::vec3 direction;
	float innerCutOff;
	float outerCutOff;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float attenuationConstant;
	float attenuationLinear;
	float attenuationQuadratic;
};

#endif