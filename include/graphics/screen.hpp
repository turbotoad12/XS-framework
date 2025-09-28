#pragma once

#include <3ds.h>
#include <string.h>
#include "colors.hpp"

namespace xs::graphics::screen
{
    /**
     * @brief Swaps Frame Buffers
     * 
     */
    void SwapFrameBuffers() {
        gfxSwapBuffers();
    }
    /**
     * @brief Waits for the next screen refresh (VBlank)
     * 
     */
    void WaitForScreen() {
        gspWaitForVBlank();
    }
    /**
     * @brief Clears the console.
     * 
     */
    void ClearConsole() {
        consoleClear();
    }
}