#include "graphics/2d.hpp"
#include <cstdio>

namespace xs::graphics {
/**
 * @brief Draw a solid rectangle.
 *
 * @param x X coordinate of the top-left vertex of the rectangle
 * @param y Y coordinate of the top-left vertex of the rectangle
 * @param depth Z coordinate of the rectangle 0.0f - 1.0f
 * @param width Width of the rectangle
 * @param height Height of the rectangle
 * @param color color() format
 */
void DrawSolidRect(float x, float y, float depth, float width, float height, 
                   u32 color) {
    C2D_DrawRectSolid(x, y, depth, width, height, color);
}
/**
 * @brief Draw a Line.
 *
 * @param x1 X coordinate of the start point of the line
 * @param y1 Y coordinate of the start point of the line
 * @param x2 X coordinate of the end point of the line
 * @param y2 Y coordinate of the end point of the line
 * @param thickness Thickness of the line
 * @param depth Z coordinate of the line 0.0f - 1.0f
 * @param color color() format
 */
void DrawSolidLine(float x1, float y1, float x2, float y2, float thickness,
              float depth, u32 color) {
    C2D_DrawLine(x1, y1, color, x2, y2, color, thickness, depth);
}
} // namespace xs::graphics