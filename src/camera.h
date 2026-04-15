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
        bool firstMouse = true;
        float yaw = -90.0f;
        float pitch = 0.0f;
        float FOV = 0.0f;
        float deltaTime;
        float camSpeed;
        float camSensitivity;

        double lastX;
        double lastY;

        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
        glm::vec3 cameraRight;
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
