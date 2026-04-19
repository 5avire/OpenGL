#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "shader.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "texture2D.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <camera.h>

Camera camera;

const int WIDTH = 1080;
const int HEIGHT = 720;

float deltaTime = 0.0f;

glm::vec3 lightPos(1.2f, 1.0f,  2.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.Move(FORWARD);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.Move(BACKWARD);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.Move(LEFT);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.Move(RIGHT);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.Move(UP);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.Move(DOWN);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_5))
        camera.ChangeCamSpeedBy(0.01f);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_4))
        camera.ChangeCamSpeedBy(-0.01f);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    camera.MouseMovement(xPos, yPos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.Zoom(yoffset);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL.com", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize glad" << std::endl;
        return -1;
    }
    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetScrollCallback(window, scroll_callback);

    // std::vector<Vertex> vertices = {
    //     {-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
    //     { 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
    //     { 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f},
    //     {-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f}
    // };
    
    std::vector<Vertex> vertices = {
        {-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
        { 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
        { 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
        { 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
        {-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
        {-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
        {-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
        { 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
        { 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
        { 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
        {-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
        {-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
        {-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
        {-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
        {-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
        {-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
        {-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
        {-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
        { 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
        { 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
        { 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
        { 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
        { 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
        { 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
        {-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
        { 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
        { 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
        { 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
        {-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
        {-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
        {-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
        { 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
        { 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
        { 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
        {-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
        {-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f}
    };

    VertexArray cubeVAO;
    cubeVAO.Bind();

    VertexBuffer VBO(vertices);
    VBO.Bind();

    // IndexBuffer ib(indices);
    // ib.Bind();

    VertexArray lightVAO;
    lightVAO.Bind();

    cubeVAO.Bind();
    cubeVAO.PushFloat(3, 0);
    cubeVAO.PushFloat(4, 1);
    cubeVAO.PushFloat(2, 2);

    lightVAO.Bind();
    VBO.Bind();
    lightVAO.PushFloat(3, 0);

    // Texture2D awesomeFace("res/texture/awesomeface.png", GL_RGBA, 0);
    // Texture2D container("res/texture/container.jpg", GL_RGB, 1);

    Shader cubeColorShader("res/shader/colorVertex.glsl", "res/shader/colorFragment.glsl");
    Shader lightingShader("res/shader/lightingVertex.glsl", "res/shader/lightingFragment.glsl");

    cubeColorShader.use();
    cubeColorShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    cubeColorShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

    // shader.setInt("texture1", 0);
    // shader.setInt("texture2", 1);

    glm::mat4 view;
    glm::mat4 proj;
    glm::mat4 model;

    const float radius = 10.0f;

    float currentTime, lastTime;
    lastTime = glfwGetTime();

    static float timeAccumulator = 0.0f;
    static int frameCount = 0;

    float clearColor[4] = { 0.105f, 0.105f, 0.105f, 1.0f };

    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        processInput(window);

        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cubeColorShader.use();

        proj = glm::perspective(glm::radians(camera.GetFOV()), (float) WIDTH/ (float) HEIGHT, 0.1f, 250.0f);
        camera.Update(view, deltaTime);

        cubeVAO.Bind();

        model = glm::mat4(1.0f);
        glm::mat4 mvp = proj * view * model;
        cubeColorShader.setMatrix4f("u_MVP", mvp);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        lightingShader.use();

        lightVAO.Bind();

        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));

        mvp = proj * view * model;
        lightingShader.setMatrix4f("u_MVP", mvp);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        timeAccumulator += deltaTime;
        frameCount++;

        if (timeAccumulator > 3)
        {
            float fps = frameCount / timeAccumulator;
            std::cout << "FPS: " << fps << std::endl;

            timeAccumulator = 0;
            frameCount = 0;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
