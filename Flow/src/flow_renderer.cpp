#include "flow_renderer.h"

void Flow::Renderer::BeginFrame()
{
	if (m_Backend)
	{
		m_Backend->BeginFrame();
		m_ScreenSize = m_Backend->GetScreenSize();
	}
}

void Flow::Renderer::EndFrame()
{
	if (m_Backend)
		m_Backend->EndFrame();
}

void Flow::Renderer::Shutdown()
{
	if (m_Backend)
		m_Backend->Shutdown();
}

void Flow::Renderer::DrawRect(int x, int y, int w, int h, Color color)
{
	DrawRect((float)x, (float)y, (float)w, (float)h, color);
}

void Flow::Renderer::DrawRect(Vector2Int position, Vector2Int size, Color color)
{
	DrawRect((float)position.x, (float)position.y, (float)size.x, (float)size.y, color);
}

void Flow::Renderer::DrawRect(float x, float y, float w, float h, Color color)
{
	if (!m_Backend)
		return;

	if (m_ScreenSize.x == 0 || m_ScreenSize.y == 0)
		return;
	
	if (w == 0 || h == 0)
		return;

	Flow::Vertex vertices[] = {
	{ x,		y,		0.f, color.r, color.g, color.b, color.a },
	{ x + w,	y,		0.f, color.r, color.g, color.b, color.a },
	{ x + w,	y + h,	0.f, color.r, color.g, color.b, color.a },
	{ x,		y + h,	0.f, color.r, color.g, color.b, color.a }
	};

	for (auto& v : vertices) {
		Vertex newVertex = m_Backend->VertexPixelsToCoords(v);
		v = newVertex;
	}

	int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	Flow::RenderPacket packet;
	packet.vertices = vertices;
	packet.verticesSize = sizeof(vertices) / sizeof(vertices[0]);
	packet.indices = indices;
	packet.indicesSize = sizeof(indices) / sizeof(indices[0]);

	m_Backend->Submit(packet);
}

void Flow::Renderer::_SetBackend(RendererBackend* backend)
{
	m_Backend = backend;
}

Flow::RendererBackend* Flow::Renderer::GetBackend()
{
	return m_Backend;
}
