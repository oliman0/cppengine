#include "framebuffer.h"

// GL FRAMEBUFFER OBJECT

Framebuffer::Framebuffer(GLint width, GLint height, GLint scr_width, GLint scr_height) : width(width), height(height), scr_width(scr_width), scr_height(scr_height) {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, scr_width, scr_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, scr_width, scr_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "framebuffer failed" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &fbo);
    glDeleteRenderbuffers(1, &rbo);
    glDeleteTextures(1, &texture);
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

// POST PROCESSING FRAMEBUFFER

PostProcessingFramebuffer::PostProcessingFramebuffer(GLint width, GLint height, GLint scr_width, GLint scr_height, const char* vertPath, const char* fragPath) : width(width), height(height), scr_width(scr_width), scr_height(scr_height), shader(vertPath, fragPath) {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, scr_width, scr_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, scr_width, scr_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

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

PostProcessingFramebuffer::~PostProcessingFramebuffer() {
    glDeleteFramebuffers(1, &fbo);
    glDeleteRenderbuffers(1, &rbo);
    glDeleteTextures(1, &texture);
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
    glBindTexture(GL_TEXTURE_2D, texture);
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

// IMAGE TEXTURE FRAMEBUFFER

ImageFramebuffer::ImageFramebuffer(GLint width, GLint height, GLint scr_width, GLint scr_height, const char* vertPath, const char* fragPath) : width(width), height(height), scr_width(scr_width), scr_height(scr_height), shader(vertPath, fragPath) {
    glGenTextures(1, &framebufferTexture);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA,
        GL_FLOAT, nullptr);

    glBindTexture(GL_TEXTURE_2D, 0);

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

ImageFramebuffer::~ImageFramebuffer() {
    glDeleteTextures(1, &framebufferTexture);
}

void ImageFramebuffer::Draw() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.Use();
    vao.Bind();
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glDrawArrays(GL_TRIANGLES, 0, vao.NumOfVertices());

    glEnable(GL_DEPTH_TEST);
}

void ImageFramebuffer::Bind() {
    glViewport(0, 0, width, height);
    glBindImageTexture(0, framebufferTexture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F);
}

void ImageFramebuffer::UnBind() {
    glViewport(0, 0, scr_width, scr_height);
    glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F);
}