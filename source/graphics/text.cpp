/**
 * @file text.cpp
 * @brief Text rendering functionality.
 * 
 */
#include "graphics/text.h"

namespace xs::graphics {


    /**
     * @brief Constructs a new Text object and loads the system font.
     */
    Text::Text() {
        font = C2D_FontLoadSystem(CFG_REGION_USA); // Load system font
        textBuf = C2D_TextBufNew(4096);
    }


    /**
     * @brief Destroys the Text object and frees font and text buffer resources.
     */
    Text::~Text() {
        C2D_FontFree(font);
        C2D_TextBufDelete(textBuf);
    }

    /**
     * @brief Draws a string at the specified position with color and scaling.
     *
     * @param str The string to render.
     * @param x The x-coordinate for the text position.
     * @param y The y-coordinate for the text position.
     * @param color The color of the text.
     * @param scaleX Horizontal scaling factor.
     * @param scaleY Vertical scaling factor.
     */
    void Text::draw(const std::string& str, float x, float y,
                    u32 color, float scaleX, float scaleY) {
        C2D_Text text;
        C2D_TextBufClear(textBuf);
        C2D_TextFontParse(&text, font, textBuf, str.c_str());
        C2D_TextOptimize(&text);

        C2D_DrawText(&text, C2D_WithColor, x, y, 0.0f,
                     scaleX, scaleY, color);
    }
}