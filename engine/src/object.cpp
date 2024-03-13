#include "object.h"

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess, GLuint diffuseTexture, GLuint specularTexture) : diffuseTexture(diffuseTexture), specularTexture(specularTexture), shininess(shininess), ambient(ambient), diffuse(diffuse), specular(specular) {}

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) : diffuseTexture(0), specularTexture(0), shininess(shininess), ambient(ambient), diffuse(diffuse), specular(specular) {}

Object::Object(glm::vec3 postition, glm::vec3 size, const char* texture, Material material) : Mesh(postition, size, texture), material(material) {}

Object::Object(glm::vec3 postition, glm::vec3 size, glm::vec4 colour, Material material) : Mesh(postition, size, colour), material(material) {}

void Object::Draw(Shader& shader) {
	shader.SetUniform("material.shininess", material.shininess);
	shader.SetUniform("material.diffuseT", material.diffuseTexture);
	shader.SetUniform("material.specularT", material.specularTexture);

	shader.SetUniform("material.ambient", material.ambient);
	shader.SetUniform("material.diffuse", material.diffuse);
	shader.SetUniform("material.specular", material.specular);

	Mesh::Draw(shader);
}