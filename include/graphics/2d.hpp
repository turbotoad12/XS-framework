#pragma once

#include <3ds.h>
#include <citro2d.h>

namespace xs::graphics {
/**
 * @brief Draw a solid rectangle.
 *
 * @param x X coordinate of the top-left vertex of the rectangle
 * @param y Y coordinate of the top-left vertex of the rectangle
 * @param depth Z coordinate of the rectangle
 * @param width Width of the rectangle
 * @param height Height of the rectangle
 * @param color color() format
 */
void DrawSolidRect(float x, float y, float width, float height, float depth,
                   u32 color);
} // namespace xs::graphics
