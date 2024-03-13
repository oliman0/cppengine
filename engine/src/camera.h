#ifndef CAMERA_H
#define CAMERA_H

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 position);
	~Camera() {}

	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 position);
	void MovePosition(glm::vec3 position);

	void SetPitchYaw(glm::vec2 vec);
	void AddPitchYaw(glm::vec2 vec);

	glm::vec3 GetFront();
	glm::vec3 GetLookFront();
	glm::vec3 GetUp();

	void Update();

	glm::mat4 View();

private:
	glm::vec3 position;
	glm::vec3 up;
	glm::vec3 front;
	glm::vec3 lookFront;

	float yaw;
	float pitch;
};

#endif