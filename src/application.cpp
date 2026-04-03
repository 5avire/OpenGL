#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "renderer.h"

#include "vertexBuffer.h"
#include "vertexBufferLayout.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "shader.h"
#include "texture.h"


static void processUserInputs(GLFWwindow *window){
    if ( glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ) 
        glfwSetWindowShouldClose(window, true);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
};

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
    window = glfwCreateWindow(1080, 720, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    GLCall(glfwMakeContextCurrent(window));
    std::cout << "OpenGL:" << glGetString(GL_VERSION) << std::endl;
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);


    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cout << "Error: " << glewGetErrorString(err);
    }

    {
        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f
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

        Shader Shader("res/shaders/shader.glsl");
        Shader.Bind();
        Shader.setUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        Texture texture("res/textures/awesomeface.png");
        texture.Bind();
        Shader.setUniform1i("u_Texture", 0);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        Shader.Unbind();

        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            // FPS

            // Input 
            processUserInputs(window);

            /* Render here */ 
            renderer.Clear();

            Shader.Bind();
            Shader.setUniform4f("u_Color", r, 0.2f, 0.7f, 1.0f);

            renderer.Draw(va, ib, Shader);


            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f) 
                increment = 0.05f;

            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
