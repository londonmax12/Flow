
namespace Flow {
	class TextRenderer {
	public:
		struct FontGlyph {
			int codepoint;
			int x;
			int y;
			int width;
			int height;
			int xOffset;
			int yOffset;
			int xAdvance;
			int pageID;
		};

		struct FontKerning
		{
			int codepoint0;
			int codepoint1;

			int amount;
		};
		enum FontType
		{
			FONT_TYPE_BITMAP
		};

		struct FontPage
		{
			int id;
			const char* file;
		};

		unsigned int LengthUTF8(const char* string);
		bool BytesToCodepoint(const char* bytes, unsigned int offset, int* outCodepoint, unsigned int* outAdvance);

	private:
		FontType m_Type;
		const char* m_Face;
		int m_Size;
		int m_LineHeight;
		int m_Baseline;

		int m_AtlasSizeX;
		int m_AtlasSizeY;

		int m_GlyphCount;
		FontGlyph* m_Glyphs;

		int m_KerningCount;
		FontKerning* m_Kernings;

		float m_TabXAdvace;

		int m_InternalDataSize;
		void* m_InternalData;
	};
}