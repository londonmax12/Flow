#pragma once

#include "flow/flow_renderer.h"

#include "glad/glad.h"

namespace Flow {
    class FlowOpenGLImpl {
    public:
        static bool Init    ();
    };

    class OpenGLRenderer : public RendererBackend {
    public:
        OpenGLRenderer() : m_Vao(0), m_Vbo(0), m_Ibo(0) { }

        void Init() override;
        void BeginFrame() override;
        void Submit(RenderPacket packet) override;
        void EndFrame() override;
        void Shutdown() override;

        Vertex VertexPixelsToCoords(Vertex v) override;

    private:
        void CreateBuffers();

        GLuint m_ShaderProgram = 0;
        unsigned int m_Vao, m_Vbo, m_Ibo;
    };
}