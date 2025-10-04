#include "graphics/2d.hpp"
#include <cstdio>

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
                   u32 color) {
  // Diagnostic print to help debug visibility in emulator
#ifdef DEBUG
  printf("DrawSolidRect: x=%.1f y=%.1f w=%.1f h=%.1f depth=%.3f color=0x%08X\n",
         x, y, width, height, depth, color);
#endif
  // Draw an extra thin rectangle at depth 0.0 in case depth ordering is
  // inverted
  constexpr float kRectOffset = 2.0f;
  constexpr float kRectScale = 4.0f;
  C2D_DrawRectSolid(x + kRectOffset, y + kRectOffset, 0.0f, width / kRectScale,
                    height / kRectScale, color);
  // Draw an extra thin rectangle at depth 0.0 in case depth ordering is
  // inverted
  C2D_DrawRectSolid(x + 2.0f, y + 2.0f, 0.0f, width / 4.0f, height / 4.0f,
                    color);
}
} // namespace xs::graphics