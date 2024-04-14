#include "flow/flow_text_renderer.h"

#include <fstream>
#include <iostream>


void Flow::FontRenderer::LoadTTFFont(const std::string& fontPath)
{
    Font font;
    if (!ReadFontDataTTF(fontPath, font)) {
        std::cerr << "Failed to load font: " << fontPath << std::endl;
        return;
    }
    fonts.push_back(font);
}

bool Flow::FontRenderer::ReadFontDataTTF(const std::string& fontPath, Font& font)
{
    std::ifstream fontFile(fontPath, std::ios::binary);
    if (!fontFile) {
        std::cerr << "Failed to open font file: " << fontPath << std::endl;
        return false;
    }

    // Read the font header
    std::uint32_t version;
    fontFile.read(reinterpret_cast<char*>(&version), sizeof(version));
    fontFile.read(reinterpret_cast<char*>(&font.numCharacters), sizeof(font.numCharacters));
    fontFile.read(reinterpret_cast<char*>(&font.firstCharacter), sizeof(font.firstCharacter));
    fontFile.read(reinterpret_cast<char*>(&font.fontWidth), sizeof(font.fontWidth));
    fontFile.read(reinterpret_cast<char*>(&font.fontHeight), sizeof(font.fontHeight));

    if (version != 1) {
        std::cerr << "Invalid font file version." << std::endl;
        fontFile.close();
        return false;
    }

    // Read the font data
    font.fontData.resize(font.numCharacters * font.fontHeight, std::vector<char>(font.fontWidth, 0));
    std::vector<char> buffer(font.fontWidth);
    for (int i = 0; i < font.numCharacters * font.fontHeight; ++i) {
        fontFile.read(buffer.data(), buffer.size());
        for (int j = 0; j < font.fontWidth; ++j) {
            font.fontData[i][j] = buffer[j];
        }
    }

    fontFile.close();
    return true;
}
