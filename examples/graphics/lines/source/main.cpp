// Simple citro2d untextured shape example
#include <xs-framework.hpp>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

int main(int argc, char *argv[]) {
    // Initialize essential services
    xs::sys::Services services(
        xs::services::GFX_SERVICE | xs::services::C3D_SERVICE |
        xs::services::C2D_SERVICE | xs::services::CONSOLE_BOTTOM);

    // Create the top screen render target
    C3D_RenderTarget *top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

    // Define colors
    u32 clrRec1 = C2D_Color32(0x9A, 0x6C, 0xB9, 0xFF);
    u32 clrRec2 = C2D_Color32(0xFF, 0xFF, 0x2C, 0xFF);
    u32 clrRec3 = C2D_Color32(0xD8, 0xF6, 0x0F, 0xFF);
    u32 clrRec4 = C2D_Color32(0x40, 0xEA, 0x87, 0xFF);
    u32 clrClear = C2D_Color32(0xFF, 0xD8, 0xB0, 0x68);

    // Main application loop
    while (xs::sys::MainLoop()) {
        xs::hid::control::ScanInput();

        // Handle user input
        u32 kDown = xs::hid::control::GetKeysPressed();
        if (kDown & KEY_START)
            break; // Exit back to hbmenu
        
        
        // Print debug info
        printf("\x1b[1;1HSimple Xs-framework lines example");
        printf("\x1b[2;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime() * 6.0f);
        printf("\x1b[3;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime() * 6.0f);
        printf("\x1b[4;1HCmdBuf:  %6.2f%%\x1b[K", C3D_GetCmdBufUsage() * 100.0f);
        
        // --- Begin drawing ---
        xs::graphics::screen::SceneInit();
        xs::graphics::screen::ClearScreen(top, clrClear);
        xs::graphics::screen::SceneBegin(top);

        // Draw Lines
        xs::graphics::DrawSolidLine(50.0f, 50.0f, 150.0f, 50.0f, 2.0f, 0.5f, clrRec1);
        xs::graphics::DrawSolidLine(100.0f, 80.0f, 200.0f, 80.0f, 2.0f, 0.4f, clrRec2);
        xs::graphics::DrawSolidLine(150.0f, 110.0f, 250.0f, 110.0f, 2.0f, 0.3f, clrRec3);
        xs::graphics::DrawSolidLine(200.0f, 140.0f, 300.0f, 140.0f, 2.0f, 0.2f, clrRec4);

        // End frame
        xs::graphics::screen::SceneEnd();
    }
    // Automatic cleanup when `services` goes out of scope
    return 0;
}