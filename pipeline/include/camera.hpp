#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum CameraMovement {
    FORWARD, BACKWARD, LEFT, RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    Camera(const glm::vec3 & position=glm::vec3(0.0, 0.0, 0.0), const glm::vec3 & up=glm::vec3(0, 1, 0), float yaw=YAW, float pitch=PITCH);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    glm::mat4 getViewMatrix() const;
    void move(CameraMovement direction, float delta_time);
    void rotate(float xoffset, float yoffset, bool constrain_pitch=true);
    void zoom(float yoffset);
private:
    void updateCameraVectors();
};

#endif // CAMERA_HPP