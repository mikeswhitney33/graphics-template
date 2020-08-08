#include "camera.hpp"


//     Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
Camera::Camera(const glm::vec3 & position, const glm::vec3 & up, float yaw, float pitch)
:Front(glm::vec3(0, 0, -1)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM), Position(position), WorldUp(up),Yaw(yaw), Pitch(pitch)
{
    updateCameraVectors();
}
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
:Camera(glm::vec3(posX, posY, posZ), glm::vec3(upX, upY, upZ), yaw, pitch)
{}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(Position, Position + Front, Up);
}
void Camera::move(CameraMovement direction, float delta_time)
{
    float vel = MovementSpeed * delta_time;
    switch(direction)
    {
        case FORWARD:
            Position += Front * vel;
            break;
        case BACKWARD:
            Position -= Front * vel;
            break;
        case LEFT:
            Position -= Right * vel;
            break;
        case RIGHT:
            Position += Right * vel;
            break;
    }
}
void Camera::rotate(float xoffset, float yoffset, bool constrain_pitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;
    Yaw += xoffset;
    Pitch += yoffset;
    if(constrain_pitch)
    {
        if(Pitch > 89.0f) Pitch = 89.0f;
        if(Pitch < -89.0f) Pitch = -89.0f;
    }
    updateCameraVectors();
}
void Camera::zoom(float yoffset)
{
    Zoom -= yoffset;
    if(Zoom < 1.0f) Zoom = 1.0f;
    if(Zoom > 45.0f) Zoom = 45.0f;
}
void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = glm::cos(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
    front.y = glm::sin(glm::radians(Pitch));
    front.z = glm::sin(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}