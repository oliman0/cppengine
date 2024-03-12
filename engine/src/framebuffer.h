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

	void Draw();

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

class ImageFramebuffer {
public:
	ImageFramebuffer(GLint width, GLint height, GLint scr_width, GLint scr_height);
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