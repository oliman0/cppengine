#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "shell32.lib")

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

class Window {
public:
	Window(const char* title, GLint width, GLint height, float sensitivity);
	~Window();

	void SwapBuffers();
	void PollEvents();
	
	bool ShouldClose();

	bool GetCursorLocked();
	void SetCursorLocked(bool locked);
	
	float GetDeltaTime();
	int GetFps();

	bool KeyHold(int key);
	bool KeyDown(int key);
	bool MouseButtonHold(int button);
	bool MouseButtonDown(int button);

	glm::vec2 GetMousePositionRaw();
	glm::vec2 GetMousePosition();
	glm::vec2 GetMouseOffset();
	float GetScrollWheelOffsetX();
	float GetScrollWheelOffsetY();

	glm::vec2 GetWindowSize();
	//glm::vec2 GetViewportSize();

private:
	GLFWwindow* glfwWindow;

	float lastTime;
	float deltaTime;

	int countFrames;
	float lastFrameTime;
	int fps;

	bool cursorLocked;
	bool keys[1024];
	bool holdKeys[1024];
	bool mouseButtons[12];
	bool holdMouseButtons[12];
	glm::vec2 mousePosition;
	glm::vec2 mouseOffset;
	float scrollWheelOffsetX;
	float scrollWheelOffsetY;
	float sensitivity;

	glm::vec2 windowSize;
	glm::vec2 frameSize;
	//glm::vec2 viewportSize;

	static void key_callback(GLFWwindow* win, GLint key, GLint code, GLint action, GLint mode);
	static void mouse_button_callback(GLFWwindow* win, GLint button, GLint action, GLint mods);
	static void scroll_wheel_callback(GLFWwindow* win, double xoff, double yoff);
};

#endif