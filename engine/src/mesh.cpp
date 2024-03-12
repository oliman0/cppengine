#include "mesh.h"

Mesh::Mesh(glm::vec3 postition, glm::vec3 size, const char* texture) : position(postition),
                                                                        colour(1.0, 1.0, 1.0, 1.0), usingTexture(true), texture(CreateTexture(texture)) {
    GLfloat vertices[180] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    size.x, 0.0f, 0.0f, 1.0f, 0.0f,
    size.x, size.y, 0.0f, 1.0f, 1.0f,
    size.x, size.y, 0.0f, 1.0f, 1.0f,
    0.0f, size.y, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

    0.0f, 0.0f, size.z, 0.0f, 0.0f,
    size.x, 0.0f, size.z, 1.0f, 0.0f,
    size.x, size.y, size.z, 1.0f, 1.0f,
    size.x, size.y, size.z, 1.0f, 1.0f,
    0.0f, size.y, size.z, 0.0f, 1.0f,
    0.0f, 0.0f, size.z, 0.0f, 0.0f,

    0.0f, size.y, size.z, 1.0f, 0.0f,
    0.0f, size.y, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, size.z, 0.0f, 0.0f,
    0.0f, size.y, size.z, 1.0f, 0.0f,

    size.x, size.y, size.z, 1.0f, 0.0f,
    size.x, size.y, 0.0f, 1.0f, 1.0f,
    size.x, 0.0f, 0.0f, 0.0f, 1.0f,
    size.x, 0.0f, 0.0f, 0.0f, 1.0f,
    size.x, 0.0f, size.z, 0.0f, 0.0f,
    size.x, size.y, size.z, 1.0f, 0.0f,

    0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    size.x, 0.0f, 0.0f, 1.0f, 1.0f,
    size.x, 0.0f, size.z, 1.0f, 0.0f,
    size.x, 0.0f, size.z, 1.0f, 0.0f,
    0.0f, 0.0f, size.z, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

    0.0f, size.y, 0.0f, 0.0f, 1.0f,
    size.x, size.y, 0.0f, 1.0f, 1.0f,
    size.x, size.y, size.z, 1.0f, 0.0f,
    size.x, size.y, size.z, 1.0f, 0.0f,
    0.0f, size.y, size.z, 0.0f, 0.0f,
    0.0f, size.y, 0.0f, 0.0f, 1.0f };

    int sizes[2] = { 3, 2 };
    vao.Create(vertices, 180, 36, 2, sizes);
}

Mesh::Mesh(glm::vec3 postition, glm::vec3 size, glm::vec4 colour) : position(postition),
                                                                    colour(colour), usingTexture(false), texture(0) {
    GLfloat vertices[180] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    size.x, 0.0f, 0.0f, 1.0f, 0.0f,
    size.x, size.y, 0.0f, 1.0f, 1.0f,
    size.x, size.y, 0.0f, 1.0f, 1.0f,
    0.0f, size.y, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

    0.0f, 0.0f, size.z, 0.0f, 0.0f,
    size.x, 0.0f, size.z, 1.0f, 0.0f,
    size.x, size.y, size.z, 1.0f, 1.0f,
    size.x, size.y, size.z, 1.0f, 1.0f,
    0.0f, size.y, size.z, 0.0f, 1.0f,
    0.0f, 0.0f, size.z, 0.0f, 0.0f,

    0.0f, size.y, size.z, 1.0f, 0.0f,
    0.0f, size.y, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, size.z, 0.0f, 0.0f,
    0.0f, size.y, size.z, 1.0f, 0.0f,

    size.x, size.y, size.z, 1.0f, 0.0f,
    size.x, size.y, 0.0f, 1.0f, 1.0f,
    size.x, 0.0f, 0.0f, 0.0f, 1.0f,
    size.x, 0.0f, 0.0f, 0.0f, 1.0f,
    size.x, 0.0f, size.z, 0.0f, 0.0f,
    size.x, size.y, size.z, 1.0f, 0.0f,

    0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    size.x, 0.0f, 0.0f, 1.0f, 1.0f,
    size.x, 0.0f, size.z, 1.0f, 0.0f,
    size.x, 0.0f, size.z, 1.0f, 0.0f,
    0.0f, 0.0f, size.z, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

    0.0f, size.y, 0.0f, 0.0f, 1.0f,
    size.x, size.y, 0.0f, 1.0f, 1.0f,
    size.x, size.y, size.z, 1.0f, 0.0f,
    size.x, size.y, size.z, 1.0f, 0.0f,
    0.0f, size.y, size.z, 0.0f, 0.0f,
    0.0f, size.y, 0.0f, 0.0f, 1.0f };

    int sizes[2] = { 3, 2 };
    vao.Create(vertices, 180, 36, 2, sizes);
}

Mesh::~Mesh() {
    if (usingTexture) {
        glDeleteTextures(1, &texture);
    }
}

void Mesh::Draw(Shader& shader) {
    shader.Use();

    glm::mat4 model(1.0f);
    model = glm::translate(model, position);
    shader.SetUniform("model", &model);
    shader.SetUniform("colour", &colour);
    shader.SetUniform("usingTexture", usingTexture);

    vao.Bind();

    if (usingTexture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    glDrawArrays(GL_TRIANGLES, 0, vao.NumOfVertices());

    glBindVertexArray(0);

    if (usingTexture) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}