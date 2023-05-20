#include "flow/flow_text_renderer.h"

#include <limits>

unsigned int Flow::TextRenderer::LengthUTF8(const char* string)
{
	unsigned int len = 0;

	for (int i = 0; i < INT_MAX; i++) {
		int chr = (int)string[i];

		// End of string
		if (chr == 0)
			break;
		// Normal character
		else if (chr < 127)
			continue;
		// Double-Byte character, increment i once
		else if ((chr & 0xE0) == 0xC0)
			i += 1;
		// Triple-byte character, increment i twice
		else if ((chr & 0xF0) == 0xE0)
			i += 2;
		// Four-byte character, increment i three times
		else if ((chr & 0xF8) == 0xF0)
			i += 3;
		else
			return 0;

		len++;
	}

	return len;
}

bool Flow::TextRenderer::BytesToCodepoint(const char* bytes, unsigned int offset, int* outCodepoint, unsigned int* outAdvance)
{
	int codepoint = (int)bytes[offset];
	// Normal single-byte character
	if (codepoint >= 0 && codepoint < 0x7F) {
		*outAdvance = 1;
		*outCodepoint = codepoint;
		return true;
	}
	// Double-byte character
	else if ((codepoint & 0xE0) == 0xC0) {
		codepoint = ((bytes[offset] & 0b00011111) << 6) + (bytes[offset + 1] & 0b00111111);
		*outAdvance = 2;
		*outCodepoint = codepoint;
		return true;
	}
	// Triple-byte character
	else if ((codepoint & 0xF0) == 0xE0) {
		codepoint = ((bytes[offset] & 0b00001111) << 12) + ((bytes[offset + 1] & 0b00111111) << 6) + (bytes[offset + 2] & 0b00111111);
		*outAdvance = 3;
		*outCodepoint = codepoint;
		return true;
	}
	// Four-byte character
	else if ((codepoint & 0xF8) == 0xF0) {
		codepoint = ((bytes[offset] & 0b00000111) << 18) + ((bytes[offset + 1] & 0b00111111) << 12) + ((bytes[offset + 2] & 0b00111111) << 6) + (bytes[offset + 3] & 0b00111111);
		*outAdvance = 4;
		*outCodepoint = codepoint;
		return true;
	}
	else {
		return false;
	}
}
