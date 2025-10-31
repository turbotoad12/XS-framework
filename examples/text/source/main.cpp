// Simple citro2d untextured shape example
#include <xs-framework.hpp>
#include <3ds.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

int main(int argc, char *argv[]) {
    // Initialize essential services
    xs::sys::Services services(
        xs::services::GFX_SERVICE | xs::services::C3D_SERVICE |
        xs::services::C2D_SERVICE | xs::services::CONSOLE_BOTTOM);

    // Create the top screen render target
    C3D_RenderTarget *top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

    // Mount RomFS so romfs:/ paths work
    Result rc = romfsInit();
    bool romfsReady = (R_SUCCEEDED(rc));

    // Load the custom font from RomFS and report if it failed (fallback will be system font)
    xs::text::Font font("romfs:/liberationitalic.ttf");
    Result fontResult = font.GetLoadResult();
    const bool customFontLoaded = R_SUCCEEDED(fontResult);

    // Create Text objects (title uses custom font if available; info uses system font)
    xs::text::Text titleText("XS-Framework Text Example", &font);
    xs::text::Text infoText("Press START to exit");

    // Main application loop
    while (xs::sys::MainLoop()) {
        xs::hid::control::ScanInput();

        // Handle user input
        u32 kDown = xs::hid::control::GetKeysPressed();
        if (kDown & KEY_START)
            break; // Exit back to hbmenu

        // Print debug info
        printf("\x1b[1;1HSimple Xs-framework Text example");
        printf("\x1b[2;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime() * 6.0f);
        printf("\x1b[3;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime() * 6.0f);
        printf("\x1b[4;1HCmdBuf:  %6.2f%%\x1b[K", C3D_GetCmdBufUsage() * 100.0f);
        if (customFontLoaded) {
            printf("\x1b[6;1HUsing custom font: liberationitalic.ttf\x1b[K");
        } else {
            printf("\x1b[6;1HCustom font failed (0x%08lX); using system font\x1b[K", fontResult);
        }

        // --- Begin drawing ---
        xs::graphics::screen::SceneInit();
        xs::graphics::screen::ClearScreen(top, xs::graphics::clrClear);
        xs::graphics::screen::SceneBegin(top);

        // Draw Text at different positions and colors
        titleText.Draw(50.0f, 50.0f, 0.5f, 1.0f, 1.0f);
        titleText.DrawWithColor(50.0f, 80.0f, 0.5f, 0.8f, 0.8f, 0xFF0000FF); // Red
        titleText.DrawWithColor(50.0f, 110.0f, 0.5f, 0.6f, 0.6f, 0x00FF00FF); // Green
        infoText.DrawWithColor(50.0f, 180.0f, 0.5f, 0.7f, 0.7f, 0xFFFFFFFF); // White
        
        // End frame
        xs::graphics::screen::SceneEnd();
    }
    if (romfsReady) romfsExit();
    // Automatic cleanup when `services` goes out of scope
    return 0;
}
