#ifndef LIGHTSYS_H
#define LIGHTSYS_H

#include "shader.h"
#include "light.h"
#include "framebuffer.h"

class LightManager {
public:
	LightManager(GLint depthMapWidth, GLint depthMapHeight);
	~LightManager();

	void RenderShadowMaps(std::vector<Object>& objects);

	void BindShadowMaps(Shader& shader);

	void AddPointLight(PointLight light);

	void DrawPointLights(Shader& shader, Shader& lightShader);

private:
	std::vector<PointLight> pointLights;
	std::vector<SpotLight> spotLights;
	GlobalLight globalLight;

	float farPlane;

	CubemapFramebuffer pointLightShadowMap;
	Shader cubemapDepthShader;
	glm::mat4 pointLightShadowProjection;

	//ShadowMap directionalShadowMap;
};

#endif