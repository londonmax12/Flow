#pragma once

#include <xhash>
#include <unordered_map>
#include <stack>

#include "flow/flow_widgets.h"
#include "flow/flow_renderer.h"

namespace Flow {
	class FlowContext {
	public:
		static bool Init();
		static void Shutdown();

		static FlowContext* GetInstance();

		Renderer* GetRenderer();

		void BeginFrame();
		void EndFrame();

		bool WidgetExists(std::string id);
		UIWidget* GetWidget(std::string id);
		void AddWidget(std::string id, UIWidget* widget);

		void AddFrame(UIWidget* widget);
		void PopFrame();
		UIWidget* GetCurrentFrame();
		int GetFrameStackSize();

	private:
		inline static FlowContext* m_Instance = nullptr;

		Renderer* m_Renderer = nullptr;

		std::stack<UIWidget*> m_FrameStack;

		std::unordered_map <std::string, UIWidget*> m_Widgets;
	};

	bool BeginFrame();
	void EndFrame();
	
	bool BeginWindow(std::string name);
	void EndWindow();

	bool Checkbox(std::string label, bool& value);
}
