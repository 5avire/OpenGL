#include "TestTexture2D.h"

#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>
#include <strings.h>
#include "renderer.h"

namespace test {

    TestTexture2D::TestTexture2D() 
        : m_Proj(glm::ortho(0.0f, 1080.0f, 0.0f, 720.0f, -1.0f, 1.0f)),
          m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
          m_TranslationA(200, 100, 0), m_TranslationB(400, 100, 0)
    {

        glm::vec3 translationA(200, 100, 0);
        glm::vec3 translationB(400, 100, 0);

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

        m_VAO = std::make_unique<vertexArray>();

        m_VBO = std::make_unique<vertexBuffer>(positions, 4 * 4 * sizeof(float));

        vertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        m_VAO->bufferAdd(*m_VBO, layout);
        m_IBO = std::make_unique<indexBuffer>(indices, 6);

        m_Shader = std::make_unique<Shader>("res/shaders/shader.glsl");
        m_Shader->Bind();
        m_Texture = std::make_unique<Texture>("res/textures/awesomeface.png");
        m_Texture->Bind();
        m_Shader->setUniform1i("u_Texture", 0);
    }

    TestTexture2D::~TestTexture2D() 
    {
    }

    void TestTexture2D::OnUpdate(float deltaTime) 
    {
    }

    void TestTexture2D::OnRender() 
    {

        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        m_Texture->Bind();

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->setUniformMat4f("u_MVP", mvp);

            renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->setUniformMat4f("u_MVP", mvp);

            renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
        }

    }

    void TestTexture2D::OnImGuiRender() 
    {
                ImGui::SliderFloat3("TranslationA: ", &m_TranslationA.x, 0.0f, 1080.0f);
                ImGui::SliderFloat3("TranslationB: ", &m_TranslationB.x, 0.0f, 1080.0f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

}
