#include "camera.h"

Camera::Camera()
    : m_CameraPos(glm::vec3(0.0f, 0.0f, 3.0f)),
    m_CameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
    m_CameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    m_CameraRight(glm::vec3(1.0f, 0.0f, 0.0f)),
    m_CamSpeed(1.0f),
    m_CamSensitivity(0.1f),
    m_FirstMouse(true),
    m_Yaw(-90.0f),
    m_Pitch(0.0f),
    m_FOV(55.0f)
{
}

Camera::~Camera()
{
}

void Camera::Move(Movement movement)
{
    float movementSpeed = m_CamSpeed * m_DeltaTime;
    if (movement == FORWARD)
        m_CameraPos += m_CameraFront * movementSpeed;
    if (movement == BACKWARD)
        m_CameraPos -= m_CameraFront * movementSpeed;
    if (movement == LEFT)
        m_CameraPos -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * movementSpeed;
    if (movement == RIGHT)
        m_CameraPos += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * movementSpeed;
    if (movement == UP)
        m_CameraPos -= glm::normalize(glm::cross(m_CameraFront, m_CameraRight)) * movementSpeed;
    if (movement == DOWN)
        m_CameraPos += glm::normalize(glm::cross(m_CameraFront, m_CameraRight)) * movementSpeed;
}

void Camera::Update(glm::mat4& view, float deltaValue)
{
    m_DeltaTime = deltaValue;
    view = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
}

void Camera::MouseMovement(double xPos, double yPos)
{
    if (m_FirstMouse)
    {
        m_LastX = xPos;
        m_LastY = yPos;
        m_FirstMouse = false;
    }

    float xoffset = xPos - m_LastX;
    float yoffset = yPos - m_LastY;
    m_LastX = xPos; m_LastY = yPos;

    xoffset *= m_CamSensitivity;
    yoffset *= m_CamSensitivity;

    m_Yaw += xoffset;
    m_Pitch -= yoffset;

    if (m_Pitch > 89.0f)
        m_Pitch = 89.0f;
    if (m_Pitch < -89.0f)
        m_Pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    direction.y = sin(glm::radians(m_Pitch));
    direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    SetFront(direction);
}

void Camera::Zoom(double offset)
{
    m_FOV -= (float)offset;
    if (m_FOV > 55.0f)
        m_FOV = 55.0f;
    if (m_FOV < 1.0f)
        m_FOV = 1.0f;
}

void Camera::SetFront(glm::vec3 direction)
{
    m_CameraFront = glm::normalize(direction);
}

void Camera::ChangeCamSpeedBy(float x)
{
    m_CamSpeed += x;

    if (m_CamSpeed > 50.0f)
        m_CamSpeed = 50.0f;
    if (m_CamSpeed < 0.5f)
        m_CamSpeed = 0.5f;
}

float Camera::GetFOV() const
{
    return m_FOV;
}
