#include "camera.h"

Camera::Camera(glm::vec3 position) : position(position), up(0.0f, 1.0f, 0.0f), front(0.0f, 0.0f, -1.0f), look_front(0.0f, 0.0f, -1.0f), yaw(0.0f), pitch(0.0f) {}

glm::vec3 Camera::GetPosition() { return position; }
void Camera::SetPosition(glm::vec3 pos) { position = pos; }
void Camera::MovePosition(glm::vec3 pos) { position += pos; }

void Camera::SetPitchYaw(glm::vec2 vec) {
    yaw = vec.x;
    pitch = vec.y;

    if (pitch > 89.0f) { pitch = 89.0f; }
    if (pitch < -89.0f) { pitch = -89.0f; }
}

void Camera::AddPitchYaw(glm::vec2 vec) {
    yaw += vec.x;
    pitch += vec.y;

    if (pitch > 89.0f) { pitch = 89.0f; }
    if (pitch < -89.0f) { pitch = -89.0f; }
}

glm::vec3 Camera::GetFront() { return front; }
glm::vec3 Camera::GetUp() { return up; }

void Camera::Update() {
    glm::vec3 direction(0.0);

    direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    direction.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    front = glm::normalize(direction);

    direction.y = glm::sin(glm::radians(pitch));
    look_front = glm::normalize(direction);
}

glm::mat4 Camera::View() {
    return glm::lookAt(
        position,
        position + look_front,
        up
    );
}