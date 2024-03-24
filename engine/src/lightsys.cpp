#include "lightsys.hpp"

LightManager::LightManager(GLint shadowMapWidth, GLint shadowMapHeight) : globalLight(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f)), farPlane(100),
																															pointLightShadowMap(shadowMapWidth, shadowMapHeight, GL_DEPTH_COMPONENT, GL_FLOAT, GL_DEPTH_ATTACHMENT),
																															pointLightShadowProjection(glm::perspective(glm::radians(90.0f), (float)shadowMapWidth / (float)shadowMapHeight, 1.0f, 100.0f)),
																															cubemapDepthShader("shaders/depthCubemap.vert", "shaders/depthCubemap.frag", "shaders/depthCubemap.geom")
																															/*, directionalShadowMap(1024, 1024),*/ {}

LightManager::~LightManager() {
	for (int i = 0; i < pointLights.size(); i++) {
		pointLights[i].Delete();
	}
}

void LightManager::RenderShadowMaps(std::vector<Object>& objects) {
	glClear(GL_DEPTH_BUFFER_BIT);
	pointLightShadowMap.Bind();

	cubemapDepthShader.SetUniform("shadowProjection", pointLightShadowProjection);
	cubemapDepthShader.SetUniform("far_plane", farPlane);

	// THIS SHOULD NOT STAY AS 1
	for (int i = 0; i < 1; i++) {
		pointLights[i].SetShadowTransforms(cubemapDepthShader);

		for (int i = 0; i < objects.size(); i++) {
			objects[i].Draw(cubemapDepthShader);
		}
	}

	pointLightShadowMap.UnBind();
}

void LightManager::BindShadowMaps(Shader& shader) {
	shader.SetUniform("pointDepthMap", 2);
	shader.SetUniform("farPlane", farPlane);

	pointLightShadowMap.BindBufferTexture(GL_TEXTURE2);
}

void LightManager::AddPointLight(PointLight light) { pointLights.push_back(light); }

void LightManager::DrawPointLights(Shader& shader, Shader& lightShader) {
	for (int i = 0; i < pointLights.size(); i++) {
		pointLights[i].SetShaderData(shader, i);
		pointLights[i].SetShaderMeshData(lightShader);
		pointLights[i].Draw(lightShader);
	}
	shader.SetUniform("numOfPointLights", (int)pointLights.size());
}