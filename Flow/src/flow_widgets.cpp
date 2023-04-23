#include "flow/flow_widgets.h"

void Flow::UIWidget::Init(Renderer* renderer)
{
	m_Renderer = renderer;
}

void Flow::UIWidget::Start(UIWidget* frame)
{
	m_Frame = frame;
}

void Flow::UIWidget::Update()
{
	if (m_Enabled)
		Render();
}

void Flow::UIWidget::SetEnabled(bool enabled)
{
	m_Enabled = enabled;
}

Flow::Vector2Int Flow::UIWidget::GetPosition()
{
	return Vector2Int(m_X, m_Y);
}


Flow::UIWindow::UIWindow(std::string name)
{
	m_Label = name;
}

bool Flow::UIWindow::Render()
{
	Vector2Int windowSize = CalcSize();
	
	m_Renderer->DrawRect(CalcPosition(), windowSize, {0.2f, 0.2f, 0.23f, 0.95f});

	return false;
}

Flow::Vector2Int Flow::UIWindow::CalcSize()
{
	return Vector2Int(50, 50);
}

Flow::Vector2Int Flow::UIWindow::CalcPosition()
{
	return { m_X, m_Y };
}

Flow::UICheckbox::UICheckbox(std::string label)
{
	m_Label = label;
}

bool Flow::UICheckbox::Render()
{
	Vector2Int checkboxSize = CalcSize();

	m_Renderer->DrawRect(CalcPosition(), checkboxSize, {0.2f, 0.2f, 0.23f, 0.95f});

	return false;
}

Flow::Vector2Int Flow::UICheckbox::CalcSize()
{
	return Vector2Int(20, 20);
}

Flow::Vector2Int Flow::UICheckbox::CalcPosition()
{
	Flow::Vector2Int pos = { m_X, m_Y };

	if (m_Frame) {
		pos = pos + m_Frame->GetPosition();
	}

	return pos;
}
