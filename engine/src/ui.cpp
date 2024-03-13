#include "ui.h"

FontCharacter::FontCharacter(GLuint texID, GLfloat width, GLfloat height) : textureID(texID), width(width), height(height) {}
void FontCharacter::Delete() { glDeleteTextures(1, &textureID); }

//// Sprite
//
//Sprite::Sprite(GLuint texture) : texture(texture), colour(1.0), usingTexture(true) {}
//Sprite::Sprite(glm::vec4 colour) : texture(0), colour(colour), usingTexture(false) {}
//
//// Text
//
//Text::Text(const char* str, float textSize, glm::vec4 colour) : str(str), textSize(textSize), colour(colour), padding(0.0), bgColour(0.0), bgTexture(0), usingTexture(false) {}
//Text::Text(const char* str, float textSize, glm::vec4 colour, glm::vec4 bgColour, glm::vec2 padding) : str(str), textSize(textSize), colour(colour), padding(padding), bgColour(bgColour), bgTexture(0), usingTexture(false) {}
//Text::Text(const char* str, float textSize, glm::vec4 colour, GLuint texture, glm::vec2 padding) : str(str), textSize(textSize), colour(colour), padding(padding), bgColour(0.0), bgTexture(texture), usingTexture(true) {}

// UI System

UI::UI(const char* fontPath, float scr_width, float scr_height) : uiShader("shaders/ui_shader.vert", "shaders/ui_shader.frag"), uiProjection(glm::ortho(0.0f, scr_width, 0.0f, scr_height, -1.0f, 1.0f)), cursorFree(true) {
	for (int i = 0; i < 128; i++) {
        if (!std::fstream(std::string(fontPath) + "/" + std::to_string(i) + ".png").good()) {
            font.push_back(FontCharacter(0, 0, 0));
            continue;
        }

        std::tuple<GLuint, float, float> data = CreateTextureAndSize((std::string(fontPath) + "/" + std::to_string(i) + ".png").c_str());
		font.push_back(FontCharacter(get<0>(data), get<1>(data), get<2>(data)));
	}

    GLint indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    GLfloat vertices[20] = {
        0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f
    };

    int sizes[2] = { 2, 2 };
    vao.Create(vertices, 20, 4, 2, sizes);

    ibo.Create(indices, 6);

    uiShader.SetUniform("projection", uiProjection);
    uiShader.SetUniform("view", glm::mat4(1.0f));
}

UI::~UI() {
    for (int i = 0; i < font.size(); i++) {
        font[i].Delete();
    }
    
    for (int i = 0; i < icons.size(); i++) {
        glDeleteTextures(1, &icons[i]);
    }

    vao.Delete();
    ibo.Delete();
}

void UI::Draw() {

}

void UI::DrawString(const char* str, float textSize, glm::vec2 position, glm::vec4 colour, bool usingView) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == 32) {
            position.x += 3.0f * textSize;
        }
        else {
            DrawCharacter(font[str[i]], textSize, position, colour, usingView);
            position.x += (font[str[i]].width * textSize) + textSize;
        }
    }
}

void UI::DrawStringBG(const char* str, float textSize, glm::vec2 position, glm::vec4 colour, glm::vec4 bgColour, glm::vec2 padding, GLuint bgTexture, bool usingTexture, bool usingView) {
    glm::vec2 str_size = StringSize(str, textSize);

    DrawSprite(bgTexture, glm::vec2(position.x - padding.x, position.y - padding.y),
        glm::vec2(str_size.x + (padding.x * 2.0), str_size.y + (3.0 * textSize) + (padding.y * 2.0)),
        bgColour, usingTexture, usingView);

    DrawString(str, textSize, position, colour, usingView);
}

glm::vec2 UI::StringSize(const char* str, float textSize) {
    glm::vec2 size(0.0);

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == 32) {
            size.x += 3.0f * textSize;
        }
        else {
            if (font[str[i]].height > size.y) size.y = font[str[i]].height;
            size.x += (font[str[i]].width * textSize) + textSize;
        }
    }

    size.x -= textSize;

    return size;
}

void UI::Update() {}

void UI::OpenWindow() {}
void UI::CloseWindow() {}

void UI::DrawWindow() {}

void UI::DrawSprite(GLuint texture, glm::vec2 position, glm::vec2 size, glm::vec4 colour, bool usingTexture, bool usingView) {
    uiShader.Use();

    glDisable(GL_DEPTH_TEST);

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size.x, size.y, 1.0));
    uiShader.SetUniform("model", &model);
    uiShader.SetUniform("colour", &colour);
    uiShader.SetUniform("usingTexture", usingTexture);
    uiShader.SetUniform("addColour", false);
    uiShader.SetUniform("useView", usingView);

    vao.Bind();

    if (usingTexture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    ibo.Bind();
    glDrawElements(GL_TRIANGLES, ibo.Len(), GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    if (usingTexture) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glEnable(GL_DEPTH_TEST);
}

void UI::DrawCharacter(FontCharacter& character, float textSize, glm::vec2 position, glm::vec4 colour, bool usingView) {
    uiShader.Use();

    glDisable(GL_DEPTH_TEST);

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(character.width * textSize, character.height * textSize, 1.0));
    uiShader.SetUniform("model", &model);
    uiShader.SetUniform("colour", &colour);
    uiShader.SetUniform("usingTexture", true);
    uiShader.SetUniform("addColour", true);
    uiShader.SetUniform("useView", usingView);

    vao.Bind();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, character.textureID);

    ibo.Bind();
    glDrawElements(GL_TRIANGLES, ibo.Len(), GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

    glEnable(GL_DEPTH_TEST);
}