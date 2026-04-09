#pragma once

#include "Test.h"
#include <glm/glm.hpp>

#include <vertexBuffer.h>
#include <vertexBufferLayout.h>
#include <texture.h>

#include <memory>

namespace test
{
    class TestTexture2D : public Test 
    {
        public:
            TestTexture2D();
            ~TestTexture2D();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;
        private:
            std::unique_ptr<vertexArray> m_VAO;
            std::unique_ptr<indexBuffer> m_IBO;
            std::unique_ptr<vertexBuffer> m_VBO;
            std::unique_ptr<Shader> m_Shader;
            std::unique_ptr<Texture> m_Texture;

            glm::mat4 m_Proj, m_View;
            
            glm::vec3 m_TranslationA, m_TranslationB;
    };
}
