#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "shader.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "texture2D.h"
#include "windowing.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <camera.h>

Camera camera;

const int WIDTH = 1080;
const int HEIGHT = 720;

float deltaTime = 0.0f;

glm::vec3 lightPos(1.2f, 1.0f,  2.0f);


int main()
{
    GLFWwindow* window = Window::Init(WIDTH, HEIGHT, "LearnOpenGL");
    
    std::array<Vertex, 36> vertices = {{
        // X      Y      Z      R     G     B     A    Tex-X Tex-Y   ----Normals----
        {-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,},
        { 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,},
        { 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,},
        { 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,},
        {-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  0.0f, -1.0f,},
        {-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,},
                                                                  
        {-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  0.0f,  1.0f},
        { 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  0.0f,  1.0f},
        { 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f},
        { 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f},
        {-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  0.0f,  1.0f},
        {-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  0.0f,  1.0f},
                                                                  
        {-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f, 0.0f},
        {-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,  0.0f, 0.0f},
        {-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f,  0.0f, 0.0f},
        {-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f,  0.0f, 0.0f},
        {-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f, 0.0f},
        {-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f, 0.0f},
                                                                  
        { 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f},
        { 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f},
        { 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  0.0f,  0.0f},
        { 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  0.0f,  0.0f},
        { 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f},
        { 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f},
                                                                  
        {-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f},
        { 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f},
        { 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f},
        { 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f},
        {-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f},
        {-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f},
                                                                  
        {-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f},
        { 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f},
        { 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f},
        { 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f},
        {-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f},
        {-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f}
    }};

    VertexArray cubeVAO;
    cubeVAO.Bind();

    VertexBuffer VBO(vertices.data(), sizeof(vertices));
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

        Window::processInput(window);

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
