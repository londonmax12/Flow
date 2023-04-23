#pragma once

namespace Flow {
	struct Vector2Int
	{
		int x = 0;
		int y = 0;

		Vector2Int() = default;
		Vector2Int(int X, int Y) 
			: x(X), y(Y) { }
	};
	struct Color {
		float r;
		float g;
		float b;
		float a;

		Color(float R, float G, float B, float A = 1.0f) 
			: r(R), g(G), b(B), a(A) { }
	};
}