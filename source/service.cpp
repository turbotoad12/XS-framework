#include "service.hpp"

namespace xs {
    namespace services {
        // Flags are declared in the header; do not redefine here.
    }
}

namespace xs::sys {
// Implementations for xs::sys::Services (declaration in include/service.h)

Services::Services(uint32_t f) {
    enable(f);
}

Services::~Services() {
    disable(flags);
}

void Services::enable(uint32_t f) {
    using namespace xs::services;

    if ((f & GFX_SERVICE) && !(flags & GFX_SERVICE)) {
        gfxInitDefault();
        flags |= GFX_SERVICE;
    }
    if ((f & NEWS_SERVICE) && !(flags & NEWS_SERVICE)) {
        newsInit();
        flags |= NEWS_SERVICE;
    }
    if ((f & CONSOLE_TOP) && !(flags & CONSOLE_TOP)) {
        consoleInit(GFX_TOP, NULL);
        flags |= CONSOLE_TOP;
    }
    if ((f & CONSOLE_BOTTOM) && !(flags & CONSOLE_BOTTOM)) {
        consoleInit(GFX_BOTTOM, NULL);
        flags |= CONSOLE_BOTTOM;
    }
}

void Services::disable(uint32_t f) {
    using namespace xs::services;

    if ((f & NEWS_SERVICE) && (flags & NEWS_SERVICE)) {
        newsExit();
        flags &= ~NEWS_SERVICE;
    }
    if ((f & GFX_SERVICE) && (flags & GFX_SERVICE)) {
        gfxExit();
        flags &= ~GFX_SERVICE;
    }
}

} // namespace xs::sys
