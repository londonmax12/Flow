#pragma once

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
	};
}