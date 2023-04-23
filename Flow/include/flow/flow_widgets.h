#pragma comment(lib, "rpcrt4.lib") 

#include <string>

#include "flow/flow_types.h"
#include "flow_renderer.h"

namespace Flow {
	class UIWidget {
	public:
		static void Init(Renderer* renderer);

		void Update();

		void SetEnabled(bool enabled);

	protected:
		virtual bool Render() = 0;
		
		inline static Renderer* m_Renderer;

		bool m_Enabled = true;
	};

	class UIWindow : public UIWidget {
	public:
		UIWindow(std::string name);

	private:
		std::string m_Name;

		int m_X = 0;
		int m_Y = 0;

		bool Render() override;
		
		Vector2Int CalcSize();
	};
}