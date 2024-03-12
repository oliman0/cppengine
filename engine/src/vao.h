#ifndef VAO_H
#define VAO_H

#include <GLAD/glad.h>

class VAO {
public:
	VAO();
	VAO(GLfloat* data, int dataLen, int numOfVertices, int numOfAttribs, int* attribSizes);
	~VAO();

	void Create(GLfloat* data, int dataLen, int numOfVertices, int numOfAttribs, int* attribSizes);
	void Delete();

	void Bind();

	int NumOfVertices();

private:
	GLuint vao;
	GLuint vbo;

	int numOfVertices;
};

class IBO {
public:
	IBO();
	IBO(GLint* data, int dataLen);
	~IBO();

	void Create(GLint* data, int dataLen);
	void Delete();

	void Bind();

	int Len();

private:
	GLuint ibo;

	int dataLen;
};

#endif