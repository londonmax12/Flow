// Example of a Windows OpenGL window using Flow
#pragma comment(lib, "opengl32.lib")

#include "flow.h"
#include "impl/flow_opengl_impl.h"

#include <Windows.h>
#include <GL/gl.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "OpenGLWindow";
    RegisterClass(&wc);

    HWND hWnd = CreateWindow("OpenGLWindow", "OpenGL Window", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);
    if (!hWnd) {
        return -1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    HDC hDC = GetDC(hWnd);

    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    int iPixelFormat = ChoosePixelFormat(hDC, &pfd);

    if (!iPixelFormat) {
        return -1;
    }

    if (!SetPixelFormat(hDC, iPixelFormat, &pfd)) {
        return -1;
    }

    HGLRC hRC = wglCreateContext(hDC);
    if (!hRC) {
        return -1;
    }
    if (!wglMakeCurrent(hDC, hRC)) {
        return -1;
    }
    
    // TODO: Remove temp code
    Flow::Vertex vertices[] = {
        { -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f },
        { 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
        { 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
        { -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f }
    };
    int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    Flow::RenderPacket packet;
    packet.vertices = vertices;
    packet.verticesSize = sizeof(vertices) / sizeof(vertices[0]);
    packet.indices = indices;
    packet.indicesSize = sizeof(indices) / sizeof(indices[0]);

    Flow::FlowOpenGLImpl::Init();

    while (true) {
        MSG msg = {};
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            glClearColor(0.7f, 0.7f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            Flow::BeginFrame();
            Flow::FlowContext::GetInstance()->GetRenderer()->Submit(packet);
            Flow::EndFrame();

            SwapBuffers(hDC);
        }
    }

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
    DestroyWindow(hWnd);

    return 0;
}