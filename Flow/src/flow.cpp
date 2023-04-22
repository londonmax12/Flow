#include "flow.h"

bool Flow::FlowContext::Init()
{
    if (m_Instance)
        return false;

    m_Instance = new FlowContext();

    return true;
}

void Flow::FlowContext::Shutdown()
{
    if (!m_Instance)
        return;

    if (m_Instance->m_Renderer) {
        m_Instance->m_Renderer->Shutdown();
    }

    delete m_Instance;
}

Flow::FlowContext * Flow::FlowContext::GetInstance()
{
    return m_Instance;
}

Flow::RendererBackend* Flow::FlowContext::GetRenderer()
{
    return m_Renderer;
}

void Flow::FlowContext::_SetRenderer(RendererBackend* renderer)
{
    m_Renderer = renderer;
}

bool Flow::BeginFrame()
{
    if (!FlowContext::GetInstance())
        return false;

    if (!FlowContext::GetInstance()->GetRenderer())
        FlowContext::GetInstance()->GetRenderer()->BeginFrame();
}

void Flow::EndFrame()
{
    if (!FlowContext::GetInstance())
        return;

    if (!FlowContext::GetInstance()->GetRenderer())
        FlowContext::GetInstance()->GetRenderer()->EndFrame();
}
