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
	GLuint texture;
	GLuint rbo;

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
	GLuint texture;
	GLuint rbo;

	VAO vao;
	Shader shader;

	int width;
	int height;
	int scr_width;
	int scr_height;
};

class ImageFramebuffer {
public:
	ImageFramebuffer(GLint width, GLint height, GLint scr_width, GLint scr_height, const char* vertPath, const char* fragPath);
	~ImageFramebuffer();

	void Draw();

	void Bind();
	void UnBind();

private:
	GLuint framebufferTexture;
	VAO vao;
	Shader shader;

	int width;
	int height;
	int scr_width;
	int scr_height;
};

#endif