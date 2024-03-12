#ifndef TEXTURE_H
#define TEXTURE_H

#include <tuple>
#include <iostream>

#include <GLAD/glad.h>

#include "stbi.h"

GLuint CreateTexture(const char* path, GLenum textureFormat = GL_RGBA);

std::tuple<GLuint, float, float> CreateTextureAndSize(const char* path, GLenum textureFormat = GL_RGBA);

#endif