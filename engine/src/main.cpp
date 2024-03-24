#define STB_IMAGE_IMPLEMENTATION

#include <vector>

#include "window.h"
#include "framebuffer.h"
#include "object.h"
#include "lightsys.h"
#include "shader.h"
#include "camera.h"
#include "ui.h"

int main()
{
	bool fullBright = false;
	bool spotLightOn = false;

	Window window("OpenGL", 1920, 1080, 10.0);
	window.SetCursorLocked(true);
	Framebuffer framebuffer(1920, 1080, 1920, 1080);

	UI ui("./res/fonts/wave-standard", 1920.0f, 1080.0f);

	Shader shader("shaders/shader.vert", "shaders/shader.frag");
	Shader lightShader("shaders/light_cube.vert", "shaders/light_cube.frag");
	shader.SetUniform("projection", glm::perspective(glm::radians(110.0f), 1920.0f / 1080.0f, 0.1f, 150.0f));
	lightShader.SetUniform("projection", glm::perspective(glm::radians(110.0f), 1920.0f / 1080.0f, 0.1f, 150.0f));

	Camera camera(glm::vec3(0.0f, 1.0f, 0.0f));

	Material floorMat(glm::vec3(1.0f), glm::vec3(1.0f), 64.0f);
	Material wallMat(glm::vec3(1.0f), glm::vec3(0.0f), 64.0f);
		
	std::vector<Object> objects;
	
	objects.push_back(Object(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 0.1f), "./res/textures/largecheck.png", wallMat));
	objects.push_back(Object(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 0.1f), "./res/textures/largecheck.png", wallMat));
	objects.push_back(Object(glm::vec3(20.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 0.1f), "./res/textures/largecheck.png", wallMat));
	objects.push_back(Object(glm::vec3(30.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 0.1f), "./res/textures/largecheck.png", wallMat));

	objects.push_back(Object(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(10.0f, 10.0f, 0.1f), "./res/textures/largecheck.png", wallMat));
	objects.push_back(Object(glm::vec3(10.0f, 0.0f, 10.0f), glm::vec3(10.0f, 10.0f, 0.1f), "./res/textures/largecheck.png", wallMat));
	objects.push_back(Object(glm::vec3(20.0f, 0.0f, 10.0f), glm::vec3(10.0f, 10.0f, 0.1f), "./res/textures/largecheck.png", wallMat));
	objects.push_back(Object(glm::vec3(30.0f, 0.0f, 10.0f), glm::vec3(10.0f, 10.0f, 0.1f), "./res/textures/largecheck.png", wallMat));

	objects.push_back(Object(glm::vec3(-50.0f, 0.0f, -50.0f), glm::vec3(100.0f, 0.1f, 100.0f), "./res/textures/checkfloor.png", floorMat));

	LightManager lightManager(1024, 1024);

	SpotLight spotLight(glm::vec3(20.0f, 50.0f, 5.0f), glm::vec3(1.0f), glm::vec4(1.0f), glm::vec3(0.0, 1.0f, 0.0f), 27.0f, 30.0f, glm::vec3(0.01f), glm::vec3(1.0f), glm::vec3(1.0f), 1.0f, 0.045f, 0.0075f);
	
	lightManager.AddPointLight(PointLight(glm::vec3(20.0f, 7.5f, 5.0f), glm::vec3(1.0f), glm::vec4(1.0f), glm::vec3(0.5f), glm::vec3(1.0f), 50.0f));
	lightManager.AddPointLight(PointLight(glm::vec3(0.0f, 7.5f, -40.0f), glm::vec3(1.0f), glm::vec4(1.0f), glm::vec3(0.5f), glm::vec3(1.0f), 50.0f));

	while (!window.ShouldClose()) {
		shader.SetUniform("view", camera.View());
		lightShader.SetUniform("view", camera.View());
		shader.SetUniform("viewPos", camera.GetPosition());

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

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

		if (window.KeyDown(GLFW_KEY_B)) {
			fullBright = !fullBright;
			shader.SetUniform("fullBright", fullBright);
		}

		if (window.KeyDown(GLFW_KEY_Q)) spotLightOn = !spotLightOn;

        camera.MovePosition(movement * 10.0f * window.GetDeltaTime());

        camera.AddPitchYaw(window.GetMouseOffset());
        camera.Update();

		// RENDER
		//

		lightManager.RenderShadowMaps(objects);
		lightManager.BindShadowMaps(shader);

		framebuffer.Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightManager.DrawPointLights(shader, lightShader);

		if (spotLightOn) {
			spotLight.SetPosition(camera.GetPosition() - camera.GetFront());
			spotLight.SetDirection(camera.GetLookFront());

			spotLight.SetShaderData(shader, 0);
			shader.SetUniform("numOfSpotLights", 1);
		}

		for (int i = 0; i < objects.size(); i++) {
			objects[i].SetShaderData(shader);
			objects[i].Draw(shader);
		}

		framebuffer.Blit();
		framebuffer.UnBind();

		ui.DrawString(("Fps: " + std::to_string(window.GetFps())).c_str(), 3.0f, glm::vec2(10.0f, 1030.0f), glm::vec4(1.0f), false);
		ui.DrawString(("Z: " + std::to_string(camera.GetPosition().z)).c_str(), 3.0f, glm::vec2(10.0f, 10.0f), glm::vec4(1.0f), false);
		ui.DrawString(("Y: " + std::to_string(camera.GetPosition().y)).c_str(), 3.0f, glm::vec2(10.0f, 46.0f), glm::vec4(1.0f), false);
		ui.DrawString(("X: " + std::to_string(camera.GetPosition().x)).c_str(), 3.0f, glm::vec2(10.0f, 82.0f), glm::vec4(1.0f), false);
		ui.Draw();

		window.SwapBuffers();
		window.PollEvents();
	}

	for (int i = 0; i < objects.size(); i++) {
		objects[i].Delete();
	}
}