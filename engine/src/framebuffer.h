#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <iostream>

#include <GLAD/glad.h>

#include "vao.h"
#include "shader.h"

class Framebuffer {
public:
	Framebuffer(GLint width, GLint height, GLint scr_width, GLint scr_height);
	Framebuffer(GLint width, GLint height);
	~Framebuffer();

	void Blit();

	void Bind();
	void UnBind();

	int GetWidth();
	int GetHeight();

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
	PostProcessingFramebuffer(GLint width, GLint height, const char* vertPath, const char* fragPath);
	~PostProcessingFramebuffer();

	void Draw();
	void Blit();

	void Bind();
	void UnBind();

	int GetWidth();
	int GetHeight();

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

// TODO: Add other constructor
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
	CubemapFramebuffer(GLint width, GLint height, GLenum bufferFormat, GLenum bufferStorageFormat, GLenum attachmentType);
	~CubemapFramebuffer();

	void Bind();
	void UnBind();

	void BindBufferTexture(GLenum texture);

	int GetWidth();
	int GetHeight();

private:
	GLuint fbo;
	GLuint buffer;

	int width;
	int height;
	int scr_width;
	int scr_height;
};

#endif