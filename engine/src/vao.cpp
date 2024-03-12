#include "vao.h"

// VAO

VAO::VAO(GLfloat* data, int dataLen, int numOfVertices, int numOfAttribs, int* attribSizes) : vao(0), vbo(0), numOfVertices(numOfVertices) { Create(data, dataLen, numOfVertices, numOfAttribs, attribSizes); }
VAO::VAO() : vao(0), vbo(0), numOfVertices(0) {}
VAO::~VAO() { Delete(); }

void VAO::Create(GLfloat* data, int dataLen, int numOfVertices, int numOfAttribs, int* attribSizes) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
        dataLen * sizeof(GLfloat),
        data,
        GL_STATIC_DRAW);

    int stride = 0, pos = 0;
    for (int i = 0; i < numOfAttribs; i++) { stride += attribSizes[i]; }

    for (int i = 0; i < numOfAttribs; i++) {
        glVertexAttribPointer(i, attribSizes[i], GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (const void*)(pos * sizeof(GLfloat)));
        glEnableVertexAttribArray(i);
        pos += attribSizes[i];
    }

    // note that this is allowed, the call to glVertexAttribPointer registered vbo as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the vao afterwards so other vao calls won't accidentally modify this vao, but this rarely happens. Modifying other
    // vaos requires a call to glBindVertexArray anyways so we generally don't unbind vaos (nor vbos) when it's not directly necessary.
    glBindVertexArray(0);

    this->numOfVertices = numOfVertices;
}

void VAO::Delete() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void VAO::Bind() { glBindVertexArray(vao); }

int VAO::NumOfVertices() { return numOfVertices; }

// IBO

IBO::IBO(GLint* data, int dataLen) : ibo(0), dataLen(dataLen) { Create(data, dataLen); }
IBO::IBO() : ibo(0), dataLen(0) {}
IBO::~IBO() { Delete(); }

void IBO::Create(GLint* data, int dataLen) {
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        dataLen * sizeof(GLint),
        data,
        GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    this->dataLen = dataLen;
}

void IBO::Delete() { glDeleteBuffers(1, &ibo); }

void IBO::Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); }

int IBO::Len() { return dataLen; }