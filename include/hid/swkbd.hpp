#pragma once

#include <3ds.h>
#include <cstddef>
#include <string>

namespace xs::hid {

// Swkbd flags
enum SwkbdFlags {
    SWKBD_NORMAL = 1 << 0,   // normal text input
    SWKBD_NUMERIC = 1 << 1,  // numeric keypad only
    SWKBD_PASSWORD = 1 << 2, // hide input (password style)
};

class Swkbd {
  public:
    Swkbd(int flags = SWKBD_NORMAL, size_t maxLen = 64);

    void setHint(const char *hint);
    void setValidation(SwkbdValidInput input);
    std::string getInput();

  private:
    SwkbdState kbd;
    size_t maxLen;
};

} // namespace xs::hid