#ifndef UI_H
#define UI_H

#include <vector>
#include <fstream>

#include <GLAD/glad.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "vao.h"
#include "shader.h"
#include "texture.h"

struct FontCharacter {
	FontCharacter(GLuint texID, GLfloat width, GLfloat height);

	void Delete();

	GLuint textureID;
	GLfloat width;
	GLfloat height;
};

class UI {
public:
	UI(const char* fontPath, float scr_width, float scr_height);
	~UI();

	void Draw();
	void DrawString(const char* str, float textSize, glm::vec2 position, glm::vec4 colour, bool usingView);
	void DrawStringBG(const char* str, float textSize, glm::vec2 position, glm::vec4 colour, glm::vec4 bgColour, glm::vec2 padding, GLuint bgTexture, bool usingTexture, bool usingView);

	glm::vec2 StringSize(const char* str, float textSize);
	
	void Update();

	void OpenWindow();
	void CloseWindow();

private:
	void DrawWindow();
	void DrawSprite(GLuint texture, glm::vec2 position, glm::vec2 size, glm::vec4 colour, bool usingTexture, bool usingView);
	void DrawCharacter(FontCharacter& character, float textSize, glm::vec2 position, glm::vec4 colour, bool usingView);

	std::vector<FontCharacter> font;
	std::vector<GLuint> icons;

	//elements
	//windows

	VAO vao;
	IBO ibo;

	glm::mat4 uiProjection;
	Shader uiShader;

	bool cursorFree;
};

#endif