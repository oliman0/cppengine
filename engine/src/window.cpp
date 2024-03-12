#include "window.h"

Window::Window(const char* title, GLint width, GLint height, float sensitivity) : windowSize(glm::vec2(width, height)), countFrames(0), cursorLocked(false), deltaTime(0.0f), fps(0), lastFrameTime(0.0f), lastTime(0.0f), mouseOffset(glm::vec2(0.0f, 0.0f)), mousePosition(glm::vec2(0.0f, 0.0f)), scrollWheelOffsetX(0.0f), scrollWheelOffsetY(0.0f), sensitivity(sensitivity) {
    for (int i = 0; i < 1024; i++) { keys[i] = false; }
    for (int i = 0; i < 12; i++) { mouseButtons[i] = false; }
    for (int i = 0; i < 1024; i++) { holdKeys[i] = false; }
    for (int i = 0; i < 12; i++) { holdMouseButtons[i] = false; }

    // glfw: initialize and configure
    // ------------------------------
    if (glfwInit() == 0) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        glfwTerminate();
    }
    //Setup GLFW window properties
    //OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core profile = No backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
    // Set Window non-resizable
    glfwWindowHint(GLFW_RESIZABLE, 0);

    // glfw window creation
    // --------------------
    glfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);

    GLint w, h = (0, 0);
    glfwGetFramebufferSize(glfwWindow, &w, &h);
    frameSize = glm::vec2(w, h);

    glfwMakeContextCurrent(glfwWindow);

    // gl: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }

    glfwSetKeyCallback(glfwWindow, key_callback);
    glfwSetMouseButtonCallback(glfwWindow, mouse_button_callback);
    glfwSetScrollCallback(glfwWindow, scroll_wheel_callback);

    glfwSetWindowUserPointer(glfwWindow, this);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSwapInterval(1);

    //if glfwRawMouseMotionSupported() == 1 { glfwSetInputMode(glfwwindow, RAW_MOUSE_MOTION, 1); (&mut *(glfwGetWindowUserPointer(glfwwindow) as *mut Window)).sensitivity *= 0.3 }
}

Window::~Window() { glfwTerminate(); }

bool Window::ShouldClose() { return glfwWindowShouldClose(glfwWindow); }

bool Window::GetCursorLocked() { return cursorLocked; }
void Window::SetCursorLocked(bool locked) {
    if (locked) {
        glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwSetCursorPos(glfwWindow, (double)(windowSize.x / 2.0f), (double)(windowSize.y / 2.0f)); 
    }
    else { glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL); } cursorLocked = locked;
}

float Window::GetDeltaTime() { return deltaTime; }
int Window::GetFps() { return fps; }

bool Window::KeyHold(int key) { return holdKeys[key]; }
bool Window::KeyDown(int key) { return keys[key]; }
bool Window::MouseButtonHold(int button) { return holdMouseButtons[button]; }
bool Window::MouseButtonDown(int button) { return mouseButtons[button]; }

glm::vec2 Window::GetMousePositionRaw() { return mousePosition; }
glm::vec2 Window::GetMousePosition() { return glm::vec2(mousePosition.x - (windowSize.x - frameSize.x), (windowSize.y - mousePosition.y) - (windowSize.y - frameSize.y)); }
glm::vec2 Window::GetMouseOffset() { return mouseOffset; }
float Window::GetScrollWheelOffsetX() { return scrollWheelOffsetX; }
float Window::GetScrollWheelOffsetY() { return scrollWheelOffsetY; }

glm::vec2 Window::GetWindowSize() { return windowSize; }
//glm::vec2 Window::GetViewportSize() { return viewportSize; }

void Window::SwapBuffers() {
    glfwSwapBuffers(glfwWindow);

    countFrames++;

    if ((float)glfwGetTime() - lastFrameTime >= 1.0f) {
        fps = countFrames;
        lastFrameTime = (float)glfwGetTime();
        countFrames = 0;
    }
}

void Window::PollEvents() {
    deltaTime = (float)glfwGetTime() - lastTime;
    lastTime = (float)glfwGetTime();

    mouseOffset = glm::vec2(0.0f);
    for (int i = 0; i < 1024; i++) { keys[i] = false; }
    for (int i = 0; i < 12; i++) { mouseButtons[i] = false; }
    scrollWheelOffsetX = 0.0f;
    scrollWheelOffsetY = 0.0f;

    glfwPollEvents();

    double xpos = 0.0f, ypos = 0.0f;
    glfwGetCursorPos(glfwWindow, &xpos, &ypos);

    mouseOffset = glm::vec2((float)xpos - (windowSize.x / 2.0f), (windowSize.y / 2.0f) - (float)ypos);
    mouseOffset *= sensitivity * deltaTime;

    mousePosition = glm::vec2((float)xpos, (float)ypos);

    if (cursorLocked) glfwSetCursorPos(glfwWindow, (double)(windowSize.x / 2.0f), (double)(windowSize.y / 2.0f));
}

void Window::key_callback(GLFWwindow* win, GLint key, GLint code, GLint action, GLint mode) {
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(win, 1);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS) {
            window->keys[key] = true;
            window->holdKeys[key] = true;
        }
        else if (action == GLFW_RELEASE) {
            window->holdKeys[key] = false;
        }
    }
}

void Window::mouse_button_callback(GLFWwindow* win, GLint button, GLint action, GLint mods) {
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));

    if (button >= 0 && button < 12)
    {
        if (action == GLFW_PRESS)
        {
            window->mouseButtons[button] = true;
            window->holdMouseButtons[button] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            window->holdMouseButtons[button] = false;
        }
    }
}

void Window::scroll_wheel_callback(GLFWwindow* win, double xoff, double yoff) {
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));

    window->scrollWheelOffsetX = (float)xoff;
    window->scrollWheelOffsetY = (float)yoff;
}