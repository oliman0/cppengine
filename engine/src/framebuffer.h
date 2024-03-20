#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <iostream>

#include <GLAD/glad.h>

#include "vao.h"
#include "shader.h"

class Framebuffer {
public:
	Framebuffer(GLint width, GLint height, GLint scr_width, GLint scr_height);
	~Framebuffer();

	void Blit();

	void Bind();
	void UnBind();

private:
	GLuint fbo;
	GLuint colourBuffer;
	GLuint depthBuffer;

	int width;
	int height;
	int scr_width;
	int scr_height;
};

class PostProcessingFramebuffer {
public:
	PostProcessingFramebuffer(GLint width, GLint height, GLint scr_width, GLint scr_height, const char* vertPath, const char* fragPath);
	~PostProcessingFramebuffer();

	void Draw();
	void Blit();

	void Bind();
	void UnBind();

private:
	GLuint fbo;
	GLuint colourBuffer;
	GLuint depthBuffer;

	VAO vao;
	Shader shader;

	int width;
	int height;
	int scr_width;
	int scr_height;
};

class TextureFramebuffer {
public:
	TextureFramebuffer(GLint width, GLint height, GLint scr_width, GLint scr_height, GLenum bufferFormat, GLenum bufferStorageFormat, GLenum attachmentType);
	~TextureFramebuffer();

	void Bind();
	void UnBind();

	void BindBufferTexture(GLenum texture);

private:
	GLuint fbo;
	GLuint buffer;

	int width;
	int height;
	int scr_width;
	int scr_height;
};

class CubemapFramebuffer {
public:
	CubemapFramebuffer(GLint width, GLint height, GLint scr_width, GLint scr_height, GLenum bufferFormat, GLenum bufferStorageFormat, GLenum attachmentType);
	~CubemapFramebuffer();

	void Bind();
	void UnBind();

	void BindBufferTexture(GLenum texture);

private:
	GLuint fbo;
	GLuint buffer;

	int width;
	int height;
	int scr_width;
	int scr_height;
};

#endif