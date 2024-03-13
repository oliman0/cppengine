#include "light.h"

Light::Light(glm::vec3 position, glm::vec3 size, glm::vec4 colour, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float attenuationConstant, float attenuationLinear, float attenuationQuadratic) : Mesh(position, size, colour), ambient(ambient), diffuse(diffuse), specular(specular),
																																																			   attenuationConstant(attenuationConstant), attenuationLinear(attenuationLinear), attenuationQuadratic(attenuationQuadratic) {}

void Light::SetShaderData(Shader& shader, unsigned int lightNum) {
	shader.SetUniform("pointLights[" + std::to_string(lightNum) + "].position", position);
	shader.SetUniform("pointLights[" + std::to_string(lightNum) + "].ambient", ambient);
	shader.SetUniform("pointLights[" + std::to_string(lightNum) + "].diffuse", diffuse);
	shader.SetUniform("pointLights[" + std::to_string(lightNum) + "].specular", specular);

	shader.SetUniform("pointLights[" + std::to_string(lightNum) + "].constant", attenuationConstant);
	shader.SetUniform("pointLights[" + std::to_string(lightNum) + "].linear", attenuationLinear);
	shader.SetUniform("pointLights[" + std::to_string(lightNum) + "].quadratic", attenuationQuadratic);
}