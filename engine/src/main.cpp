#define STB_IMAGE_IMPLEMENTATION

#include "window.h"
#include "framebuffer.h"
#include "mesh.h"
#include "shader.h"
#include "camera.h"
#include "ui.h"

int main()
{
	Window window("OpenGL", 1920, 1080, 10.0);
	window.SetCursorLocked(true);
	Framebuffer framebuffer(1920, 1080, 1920, 1080);

	UI ui("./res/fonts/wave-standard", 1920.0f, 1080.0f);

	Shader shader("shaders/shader.vert", "shaders/shader.frag");
	shader.SetUniform("projection", glm::perspective(glm::radians(110.0f), 1920.0f / 1080.0f, 0.1f, 150.0f));

	Camera camera(glm::vec3(0.0f, 1.0f, 0.0f));
		
	Mesh mesh(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(5.0f, 5.0f, 5.0f), "./res/textures/largecheck.png");

	while (!window.ShouldClose()) {
		framebuffer.Bind();
		shader.SetUniform("view", camera.View());

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 movement(0.0f, 0.0f, 0.0f);

        if (window.KeyHold(GLFW_KEY_W)) {
            movement += camera.GetFront();
        }
        if (window.KeyHold(GLFW_KEY_S)) {
			movement -= camera.GetFront();
        }
        if (window.KeyHold(GLFW_KEY_A)) {
            movement -= glm::normalize(glm::cross(camera.GetFront(), camera.GetUp()));
        }
        if (window.KeyHold(GLFW_KEY_D)) {
            movement += glm::normalize(glm::cross(camera.GetFront(), camera.GetUp()));
        }

		if (window.KeyHold(GLFW_KEY_SPACE)) {
			movement += camera.GetUp();
		}
		if (window.KeyHold(GLFW_KEY_LEFT_CONTROL)) {
			movement -= camera.GetUp();
		}

        camera.MovePosition(movement * 10.0f * window.GetDeltaTime());

        camera.AddPitchYaw(window.GetMouseOffset());
        camera.Update();

		mesh.Draw(shader);

		framebuffer.Draw();
		framebuffer.UnBind();

		ui.DrawString(("Fps: " + std::to_string(window.GetFps())).c_str(), 3.0f, glm::vec2(10.0f, 1030.0f), glm::vec4(1.0f), false);
		ui.DrawString(("Z: " + std::to_string(camera.GetPosition().z)).c_str(), 3.0f, glm::vec2(10.0f, 10.0f), glm::vec4(1.0f), false);
		ui.DrawString(("Y: " + std::to_string(camera.GetPosition().y)).c_str(), 3.0f, glm::vec2(10.0f, 46.0f), glm::vec4(1.0f), false);
		ui.DrawString(("X: " + std::to_string(camera.GetPosition().x)).c_str(), 3.0f, glm::vec2(10.0f, 82.0f), glm::vec4(1.0f), false);
		ui.Draw();

		window.SwapBuffers();
		window.PollEvents();
	}
}