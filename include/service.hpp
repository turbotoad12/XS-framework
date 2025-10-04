#pragma once
#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>

namespace xs::services {

enum ServiceFlags : uint32_t {
  NONE = 0,
  GFX_SERVICE = 1 << 0,
  NEWS_SERVICE = 1 << 1,
  CONSOLE_TOP = 1 << 2,
  CONSOLE_BOTTOM = 1 << 3,
  C2D_SERVICE = 1 << 4,
  C3D_SERVICE = 1 << 5,
};

} // namespace xs::services

namespace xs::sys {

class Services {
public:
  explicit Services(uint32_t f);
  ~Services();

  void enable(uint32_t f);
  void disable(uint32_t f);

private:
  uint32_t flags = xs::services::NONE;
};

} // namespace xs::sys
