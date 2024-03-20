#include "mesh.h"

Mesh::Mesh(glm::vec3 postition, glm::vec3 size, const char* texture) : position(postition),
                                                                        colour(1.0, 1.0, 1.0, 1.0), usingTexture(true), texture(CreateTexture(texture, GL_SRGB_ALPHA)) {
    GLfloat vertices[288] = {
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        size.x, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        size.x, size.y, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        size.x, size.y, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.0f, size.y, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, size.z, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        size.x, 0.0f, size.z, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        size.x, size.y, size.z, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        size.x, size.y, size.z, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, size.y, size.z, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, size.z, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        0.0f, size.y, size.z, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, size.y, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, size.z, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, size.y, size.z, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        size.x, size.y, size.z, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        size.x, size.y, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        size.x, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        size.x, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        size.x, 0.0f, size.z, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        size.x, size.y, size.z, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        size.x, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        size.x, 0.0f, size.z, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        size.x, 0.0f, size.z, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, size.z, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, size.y, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        size.x, size.y, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        size.x, size.y, size.z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        size.x, size.y, size.z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, size.y, size.z, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, size.y, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f };

    int sizes[3] = { 3, 3, 2 };
    vao.Create(vertices, 288, 36, 3, sizes);
}

Mesh::Mesh(glm::vec3 postition, glm::vec3 size, glm::vec4 colour) : position(postition),
                                                                    colour(colour), usingTexture(false), texture(0) {
    GLfloat vertices[288] = {
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        size.x, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        size.x, size.y, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        size.x, size.y, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.0f, size.y, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, size.z, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        size.x, 0.0f, size.z, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        size.x, size.y, size.z, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        size.x, size.y, size.z, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, size.y, size.z, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, size.z, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        0.0f, size.y, size.z, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, size.y, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, size.z, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, size.y, size.z, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        size.x, size.y, size.z, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        size.x, size.y, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        size.x, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        size.x, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        size.x, 0.0f, size.z, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        size.x, size.y, size.z, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        size.x, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        size.x, 0.0f, size.z, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        size.x, 0.0f, size.z, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, size.z, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, size.y, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        size.x, size.y, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        size.x, size.y, size.z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        size.x, size.y, size.z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, size.y, size.z, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, size.y, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f };

    int sizes[3] = { 3, 3, 2 };
    vao.Create(vertices, 288, 36, 3, sizes);
}

void Mesh::Delete() {
    if (usingTexture) {
        glDeleteTextures(1, &texture);
    }

    vao.Delete();
}

void Mesh::Draw(Shader& shader) {
    shader.Use();

    glm::mat4 model(1.0f);
    model = glm::translate(model, position);
    shader.SetUniform("model", &model);

    vao.Bind();

    glDrawArrays(GL_TRIANGLES, 0, vao.NumOfVertices());

    glBindVertexArray(0);

    if (usingTexture) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Mesh::SetShaderData(Shader& shader) {
    shader.SetUniform("colour", &colour);
    shader.SetUniform("usingTexture", usingTexture);

    if (usingTexture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
}

glm::vec3 Mesh::GetPosition() { return position; }
void Mesh::SetPosition(glm::vec3 pos) { position = pos; }