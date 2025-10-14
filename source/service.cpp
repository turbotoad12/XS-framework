#include "service.hpp"

namespace xs {
namespace services {
// Only the enum lives in the header, no variables needed here
}
} // namespace xs

namespace xs::sys {

Services::Services(uint32_t f) { enable(f); }

Services::~Services() { disable(flags); }

void Services::enable(uint32_t f) {
    using namespace xs::services;

    // --- Initialize in proper order ---
    if ((f & C3D_SERVICE) && !(flags & C3D_SERVICE)) {
        C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
        flags |= C3D_SERVICE;
    }

    if ((f & C2D_SERVICE) && !(flags & C2D_SERVICE)) {
        C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
        C2D_Prepare();
        flags |= C2D_SERVICE;
    }

    if ((f & GFX_SERVICE) && !(flags & GFX_SERVICE)) {
        gfxInitDefault();
        flags |= GFX_SERVICE;
    }

    if ((f & NEWS_SERVICE) && !(flags & NEWS_SERVICE)) {
        newsInit();
        flags |= NEWS_SERVICE;
    }

    if ((f & CONSOLE_TOP) && !(flags & CONSOLE_TOP)) {
        consoleInit(GFX_TOP, nullptr);
        flags |= CONSOLE_TOP;
    }

    if ((f & CONSOLE_BOTTOM) && !(flags & CONSOLE_BOTTOM)) {
        consoleInit(GFX_BOTTOM, nullptr);
        flags |= CONSOLE_BOTTOM;
    }
}

void Services::disable(uint32_t f) {
    using namespace xs::services;

    // --- Shutdown in reverse order ---

    if ((f & CONSOLE_BOTTOM) && (flags & CONSOLE_BOTTOM)) {
        consoleClear();
        flags &= ~CONSOLE_BOTTOM;
    }

    if ((f & CONSOLE_TOP) && (flags & CONSOLE_TOP)) {
        consoleClear();
        flags &= ~CONSOLE_TOP;
    }

    if ((f & NEWS_SERVICE) && (flags & NEWS_SERVICE)) {
        newsExit();
        flags &= ~NEWS_SERVICE;
    }

    if ((f & GFX_SERVICE) && (flags & GFX_SERVICE)) {
        gfxExit();
        flags &= ~GFX_SERVICE;
    }

    if ((f & C2D_SERVICE) && (flags & C2D_SERVICE)) {
        C2D_Fini();
        flags &= ~C2D_SERVICE;
    }

    if ((f & C3D_SERVICE) && (flags & C3D_SERVICE)) {
        C3D_Fini();
        flags &= ~C3D_SERVICE;
    }
}

} // namespace xs::sys
