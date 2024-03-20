#ifndef SHADOWMAP_H
#define SHADOWMAP_H

#include <vector>

#include <GLM/gtc/matrix_transform.hpp>

#include "framebuffer.h"

class ShadowCubemap : public CubemapFramebuffer
{
public:
	ShadowCubemap(GLint width, GLint height, float near, float far);
	~ShadowCubemap() {}

	void SetDepthShaderData();
	Shader& GetDepthShader();

private:
	Shader depthShader;

	glm::mat4 shadowProjection;
	float farPlane;
};

class ShadowMap : public TextureFramebuffer {
public:
	ShadowMap(GLint width, GLint height);
	~ShadowMap() {}
	// TODO: impl
};

#endif