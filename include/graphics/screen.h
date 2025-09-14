#pragma once

#include <3ds.h>
#include <string.h>

namespace xs::graphics::screen
{
    /**
     * @brief Swaps Frame Buffers
     * 
     */
    void SwapFrameBuffers() {
        gfxSwapBuffers();
    }
    void WaitForScreen() {
        gspWaitForVBlank();
    }
}