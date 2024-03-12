#ifndef MESH_H
#define MESH_H

#include <GLAD/glad.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "shader.h"
#include "vao.h"
#include "texture.h"

class Mesh
{
public:
	Mesh(glm::vec3 postition, glm::vec3 size, const char* texture);
	Mesh(glm::vec3 postition, glm::vec3 size, glm::vec4 colour);
	~Mesh();

	void Draw(Shader& shader);

private:
	VAO vao;

	glm::vec3 position;

	glm::vec4 colour;
	bool usingTexture;
	GLuint texture;
};

#endif