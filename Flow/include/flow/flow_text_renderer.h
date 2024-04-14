#include <string>
#include <sstream>
#include <vector>

namespace Flow {
    struct Font {
        int numCharacters;
        char firstCharacter;
        int fontWidth;
        int fontHeight;
        std::vector<std::vector<char>> fontData;
    };

    class FontRenderer {
    public:
        FontRenderer() {}

        void LoadTTFFont(const std::string& fontPath);

    private:
        std::vector<Font> fonts;

        bool ReadFontDataTTF(const std::string& fontPath, Font& font);
    };
}