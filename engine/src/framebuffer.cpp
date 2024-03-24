#include "framebuffer.h"

// GL FRAMEBUFFER OBJECT

Framebuffer::Framebuffer(GLint width, GLint height, GLint scr_width, GLint scr_height) : width(width), height(height), scr_width(scr_width), scr_height(scr_height) {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenRenderbuffers(1, &colourBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, colourBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB, scr_width, scr_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colourBuffer);

    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, scr_width, scr_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "framebuffer failed" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Framebuffer::Framebuffer(GLint width, GLint height) : Framebuffer(width, height, width, height) {}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &fbo);
    glDeleteRenderbuffers(1, &depthBuffer);
    glDeleteRenderbuffers(1, &colourBuffer);
}

void Framebuffer::Blit() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, width, height, 0, 0, scr_width, scr_height, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
}

void Framebuffer::Bind() {
    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Framebuffer::UnBind() {
    glViewport(0, 0, scr_width, scr_height);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int Framebuffer::GetWidth() { return width; }
int Framebuffer::GetHeight() { return height; }

// POST PROCESSING FRAMEBUFFER

PostProcessingFramebuffer::PostProcessingFramebuffer(GLint width, GLint height, GLint scr_width, GLint scr_height, const char* vertPath, const char* fragPath) : width(width), height(height), scr_width(scr_width), scr_height(scr_height), shader(vertPath, fragPath) {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &colourBuffer);
    glBindTexture(GL_TEXTURE_2D, colourBuffer);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, scr_width, scr_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colourBuffer, 0);

    glGenTextures(1, &depthBuffer);
    glBindTexture(GL_TEXTURE_2D, depthBuffer);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, scr_width, scr_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "framebuffer failed" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    GLfloat vertices[] = {
        -1.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,

            -1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f
    };

    int sizes[2] = { 2, 2 };
    vao = VAO(vertices, 24, 6, 2, sizes);
}

PostProcessingFramebuffer::PostProcessingFramebuffer(GLint width, GLint height, const char* vertPath, const char* fragPath) : PostProcessingFramebuffer(width, height, width, height, vertPath, fragPath) {}

PostProcessingFramebuffer::~PostProcessingFramebuffer() {
    glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &depthBuffer);
    glDeleteTextures(1, &colourBuffer);
}

void PostProcessingFramebuffer::Blit() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, width, height, 0, 0, scr_width, scr_height, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
}

void PostProcessingFramebuffer::Draw() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.Use();
    vao.Bind();
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, colourBuffer);
    glDrawArrays(GL_TRIANGLES, 0, vao.NumOfVertices());

    glEnable(GL_DEPTH_TEST);
}

void PostProcessingFramebuffer::Bind() {
    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void PostProcessingFramebuffer::UnBind() {
    glViewport(0, 0, scr_width, scr_height);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int PostProcessingFramebuffer::GetWidth() { return width; }
int PostProcessingFramebuffer::GetHeight() { return height; }

// TEXTURE FRAMEBUFFER

TextureFramebuffer::TextureFramebuffer(GLint width, GLint height, GLint scr_width, GLint scr_height, GLenum bufferFormat, GLenum bufferStorageFormat, GLenum attachmentType) : width(width), height(height), scr_width(scr_width), scr_height(scr_height) {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &buffer);
    glBindTexture(GL_TEXTURE_2D, buffer);

    glTexImage2D(GL_TEXTURE_2D, 0, bufferFormat, scr_width, scr_height, 0, bufferFormat, bufferStorageFormat, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, buffer, 0);
}

TextureFramebuffer::~TextureFramebuffer() {
    glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &buffer);
}

void TextureFramebuffer::Bind() {
    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void TextureFramebuffer::UnBind() {
    glViewport(0, 0, scr_width, scr_height);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void TextureFramebuffer::BindBufferTexture(GLenum texture) {
    glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_2D, buffer);
}

// CUBEMAP FRAMEBUFFER

CubemapFramebuffer::CubemapFramebuffer(GLint width, GLint height, GLint scr_width, GLint scr_height, GLenum bufferFormat, GLenum bufferStorageFormat, GLenum attachmentType) : width(width), height(height), scr_width(scr_width), scr_height(scr_height) {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &buffer);
    glBindTexture(GL_TEXTURE_CUBE_MAP, buffer);

    for (unsigned int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, bufferFormat,
            scr_width, scr_width, 0, bufferFormat, bufferStorageFormat, nullptr);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    glFramebufferTexture(GL_FRAMEBUFFER, attachmentType, buffer, 0);

    // TODO: need to add a better way of managing attachemnts that
    //       you may or may not want.
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "cubemap framebuffer failed" << std::endl;
    }
}

CubemapFramebuffer::CubemapFramebuffer(GLint width, GLint height, GLenum bufferFormat, GLenum bufferStorageFormat, GLenum attachmentType) : CubemapFramebuffer(width, height, width, height, bufferFormat, bufferStorageFormat, attachmentType) {}

CubemapFramebuffer::~CubemapFramebuffer() {
    glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &buffer);
}

void CubemapFramebuffer::Bind() {
    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void CubemapFramebuffer::UnBind() {
    glViewport(0, 0, scr_width, scr_height);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CubemapFramebuffer::BindBufferTexture(GLenum texture) {
    glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, buffer);
}

int CubemapFramebuffer::GetWidth() { return width; }
int CubemapFramebuffer::GetHeight() { return height; }