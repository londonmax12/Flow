#pragma once

#include <iostream>

#include "flow_renderer.h"

namespace Flow {
	class FlowContext {
	public:
		static bool Init();
		static void Shutdown();

		static FlowContext* GetInstance();

		Renderer* GetRenderer();

	private:
		inline static FlowContext* m_Instance = nullptr;

		Renderer* m_Renderer = nullptr;
	};

	bool BeginFrame();
	void EndFrame();
}