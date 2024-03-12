#include "texture.h"

GLuint CreateTexture(const char* path, GLenum textureFormat) {
    GLuint texture_id = 0;
    GLint width = 0, height = 0;

    stbi_set_flip_vertically_on_load(0);

    unsigned char* tex_data = stbi_load(
        path,
        &width, &height,
        nullptr, 0);
    if (!tex_data) {
        std::cerr << "Failed to load texture: " << path << std::endl;
    }

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(tex_data);

    return texture_id;
}

std::tuple<GLuint, float, float> CreateTextureAndSize(const char* path, GLenum textureFormat) {
    GLuint texture_id = 0;
    GLint width = 0, height = 0;

    stbi_set_flip_vertically_on_load(0);

    unsigned char* tex_data = stbi_load(
        path,
        &width, &height,
        nullptr, 0);
    if (!tex_data) {
        std::cerr << "Failed to load texture: " << path << std::endl;
    }

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(tex_data);

    return std::tuple<GLuint, float, float>(texture_id, (float)width, (float)height);
}