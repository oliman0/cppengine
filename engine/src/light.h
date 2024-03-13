#ifndef LIGHT_H
#define LIGHT_H

#include "mesh.h"

class Light : public Mesh
{
public:
	Light(glm::vec3 position, glm::vec3 size, glm::vec4 colour, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float attenuationConstant, float attenuationLinear, float attenuationQuadratic);
	~Light() {}

	void SetShaderData(Shader& shader, unsigned int lightNum);

private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float attenuationConstant;
	float attenuationLinear;
	float attenuationQuadratic;
};

#endif