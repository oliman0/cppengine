#ifndef OBJECT_H
#define OBJECT_H

#include "mesh.h"

struct Material {
	Material(glm::vec3 diffuse, glm::vec3 specular, float shininess, GLuint diffuseTexture, GLuint specularTexture);
	Material(glm::vec3 diffuse, glm::vec3 specular, float shininess);

	GLuint diffuseTexture;
	GLuint specularTexture;

	glm::vec3 diffuse;
	glm::vec3 specular;

	float shininess;
};

class Object : public Mesh {
public:
	Object(glm::vec3 postition, glm::vec3 size, const char* texture, Material material);
	Object(glm::vec3 postition, glm::vec3 size, glm::vec4 colour, Material material);
	~Object() {}

	void SetShaderData(Shader& shader);

private:
	Material material;
};

#endif