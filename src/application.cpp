#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "global.h"

#include "shader.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "texture2D.h"
#include "windowing.h"
#include "mesh.h"
#include "model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <camera.h>

Camera camera;

float deltaTime = 0.0f;

int main()
{
    GLFWwindow* window = Window::Init(WIDTH, HEIGHT, "LearnOpenGL");
    stbi_set_flip_vertically_on_load(true);
    
    Shader cubeColorShader("res/shader/colorVertex.glsl", "res/shader/colorFragment.glsl");
    Shader lightingShader("res/shader/lightingVertex.glsl", "res/shader/lightingFragment.glsl");

    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };  

    Model backpack("res/models/backpack/backpack.obj");

    cubeColorShader.use();
    cubeColorShader.setVec3("u_LightColor", {1.0f, 1.0f, 1.0f});

    lightingShader.use();
    lightingShader.setVec3("u_LightColor", {1.0f, 1.0f, 1.0f});

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    const float radius = 10.0f;

    float currentTime, lastTime;
    lastTime = glfwGetTime();

    static float timeAccumulator = 0.0f;
    static int frameCount = 0;

    float clearColor[4] = { 0.105f, 0.105f, 0.105f, 1.0f };

    cubeColorShader.use();
    cubeColorShader.setFloat("u_Material.shininess", 32.0f);

    // cubeColorShader.setVec3("u_Light.ambient",  {0.2f, 0.2f, 0.2f});
    // cubeColorShader.setVec3("u_Light.diffuse",  {0.5f, 0.5f, 0.5f});
    // cubeColorShader.setVec3("u_Light.specular", {1.0f, 1.0f, 1.0f}); 

    // cubeColorShader.setFloat("u_Light.constant",  1.0f);
    // cubeColorShader.setFloat("u_Light.linear",    0.09f);
    // cubeColorShader.setFloat("u_Light.quadratic", 0.032f);	    

    cubeColorShader.setFloat("u_PointLight[0].constant", 1.0f);

    // Texture2D shinyContainer("res/texture/shinyContainer.png", GL_RGBA, 0);
    // cubeColorShader.setInt("u_Material.diffuse", 0);
    //
    // Texture2D shinyContainerSpec("res/texture/shinyContainer_specular.png", GL_RGBA, 1);
    // cubeColorShader.setInt("u_Material.specular", 1);

    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        Window::processInput(window);

        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cubeColorShader.use();

        // directional light
        cubeColorShader.setVec3("u_DirLight.direction", {-0.2f, -1.0f, -0.3f});
        cubeColorShader.setVec3("u_DirLight.ambient", {0.05f, 0.05f, 0.05f});
        cubeColorShader.setVec3("u_DirLight.diffuse", {0.4f, 0.4f, 0.4f});
        cubeColorShader.setVec3("u_DirLight.specular", {0.5f, 0.5f, 0.5f});

        // point light 1
        cubeColorShader.setVec3("u_PointLight[0].position", pointLightPositions[0]);
        cubeColorShader.setVec3("u_PointLight[0].ambient", {0.05f, 0.05f, 0.05f});
        cubeColorShader.setVec3("u_PointLight[0].diffuse", {0.8f, 0.8f, 0.8f});
        cubeColorShader.setVec3("u_PointLight[0].specular", {1.0f, 1.0f, 1.0f});
        cubeColorShader.setFloat("u_PointLight[0].constant", 0.5f);
        cubeColorShader.setFloat("u_PointLight[0].linear", 0.09f);
        cubeColorShader.setFloat("u_PointLight[0].quadratic", 0.032f);

        // point light 2
        cubeColorShader.setVec3("u_PointLight[1].position", pointLightPositions[1]);
        cubeColorShader.setVec3("u_PointLight[1].ambient", {0.05f, 0.05f, 0.05f});
        cubeColorShader.setVec3("u_PointLight[1].diffuse", {0.8f, 0.8f, 0.8f});
        cubeColorShader.setVec3("u_PointLight[1].specular", {1.0f, 1.0f, 1.0f});
        cubeColorShader.setFloat("u_PointLight[1].constant", 0.5f);
        cubeColorShader.setFloat("u_PointLight[1].linear", 0.09f);
        cubeColorShader.setFloat("u_PointLight[1].quadratic", 0.032f);

        // point light 3
        cubeColorShader.setVec3("u_PointLight[2].position", pointLightPositions[2]);
        cubeColorShader.setVec3("u_PointLight[2].ambient", {0.05f, 0.05f, 0.05f});
        cubeColorShader.setVec3("u_PointLight[2].diffuse", {0.8f, 0.8f, 0.8f});
        cubeColorShader.setVec3("u_PointLight[2].specular", {1.0f, 1.0f, 1.0f});
        cubeColorShader.setFloat("u_PointLight[2].constant", 0.5f);
        cubeColorShader.setFloat("u_PointLight[2].linear", 0.09f);
        cubeColorShader.setFloat("u_PointLight[2].quadratic", 0.032f);

        // point light 4
        cubeColorShader.setVec3("u_PointLight[3].position", pointLightPositions[3]);
        cubeColorShader.setVec3("u_PointLight[3].ambient", {0.05f, 0.05f, 0.05f});
        cubeColorShader.setVec3("u_PointLight[3].diffuse", {0.8f, 0.8f, 0.8f});
        cubeColorShader.setVec3("u_PointLight[3].specular", {1.0f, 1.0f, 1.0f});
        cubeColorShader.setFloat("u_PointLight[3].constant", 0.5f);
        cubeColorShader.setFloat("u_PointLight[3].linear", 0.09f);
        cubeColorShader.setFloat("u_PointLight[3].quadratic", 0.032f);

        // spotLight
        cubeColorShader.setVec3("u_SpotLight.position", camera.GetPos());
        cubeColorShader.setVec3("u_SpotLight.direction", camera.GetFront());
        cubeColorShader.setVec3("u_SpotLight.ambient", {0.0f, 0.0f, 0.0f});
        cubeColorShader.setVec3("u_SpotLight.diffuse", {1.0f, 1.0f, 1.0f});
        cubeColorShader.setVec3("u_SpotLight.specular", {0.5f, 0.5f, 0.5f});
        cubeColorShader.setFloat("u_SpotLight.constant", 0.5f);
        cubeColorShader.setFloat("u_SpotLight.linear", 0.09f);
        cubeColorShader.setFloat("u_SpotLight.quadratic", 0.032f);
        cubeColorShader.setFloat("u_SpotLight.innerCutOff", glm::cos(glm::radians(12.5f)));
        cubeColorShader.setFloat("u_SpotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        proj = glm::perspective(glm::radians(camera.GetFOV()), (float) WIDTH/ (float) HEIGHT, 0.1f, 250.0f);
        camera.Update(view, deltaTime);

        model = glm::mat4(1.0f);

        cubeColorShader.setMatrix4f("u_View", view);
        cubeColorShader.setMatrix4f("u_Proj", proj);
        cubeColorShader.setMatrix4f("u_Model", model);
        
        backpack.Draw(cubeColorShader);

        lightingShader.use();
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.2f));

        lightingShader.setMatrix4f("u_View", view);
        lightingShader.setMatrix4f("u_Proj", proj);

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
