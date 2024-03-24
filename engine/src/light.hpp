#ifndef LIGHT_H
#define LIGHT_H

#include <vector>

#include "mesh.hpp"
#include "object.hpp"

class PointLight : public Mesh {
public:
	PointLight(glm::vec3 position, glm::vec3 size, glm::vec4 meshColour, glm::vec3 diffuse, glm::vec3 specular, float intensity);
	PointLight(glm::vec3 position, glm::vec3 size, glm::vec4 meshColour, glm::vec3 diffuse, glm::vec3 specular, float intensity, float bias, float biasMin);
	~PointLight() {}

	void SetShaderData(Shader& shader, unsigned int lightNum);
	void SetShaderMeshData(Shader& shader);

	void SetShadowTransforms(Shader& shader);

private:
	glm::vec3 diffuse;
	glm::vec3 specular;

	float intensity;

	float bias;
	float biasMin;

	std::vector<glm::mat4> shadowTransforms;
};

class GlobalLight {
public:
	GlobalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	~GlobalLight() {}

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