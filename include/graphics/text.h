/**
 * @file text.h
 * @brief Text rendering utilities for graphics.
 *
 */
#pragma once
#include <3ds.h>
#include <citro2d.h>
#include <string>

/**
 * @brief Graphics-related utilities.
 *
 */
namespace xs::graphics {

    /**
     * @class Text
     * @brief Handles rendering of text using Citro2D on the 3DS.
     */
    class Text {
    public:
        /**
         * @brief Constructs a new Text object and loads the default font.
         */
        Text();

        /**
         * @brief Destroys the Text object and frees resources.
         */
        ~Text();

        /**
         * @brief Draws a string at the specified position with color and scaling.
         *
         * @param str The string to render.
         * @param x The x-coordinate for the text position.
         * @param y The y-coordinate for the text position.
         * @param color The color of the text (default: white, fully opaque).
         * @param scaleX Horizontal scaling factor (default: 1.0f).
         * @param scaleY Vertical scaling factor (default: 1.0f).
         */
        void draw(const std::string& str, float x, float y,
                  u32 color = C2D_Color32(255,255,255,255),
                  float scaleX = 1.0f, float scaleY = 1.0f);

    private:
        /**
         * @brief The font used for rendering text.
         */
        C2D_Font font;

        /**
         * @brief The text buffer for storing rendered text.
         */
        C2D_TextBuf textBuf;
    };

}
