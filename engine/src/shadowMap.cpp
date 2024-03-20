#include "shadowMap.h"

ShadowCubemap::ShadowCubemap(GLint width, GLint height, float near, float far) : CubemapFramebuffer(width, height, width, height, GL_DEPTH_COMPONENT, GL_FLOAT, GL_DEPTH_ATTACHMENT),
																				 shadowProjection(glm::perspective(glm::radians(90.0f), (float)width / (float)height, near, far)), farPlane(far),
																				 depthShader("shaders/depthCubemap.vert", "shaders/depthCubemap.frag", "shaders/depthCubemap.geom") {}

void ShadowCubemap::SetDepthShaderData() {
	depthShader.SetUniform("shadowProjection", shadowProjection);
	depthShader.SetUniform("far_plane", farPlane);
}

Shader& ShadowCubemap::GetDepthShader() { return depthShader; }



ShadowMap::ShadowMap(GLint width, GLint height) : TextureFramebuffer(width, height, width, height, GL_DEPTH_COMPONENT, GL_FLOAT, GL_DEPTH_ATTACHMENT) {
	//TODO: constructor
}