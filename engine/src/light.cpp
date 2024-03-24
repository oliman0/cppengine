#include "light.hpp"

// Point Light

PointLight::PointLight(glm::vec3 position, glm::vec3 size, glm::vec4 colour, glm::vec3 diffuse, glm::vec3 specular, float intensity) : Mesh(position, size, colour), diffuse(diffuse), specular(specular), intensity(intensity), bias(0.05f), biasMin(0.05f) {
	shadowTransforms.push_back(glm::lookAt(position, position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(glm::lookAt(position, position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(glm::lookAt(position, position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	shadowTransforms.push_back(glm::lookAt(position, position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
	shadowTransforms.push_back(glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
}

PointLight::PointLight(glm::vec3 position, glm::vec3 size, glm::vec4 colour, glm::vec3 diffuse, glm::vec3 specular, float intensity, float bias, float biasMin) : Mesh(position, size, colour), diffuse(diffuse), specular(specular), intensity(intensity), bias(bias), biasMin(biasMin) {
	shadowTransforms.push_back(glm::lookAt(position, position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(glm::lookAt(position, position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(glm::lookAt(position, position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	shadowTransforms.push_back(glm::lookAt(position, position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
	shadowTransforms.push_back(glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
}

void PointLight::SetShaderData(Shader& shader, unsigned int lightNum) {
	shader.SetUniform("pointLights[" + std::to_string(lightNum) + "].position", position);

	shader.SetUniform("pointLights[" + std::to_string(lightNum) + "].diffuse", diffuse);
	shader.SetUniform("pointLights[" + std::to_string(lightNum) + "].specular", specular);

	shader.SetUniform("pointLights[" + std::to_string(lightNum) + "].intensity", intensity);

	shader.SetUniform("pointLights[" + std::to_string(lightNum) + "].bias", bias);
	shader.SetUniform("pointLights[" + std::to_string(lightNum) + "].biasMin", biasMin);
}

void PointLight::SetShaderMeshData(Shader& shader) { Mesh::SetShaderData(shader); }

void PointLight::SetShadowTransforms(Shader& shader) {
	for (int i = 0; i < 6; i++)
		shader.SetUniform("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);

	shader.SetUniform("lightPos", position);
}

// Global Light

GlobalLight::GlobalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : direction(direction), ambient(ambient), diffuse(diffuse), specular(specular) {}

void GlobalLight::SetShaderData(Shader& shader) {
	shader.SetUniform("directionalLight.direction", direction);

	shader.SetUniform("directionalLight.ambient", ambient);
	shader.SetUniform("directionalLight.diffuse", diffuse);
	shader.SetUniform("directionalLight.specular", specular);
}

// Spot Light

SpotLight::SpotLight(glm::vec3 position, glm::vec3 size, glm::vec4 meshColour, glm::vec3 direction, float innerCutOff, float outerCutOff, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float attenuationConstant, float attenuationLinear, float attenuationQuadratic) : Mesh(position, size, meshColour), direction(direction),
																																																	  innerCutOff(glm::cos(glm::radians(innerCutOff))), outerCutOff(glm::cos(glm::radians(outerCutOff))),
																																																	  ambient(ambient), diffuse(diffuse), specular(specular),
																																																	  attenuationConstant(attenuationConstant), attenuationLinear(attenuationLinear), attenuationQuadratic(attenuationQuadratic) {}

void SpotLight::SetDirection(glm::vec3 dir) { direction = dir; }

void SpotLight::SetShaderData(Shader& shader, unsigned int lightNum) {
	shader.SetUniform("spotLights[" + std::to_string(lightNum) + "].position", position);
	shader.SetUniform("spotLights[" + std::to_string(lightNum) + "].direction", direction);
	shader.SetUniform("spotLights[" + std::to_string(lightNum) + "].innerCutOff", innerCutOff);
	shader.SetUniform("spotLights[" + std::to_string(lightNum) + "].outerCutOff", outerCutOff);

	shader.SetUniform("spotLights[" + std::to_string(lightNum) + "].ambient", ambient);
	shader.SetUniform("spotLights[" + std::to_string(lightNum) + "].diffuse", diffuse);
	shader.SetUniform("spotLights[" + std::to_string(lightNum) + "].specular", specular);

	shader.SetUniform("spotLights[" + std::to_string(lightNum) + "].constant", attenuationConstant);
	shader.SetUniform("spotLights[" + std::to_string(lightNum) + "].linear", attenuationLinear);
	shader.SetUniform("spotLights[" + std::to_string(lightNum) + "].quadratic", attenuationQuadratic);
}