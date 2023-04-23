#include "flow/flow.h"

#include <random>

bool Flow::FlowContext::Init()
{
    if (m_Instance)
        return false;

    m_Instance = new FlowContext();

    m_Instance->m_Renderer = new Renderer();
    UIWidget::Init(m_Instance->m_Renderer);

    return true;
}

void Flow::FlowContext::Shutdown()
{
    if (!m_Instance)
        return;

    if (m_Instance->m_Renderer) {
        m_Instance->m_Renderer->Shutdown();
    }

    for (auto& w : m_Instance->m_Widgets) {
        delete w.second;
    }

    delete m_Instance;
}

Flow::FlowContext * Flow::FlowContext::GetInstance()
{
    return m_Instance;
}

Flow::Renderer* Flow::FlowContext::GetRenderer()
{
    return m_Renderer;
}

void Flow::FlowContext::EndFrame()
{
    for (auto& w : m_Widgets) {
        w.second->Update();
        w.second->SetEnabled(false);
    }
}

bool Flow::FlowContext::WidgetExists(std::string id)
{
    return m_Widgets.count(id) > 0;
}

Flow::UIWidget* Flow::FlowContext::GetWidget(std::string id)
{
    return m_Widgets[id];
}

void Flow::FlowContext::AddWidget(std::string id, UIWidget* widget)
{
    m_Widgets[id] = widget;
}

bool Flow::BeginFrame()
{
    if (!FlowContext::GetInstance())
        return false;

    if (FlowContext::GetInstance()->GetRenderer())
        FlowContext::GetInstance()->GetRenderer()->BeginFrame();
}

void Flow::EndFrame()
{
    if (!FlowContext::GetInstance())
        return;

    FlowContext::GetInstance()->EndFrame();

    if (FlowContext::GetInstance()->GetRenderer())
        FlowContext::GetInstance()->GetRenderer()->EndFrame();
}

bool Flow::BeginWindow(std::string name)
{
    std::string id = "window_" + name;
    if (FlowContext::GetInstance()->WidgetExists(id)) {
        FlowContext::GetInstance()->GetWidget(id)->SetEnabled(true);
    }
    else {
        UIWindow* window = new UIWindow(name);
        FlowContext::GetInstance()->AddWidget(id, window);
    }
    
    return false;
}
