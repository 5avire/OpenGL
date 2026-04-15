#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
    private:
        bool m_FirstMouse = true;
        float m_Yaw = -90.0f;
        float m_Pitch = 0.0f;
        float m_FOV = 0.0f;
        float m_DeltaTime;
        float m_CamSpeed;
        float m_CamSensitivity;

        double m_LastX;
        double m_LastY;

        glm::vec3 m_CameraPos;
        glm::vec3 m_CameraFront;
        glm::vec3 m_CameraUp;
        glm::vec3 m_CameraRight;
    public:
        Camera();
        ~Camera();

        void Update(glm::mat4& view, float deltaTime);
        void Move(Movement movement);
        void MouseMovement(double xPos, double yPos);
        void Zoom(double offset);
        void SetFront(glm::vec3 direction);
        void ChangeCamSpeedBy(float x);

        float GetFOV() const;
};
