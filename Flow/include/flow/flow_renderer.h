#pragma once

#include "flow_types.h"

namespace Flow {
    struct Vertex {
        float x;
        float y;
        float z;
        float r;
        float g;
        float b;
        float a;

        Vertex(float X, float Y, float Z, float R, float G, float B, float A) :
            x(X), y(Y), z(Z), r(R), g(G), b(B), a(A) { }
    };

    struct RenderPacket {
        int verticesSize = 0;
        Vertex* vertices = 0;
        int indicesSize = 0;
        int* indices = 0;
    };

    // Abstract renderer class
	class RendererBackend {
    public:
        virtual void Init() = 0;
        virtual void BeginFrame() = 0;
        virtual void Submit(RenderPacket packet) = 0;
        virtual void EndFrame() = 0;
        virtual void Shutdown() = 0;

        virtual Vertex VertexPixelsToCoords(Vertex v) = 0;

        Vector2Int GetScreenSize() { return m_ScreenSize; }
           
    protected:
        Vector2Int m_ScreenSize;
	};
    
    // A frontend renderer class
    class Renderer {
    public:
        void BeginFrame();
        void EndFrame();
        void Shutdown();

        void DrawRect(int x, int y, int w, int h, Color color = { 1.f, 1.f, 1.f, 1.f });
        void DrawRect(Vector2Int position, Vector2Int size, Color color = { 1.f, 1.f, 1.f, 1.f });
        void DrawRect(float x, float y, float w, float h, Color color = { 1.f, 1.f, 1.f, 1.f });

        void _SetBackend(RendererBackend* backend);
        RendererBackend* GetBackend();

    private:
        Vector2Int m_ScreenSize;

        RendererBackend* m_Backend = 0;
    };
}