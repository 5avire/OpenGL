#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>

#include "renderer.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "vertexBuffer.h"
#include "vertexBufferLayout.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "shader.h"
#include "texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


const int WIDTH = 1080;
const int HEIGHT = 720;

static void processUserInputs(GLFWwindow *window){
    if ( glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ) 
        glfwSetWindowShouldClose(window, true);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    std::cout << "OpenGL:" << glGetString(GL_VERSION) << std::endl;

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cout << "Error: " << glewGetErrorString(err);
    }

    {
        float positions[] = {
             -50.0f,  -50.0f, 0.0f, 0.0f,
              50.0f,  -50.0f, 1.0f, 0.0f,
              50.0f,   50.0f, 1.0f, 1.0f,
             -50.0f,   50.0f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        // Initializing the buffers and vertex arrays
        vertexArray va;

        vertexBuffer vb(positions, 4 * 4 * sizeof(float));

        vertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        va.bufferAdd(vb, layout);

        indexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        Shader Shader("res/shaders/shader.glsl");
        Shader.Bind();

        Texture texture("res/textures/awesomeface.png");
        texture.Bind();
        Shader.setUniform1i("u_Texture", 0);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        Shader.Unbind();

        Renderer renderer;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();

        glm::vec3 translationA(200, 100, 0);
        glm::vec3 translationB(400, 100, 0);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            // FPS

            // Input 
            processUserInputs(window);

            /* Render here */ 
            renderer.Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {
                ImGui::SliderFloat3("TranslationA: ", &translationA.x, 0.0f, (float)WIDTH);
                ImGui::SliderFloat3("TranslationB: ", &translationB.x, 0.0f, (float)WIDTH);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
                glm::mat4 mvp = proj * view * model;
                Shader.Bind();
                Shader.setUniformMat4f("u_MVP", mvp);

                renderer.Draw(va, ib, Shader);
            }

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
                glm::mat4 mvp = proj * view * model;
                Shader.Bind();
                Shader.setUniformMat4f("u_MVP", mvp);

                renderer.Draw(va, ib, Shader);
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
