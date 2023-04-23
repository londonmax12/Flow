#include "flow/flow.h"

#include <iostream>

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

void Flow::FlowContext::BeginFrame()
{
    while (!m_FrameStack.empty()) {
        m_FrameStack.pop();
    }
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
    if (GetFrameStackSize())
        widget->Start(m_FrameStack.top());

    m_Widgets[id] = widget;
}

void Flow::FlowContext::AddFrame(UIWidget* widget)
{
    m_FrameStack.push(widget);
}

void Flow::FlowContext::PopFrame()
{
    m_FrameStack.pop();
}

Flow::UIWidget* Flow::FlowContext::GetCurrentFrame()
{
    return m_FrameStack.top();
}

int Flow::FlowContext::GetFrameStackSize()
{
    return m_FrameStack.size();
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
    FlowContext* context = FlowContext::GetInstance();
    std::string id = "window_" + name;

    if (context->WidgetExists(id)) {
        context->GetWidget(id)->SetEnabled(true);
    }
    else {
        UIWindow* window = new UIWindow(name);
        context->AddWidget(id, window);
        
    }
    context->AddFrame(FlowContext::GetInstance()->GetWidget(id));

    return true;
}

void Flow::EndWindow()
{
    FlowContext* context = FlowContext::GetInstance();

    if (!context->GetFrameStackSize()) {
        std::cerr << "Flow: Cannot EndWindow: Frame stack has 0 frames " << std::endl;
        return;
    }

    context->PopFrame();
}

bool Flow::Checkbox(std::string label, bool& value)
{
    FlowContext* context = FlowContext::GetInstance();
    std::string id = "checkbox_" + label;

    if (context->WidgetExists(id)) {
        context->GetWidget(id)->SetEnabled(true);
    }
    else {
        UICheckbox* cb = new UICheckbox(label);
        context->AddWidget(id, cb);

    }
    return false;
}
