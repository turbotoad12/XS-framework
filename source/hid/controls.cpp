#include "hid/controls.hpp"

namespace xs::hid::control {
/**
 * @brief Gets the current position of the circle pad.
 * @return circlePosition Current circle pad position.
 */
circlePosition GetCirclePadPosition() {
  circlePosition pos;
  hidCircleRead(&pos);
  return pos;
}
/**
 * @brief Gets the current position of the touch screen.
 * @return touchPosition Current touch screen position.
 */
touchPosition GetTouchPosition() {
  touchPosition pos;
  hidTouchRead(&pos);
  return pos;
}

} // namespace xs::hid::control