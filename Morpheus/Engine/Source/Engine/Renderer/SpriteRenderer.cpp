#include "mepch.h"
#include "SpriteRenderer.h"
#include <glad/glad.h>

namespace Morpheus {

    SpriteRenderer::SpriteRenderer(entt::registry& registry, glm::vec2 screenSize)
        : m_VAO(0)
        , m_VBO(0)
        , m_Shader(nullptr)
        , m_WireframeShader(nullptr)
        , m_DiffuseMap(nullptr)
        , m_NormalMap(nullptr)
        , m_SpecularMap(nullptr)
        , m_ScreenSize(screenSize)
        , m_AmbientColor(glm::vec4(1.0f, 1.0f, 1.f, 0.25f))
        , m_Scale(1.0f)
        , m_EnableNormal(true)
        , m_EnableSpecular(true)
        , m_EnableWireframe(false)
    {
        auto& statisticsEntity = registry.ctx<Morpheus::StatisticsEntity>();
        auto& statistics = registry.get<Morpheus::StatisticsComponent>(statisticsEntity.id);
        m_NumberOfVertices = &statistics.vertices;
        m_DrawCalls = &statistics.drawCalls;

        m_Shader = new Morpheus::Shader("Assets/shaders/sprite.vert", "Assets/shaders/sprite.frag");
        m_WireframeShader = new Morpheus::Shader("Assets/shaders/wireframe.vert", "Assets/shaders/wireframe.frag", "Assets/shaders/wireframe.geom");

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2dUVColor), (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2dUVColor), (void*)sizeof(glm::vec2));
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2dUVColor), (void*)sizeof(glm::vec4));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glEnableVertexAttribArray(0);

        m_Shader->Enable();
        m_Shader->SetVec2("Resolution", m_ScreenSize);
        m_Shader->SetInt("u_texture", 0);
        m_Shader->SetInt("u_normal", 1);
        m_Shader->SetInt("u_specular", 2);
        m_Shader->Disable();

        SetScreenSize(m_ScreenSize);
    }

    SpriteRenderer::~SpriteRenderer()
    {
        delete m_Shader;
    }

    void SpriteRenderer::Draw(Texture* pDiffuseMap, Texture* pNormalMap, Texture* pSpecularMap, glm::vec4 destRect, glm::vec4 sourceRect, glm::vec4 color)
    {
        if (m_DiffuseMap != pDiffuseMap)
        {
            Render();
            m_DiffuseMap = pDiffuseMap;
            m_NormalMap = pNormalMap;
            m_SpecularMap = pSpecularMap;
        }

        RearrangeVertices(destRect, sourceRect, color);
    }

    void SpriteRenderer::Draw(Texture* pDiffuseMap, Texture* pNormalMap, glm::vec4 destRect, glm::vec4 sourceRect, glm::vec4 color)
    {
        if (m_DiffuseMap != pDiffuseMap)
        {
            Render();
            m_DiffuseMap = pDiffuseMap;
            m_NormalMap = pNormalMap;
        }

        RearrangeVertices(destRect, sourceRect, color);
    }

    void SpriteRenderer::Draw(Texture* pDiffuseMap, glm::vec4 destRect, glm::vec4 sourceRect, glm::vec4 color)
    {
        if (m_DiffuseMap != pDiffuseMap)
        {
            Render();
            m_DiffuseMap = pDiffuseMap;
        }

        RearrangeVertices(destRect, sourceRect, color);
    }

    void SpriteRenderer::RearrangeVertices(glm::vec4 destRect, glm::vec4 sourceRect, glm::vec4 color)
    {
        m_Vertices.push_back(Vertex2dUVColor(glm::vec2(destRect.x, destRect.y), glm::vec2(sourceRect.x, sourceRect.y), color));
        m_Vertices.push_back(Vertex2dUVColor(glm::vec2(destRect.x + destRect.z, destRect.y), glm::vec2(sourceRect.z, sourceRect.y), color));
        m_Vertices.push_back(Vertex2dUVColor(glm::vec2(destRect.x, destRect.y + destRect.w), glm::vec2(sourceRect.x, sourceRect.w), color));
        m_Vertices.push_back(Vertex2dUVColor(glm::vec2(destRect.x + destRect.z, destRect.y), glm::vec2(sourceRect.z, sourceRect.y), color));
        m_Vertices.push_back(Vertex2dUVColor(glm::vec2(destRect.x, destRect.y + destRect.w), glm::vec2(sourceRect.x, sourceRect.w), color));
        m_Vertices.push_back(Vertex2dUVColor(glm::vec2(destRect.x + destRect.z, destRect.y + destRect.w), glm::vec2(sourceRect.z, sourceRect.w), color));
    }

    void SpriteRenderer::AddSpotLight(glm::vec3 lightPosition, glm::vec4 lightColor, glm::vec3 lightFalloff)
    {
        if (m_SpotLights.size() < MAX_LIGHT_SOURCES)
        {
            m_SpotLights.push_back(SpotLight(lightPosition, lightColor, lightFalloff));
        }
    }

    void SpriteRenderer::SetAmbientColor(glm::vec4 ambientColor)
    {
        m_AmbientColor = ambientColor;
    }

    void SpriteRenderer::SetScreenSize(glm::vec2 screenSize)
    {
        m_ScreenSize = screenSize;

        m_ScreenTransform[0][0] = 2 / m_ScreenSize.x;
        m_ScreenTransform[1][1] = 2 / m_ScreenSize.y;
        m_ScreenTransform[2][0] = 0;
        m_ScreenTransform[2][1] = 0;

        m_Shader->Enable();
        m_Shader->SetVec2("Resolution", m_ScreenSize);
        m_Shader->Disable();
    }

    void SpriteRenderer::LookAt(int x, int y)
    {
        if (x != m_ScreenTransform[2][0] || y != m_ScreenTransform[2][1])
        {
            m_ScreenTransform[2][0] = (-1 + (2 / m_ScreenSize.x * x) * (1 / m_Scale));
            m_ScreenTransform[2][1] = -(-1 + (2 / m_ScreenSize.y * y) * (1 / m_Scale));
        }
    }

    glm::vec2 SpriteRenderer::LookingAt()
    {
        return glm::vec2(m_ScreenTransform[2][0], m_ScreenTransform[2][1]);
    }

    void SpriteRenderer::SetScale(float scale)
    {
        m_Scale = scale;
    }

    void SpriteRenderer::Render()
    {
        if (m_Vertices.size() == 0 || m_DiffuseMap == nullptr)
        {
            return;
        }

        if (m_EnableWireframe)
        {
            m_WireframeShader->Enable();
            m_WireframeShader->SetMat3("screenTransform", m_ScreenTransform);
            m_WireframeShader->SetFloat("scale", m_Scale);
            m_WireframeShader->Disable();
        }

        m_Shader->Enable();
        m_Shader->SetVec4("AmbientColor", m_AmbientColor);
        m_Shader->SetMat3("screenTransform", m_ScreenTransform);
        m_Shader->SetFloat("scale", m_Scale);
        m_Shader->SetBool("u_enableNormal", m_EnableNormal);
        m_Shader->SetBool("u_enableSpecular", m_EnableSpecular);

        glm::vec3 lightPositions[MAX_LIGHT_SOURCES] = { };
        glm::vec4 lightColors[MAX_LIGHT_SOURCES] = { };
        glm::vec3 lightFalloffs[MAX_LIGHT_SOURCES] = { };

        int index = 0;
        for (const auto& light : m_SpotLights)
        {
            glm::vec3 lightPosition = light.m_Position;

            lightPosition.x = lightPosition.x / m_ScreenSize.x;
            lightPosition.y = -((lightPosition.y - m_ScreenSize.y) / m_ScreenSize.y);
            lightPosition.z = lightPosition.z;

            lightPositions[index] = lightPosition;
            lightColors[index] = light.m_Color;
            lightFalloffs[index] = light.m_Falloff;

            index++;
        }

        GLsizei spotLightsSize = (GLsizei)m_SpotLights.size();
        GLsizei verticesSize = (GLsizei)m_Vertices.size();

        m_Shader->SetInt("TotalSpotLights", spotLightsSize);
        glUniform3fv(m_Shader->GetUniformLocation("LightPos"), spotLightsSize, (float*) lightPositions);
        glUniform4fv(m_Shader->GetUniformLocation("LightColor"), spotLightsSize, (float*) lightColors);
        glUniform3fv(m_Shader->GetUniformLocation("LightFalloff"), spotLightsSize, (float*) lightFalloffs);

        glBindVertexArray(m_VAO);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, m_SpecularMap->GetID());

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_NormalMap->GetID());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_DiffuseMap->GetID());

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2dUVColor) * verticesSize, &m_Vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Enable vertex attributes for position, uv, and color
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glDrawArrays(GL_TRIANGLES, 0, verticesSize);
        m_Shader->Disable();

        if (m_EnableWireframe)
        {
            m_WireframeShader->Enable();
            glDrawArrays(GL_TRIANGLES, 0, verticesSize);
            m_WireframeShader->Disable();
        }

        // Disable vertex attribute
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        glBindVertexArray(0);

        (*m_NumberOfVertices) += (int)(verticesSize);
        (*m_DrawCalls) += 1;

        m_Vertices.clear();
        m_SpotLights.clear();
    }

    void SpriteRenderer::EnableNormal(bool enable)
    {
        m_EnableNormal = enable;
    }

    void SpriteRenderer::EnableSpecular(bool enable)
    {
        m_EnableSpecular = enable;
    }

    void SpriteRenderer::EnableWireframe(bool enable)
    {
        m_EnableWireframe = enable;
    }

}

