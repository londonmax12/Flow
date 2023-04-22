#pragma once

#include <iostream>

#include "flow_renderer.h"

namespace Flow {
	class FlowContext {
	public:
		static bool Init();
		static void Shutdown();

		static FlowContext* GetInstance();

		RendererBackend* GetRenderer();

		void _SetRenderer(RendererBackend* renderer);

	private:
		inline static FlowContext* m_Instance = nullptr;

		RendererBackend* m_Renderer;
	};

	bool BeginFrame();
	void EndFrame();
}