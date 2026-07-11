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

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

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
    cubeVAO.PushFloat(3, 3);

    lightVAO.Bind();
    VBO.Bind();
    lightVAO.PushFloat(3, 0);


    Shader cubeColorShader("res/shader/colorVertex.glsl", "res/shader/colorFragment.glsl");
    Shader lightingShader("res/shader/lightingVertex.glsl", "res/shader/lightingFragment.glsl");

    cubeColorShader.use();
    cubeColorShader.setVec3("u_ObjectColor", {1.0f, 0.5f, 0.31f});
    cubeColorShader.setVec3("u_LightColor", {1.0f, 1.0f, 1.0f});

    lightingShader.use();
    lightingShader.setVec3("u_LightColor", {1.0f, 1.0f, 1.0f});

    glm::mat4 view;
    glm::mat4 proj;
    glm::mat4 model;

    const float radius = 10.0f;

    float currentTime, lastTime;
    lastTime = glfwGetTime();

    static float timeAccumulator = 0.0f;
    static int frameCount = 0;

    float clearColor[4] = { 0.105f, 0.105f, 0.105f, 1.0f };

    cubeColorShader.use();
    cubeColorShader.setVec3("u_Material.specular", {0.5f, 0.5f, 0.5f});
    cubeColorShader.setFloat("u_Material.shininess", 32.0f);

    cubeColorShader.setVec3("u_Light.ambient",  {0.2f, 0.2f, 0.2f});
    cubeColorShader.setVec3("u_Light.diffuse",  {0.5f, 0.5f, 0.5f});
    cubeColorShader.setVec3("u_Light.specular", {1.0f, 1.0f, 1.0f}); 

    cubeColorShader.setFloat("u_Light.constant",  1.0f);
    cubeColorShader.setFloat("u_Light.linear",    0.09f);
    cubeColorShader.setFloat("u_Light.quadratic", 0.032f);	    

    Texture2D shinyContainer("res/texture/shinyContainer.png", GL_RGBA, 0);
    cubeColorShader.setInt("u_Material.diffuse", 0);

    Texture2D shinyContainerSpec("res/texture/shinyContainer_specular.png", GL_RGBA, 1);
    cubeColorShader.setInt("u_Material.specular", 1);

    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        Window::processInput(window);

        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cubeColorShader.use();
        // cubeColorShader.setVec3("u_Light.position", lightPos);
        cubeColorShader.setVec3("u_ViewPos", camera.GetPos());

        cubeColorShader.setVec3("u_Light.direction", camera.GetFront());
        cubeColorShader.setVec3("u_Light.position", camera.GetPos());
        cubeColorShader.setFloat("u_Light.cutOff", glm::cos(glm::radians(20.0f)));
        cubeColorShader.setFloat("u_Light.outerCutOff", glm::cos(glm::radians(35.0f)));

        proj = glm::perspective(glm::radians(camera.GetFOV()), (float) WIDTH/ (float) HEIGHT, 0.1f, 250.0f);
        camera.Update(view, deltaTime);

        cubeVAO.Bind();

        cubeColorShader.setMatrix4f("u_View", view);
        cubeColorShader.setMatrix4f("u_Proj", proj);

        shinyContainer.Bind();
        shinyContainerSpec.Bind();

        for (unsigned int i = 0; i < 10; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20 * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            cubeColorShader.setMatrix4f("u_Model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        model = glm::mat4(1.0f);

        lightingShader.use();
        lightVAO.Bind();

        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));

        lightingShader.setMatrix4f("u_Model", model);
        lightingShader.setMatrix4f("u_View", view);
        lightingShader.setMatrix4f("u_Proj", proj);

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
