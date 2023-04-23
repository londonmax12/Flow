#pragma once

#include <xhash>
#include <unordered_map>

#include "flow/flow_widgets.h"
#include "flow/flow_renderer.h"

namespace Flow {
	class FlowContext {
	public:
		static bool Init();
		static void Shutdown();

		static FlowContext* GetInstance();

		Renderer* GetRenderer();

		void EndFrame();

		bool WidgetExists(std::string id);
		UIWidget* GetWidget(std::string id);
		void AddWidget(std::string id, UIWidget* widget);

	private:
		inline static FlowContext* m_Instance = nullptr;

		Renderer* m_Renderer = nullptr;

		std::unordered_map <std::string, UIWidget*> m_Widgets;
	};

	bool BeginFrame();
	void EndFrame();
	
	bool BeginWindow(std::string name);
}
