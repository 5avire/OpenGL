#include "camera.h"
#include <glm/geometric.hpp>

Camera::Camera()
    : cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)),
    cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
    cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    cameraRight(glm::vec3(1.0f, 0.0f, 0.0f)),
    camSpeed(2.5f),
    camSensitivity(0.1f),
    firstMouse(true),
    yaw(-90.0f),
    pitch(0.0f),
    FOV(55.0f)
{
}

Camera::~Camera()
{
}

void Camera::Move(Movement movement)
{
    float movementSpeed = camSpeed * deltaTime;
    if (movement == FORWARD)
        cameraPos += cameraFront * movementSpeed;
    if (movement == BACKWARD)
        cameraPos -= cameraFront * movementSpeed;
    if (movement == LEFT)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * movementSpeed;
    if (movement == RIGHT)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * movementSpeed;
    if (movement == UP)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraRight)) * movementSpeed;
    if (movement == DOWN)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraRight)) * movementSpeed;
}

void Camera::Update(glm::mat4& view, float deltaValue)
{
    deltaTime = deltaValue;
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::MouseMovement(double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    float xoffset = xPos - lastX;
    float yoffset = yPos - lastY;
    lastX = xPos; lastY = yPos;

    xoffset *= camSensitivity;
    yoffset *= camSensitivity;

    yaw += xoffset;
    pitch -= yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    SetFront(direction);
}

void Camera::Zoom(double offset)
{
    FOV -= (float)offset;
    if (FOV > 55.0f)
        FOV = 55.0f;
    if (FOV < 1.0f)
        FOV = 1.0f;
}

void Camera::SetFront(glm::vec3 direction)
{
    cameraFront = glm::normalize(direction);
}

void Camera::ChangeCamSpeedBy(float x)
{
    camSpeed += x;

    if (camSpeed > 50.0f)
        camSpeed = 50.0f;
    if (camSpeed < 0.5f)
        camSpeed = 0.5f;
}

float Camera::GetFOV() const
{
    return FOV;
}
