#pragma comment(lib, "rpcrt4.lib") 

#include <string>

#include "flow/flow_types.h"
#include "flow_renderer.h"

namespace Flow {
	class UIWidget {
	public:
		static void Init(Renderer* renderer);

		void Start(UIWidget* frame);
		void Update();

		void SetEnabled(bool enabled);
		
		Vector2Int GetPosition();

	protected:
		virtual bool Render() = 0;
		
		virtual Vector2Int CalcSize() = 0;
		virtual Vector2Int CalcPosition() = 0;

		inline static Renderer* m_Renderer;

		bool m_Enabled = true;

		UIWidget* m_Frame = nullptr;

		int m_X = 0;
		int m_Y = 0;

		std::string m_Label = "";
	};

	class UIWindow : public UIWidget {
	public:
		UIWindow(std::string label);

	private:
		bool Render() override;

		Vector2Int CalcSize() override;
		Vector2Int CalcPosition() override;
	};

	class UICheckbox : public UIWidget {
	public:
		UICheckbox(std::string label);

	private:
		bool Render() override;

		Vector2Int CalcSize();
		Vector2Int CalcPosition() override;
	};
}