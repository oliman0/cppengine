#ifndef MESH_H
#define MESH_H

#include <GLAD/glad.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "shader.hpp"
#include "vao.hpp"
#include "texture.hpp"

class Mesh
{
public:
	Mesh(glm::vec3 postition, glm::vec3 size, const char* texture);
	//Mesh(glm::vec3 postition, glm::vec3 size, const char* texture, float texRepeat);
	Mesh(glm::vec3 postition, glm::vec3 size, glm::vec4 colour);
	~Mesh() {}

	void Delete();

	void Draw(Shader& shader);
	void SetShaderData(Shader& shader);

	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 position);

protected:
	VAO vao;

	glm::vec3 position;

	glm::vec4 colour;
	bool usingTexture;
	GLuint texture;
};

#endif