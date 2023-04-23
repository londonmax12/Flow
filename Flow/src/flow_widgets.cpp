#include "flow/flow_widgets.h"

void Flow::UIWidget::Init(Renderer* renderer)
{
	m_Renderer = renderer;
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

Flow::UIWindow::UIWindow(std::string name)
{
	m_Name = name;
}

bool Flow::UIWindow::Render()
{
	Vector2Int windowSize = CalcSize();
	
	m_Renderer->DrawRect({ m_X, m_Y }, windowSize, { 0.2f, 0.2f, 0.23f, 0.95f });

	return false;
}

Flow::Vector2Int Flow::UIWindow::CalcSize()
{
	return Vector2Int(50, 50);
}