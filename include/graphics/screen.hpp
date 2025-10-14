#pragma once

#include "colors.hpp"
#include <3ds.h>
#include <cstdio>
#include <string.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

namespace xs::graphics::screen {
/**
 * @brief Swaps Frame Buffers
 *
 */
inline void SwapFrameBuffers() { gfxSwapBuffers(); }
/**
 * @brief Waits for the next screen refresh (VBlank)
 *
 */
inline void WaitForScreen() { gspWaitForVBlank(); }
/**
 * @brief Clears the console.
 *
 */
inline void ClearConsole() { consoleClear(); }

inline void SceneInit() { C3D_FrameBegin(0); }

inline void SceneBegin(C3D_RenderTarget *target) { C2D_SceneBegin(target); }

inline void ClearScreen(C3D_RenderTarget *target, u32 color) {
    C2D_TargetClear(target, color);
}

inline void SceneEnd() { C3D_FrameEnd(0); }
} // namespace xs::graphics::screen