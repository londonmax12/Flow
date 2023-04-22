#include "impl/flow_opengl_impl.h"
#include "flow.h"

#include <stddef.h>
#include <iostream>

namespace Flow {
    void OpenGLRenderer::Init() {
        if (!FlowContext::GetInstance()) {
            std::cerr << "Flow: Failed to initialize renderer: Flow is not initialized" << std::endl;
        }

        gladLoadGL();

        CreateBuffers();

        const char* vertexShaderSource = R"glsl(
            #version 330 core

            layout(location = 0) in vec3 aPosition;
            layout(location = 1) in vec4 aColor;

            out vec4 vColor;

            void main() {
                gl_Position = vec4(aPosition, 1.0);
                vColor = aColor;
            }
        )glsl";
        const char* fragmentShaderSource = R"glsl(
            #version 330 core

            in vec4 vColor;

            out vec4 fragColor;

            void main() {
                fragColor = vColor;
            }
        )glsl";

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        GLint success = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cerr << "Flow: Vertex shader compilation failed: " << infoLog << std::endl;
            return;
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            std::cerr << "Flow: Fragment shader compilation failed: " << infoLog << std::endl;
            return;
        }

        m_ShaderProgram = glCreateProgram();
        glAttachShader(m_ShaderProgram, vertexShader);
        glAttachShader(m_ShaderProgram, fragmentShader);
        glLinkProgram(m_ShaderProgram);
    }

    void OpenGLRenderer::BeginFrame() {
    }

    void OpenGLRenderer::Submit(RenderPacket packet) {
        glUseProgram(m_ShaderProgram);

        if (!packet.vertices || !packet.indices) {
            return;
        }
     
        glBindVertexArray(m_Vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
        glBufferData(GL_ARRAY_BUFFER, packet.verticesSize * sizeof(Vertex), packet.vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, packet.indicesSize * sizeof(int), packet.indices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, r));

        glUseProgram(m_ShaderProgram);
        glDrawElements(GL_TRIANGLES, packet.indicesSize, GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    }

    void OpenGLRenderer::EndFrame() { }
    void OpenGLRenderer::Shutdown() {
        if (m_ShaderProgram)
            glDeleteProgram(m_ShaderProgram);
    }
     
    void OpenGLRenderer::CreateBuffers()
    {
        glGenVertexArrays(1, &m_Vao);
        glBindVertexArray(m_Vao);

        glGenBuffers(1, &m_Vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);

        glGenBuffers(1, &m_Ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);

        glBindVertexArray(0);
    }

    bool FlowOpenGLImpl::Init()
    {
        if (!FlowContext::GetInstance())
            FlowContext::Init();

        Flow::OpenGLRenderer* renderer = new Flow::OpenGLRenderer();
        renderer->Init();

        FlowContext::GetInstance()->_SetRenderer(renderer);

        return false;
    }
}